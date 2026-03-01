/**
 * @file LoadBalancer.cpp
 * @brief Implements the LoadBalancer class.
 */
#include "LoadBalancer.h"
#include <iostream>
#include <cstdlib>
#include <cstdio> //for sscanf

#define RESET   "\033[0m"
#define RED "\033[31m"      //blocked range, removed server
#define GREEN   "\033[32m"  //added server, start something
#define YELLOW  "\033[33m"  //queue size
#define BLUE    "\033[34m"  //fill, new request, finished request
#define WHITE   "\033[37m"  //assigned request

LoadBalancer::LoadBalancer(int numServers, int totalTime, int cooldown) {
    this->numServers = numServers;
    this->totalTime = totalTime;
    this->cooldownTime = cooldown;
    this->cooldownRemaining = 0;
    this->clockCycle = 0;
    this->startingQueueSize = 0;
    this->requestsProcessed = 0;
    this->requestsBlocked = 0;
    this->serversAdded = 0;
    this->serversRemoved = 0;

    for (int i = 0; i < numServers; i++) {
        servers.push_back(new WebServer(i));
    }

    logFile.open("log.txt");
}

LoadBalancer::~LoadBalancer() {
    for (long unsigned int i = 0; i < servers.size(); i++) {
        delete servers[i];
    }
    if (logFile.is_open()) {
        logFile.close();
    }
}

void LoadBalancer::setBlockedRange(std::string start, std::string end) {
    blockedStartIP = start;
    blockedEndIP = end;
    log("Blocked IP range: " + start + " to " + end, RED);
}

bool LoadBalancer::isBlocked(std::string ip) {
    if (blockedStartIP == "" || blockedEndIP == "")
        return false;
    // parse ip into 4 numbers
    int a1, b1, c1, d1;
    int a2, b2, c2, d2;
    int a, b, c, d;
    sscanf(blockedStartIP.c_str(), "%d.%d.%d.%d", &a1, &b1, &c1, &d1);
    sscanf(blockedEndIP.c_str(), "%d.%d.%d.%d", &a2, &b2, &c2, &d2);
    sscanf(ip.c_str(), "%d.%d.%d.%d", &a, &b, &c, &d);
    // compare first octet to see if it falls in range
    if (a >= a1 && a <= a2)
        return true;
    return false;
}

void LoadBalancer::initializeQueue(int count) {
    int addedReqs = 0;
    int blockedReqs = 0;
    for (int i = 0; i < count; i++) {
        Request req = genRandomRequest();
        if (isBlocked(req.ipIn) || isBlocked(req.ipOut)) {
            blockedReqs++;
            requestsBlocked++;
        } else {
            requestQueue.enqueue(req);
            addedReqs++;
        }
    }
    startingQueueSize = requestQueue.size();
    log("Initialized queue with " + std::to_string(addedReqs) + " requests and blocked " + std::to_string(blockedReqs) + " requests", BLUE);
}

void LoadBalancer::log(std::string message, std::string color) {
    std::string logMsg = "[" + std::to_string(clockCycle) + "] " + message;
    std::cout << color << logMsg << RESET << std::endl;
    if (logFile.is_open()) {
        logFile << logMsg << std::endl;
    }
}

void LoadBalancer::assignRequests() {
    for (long unsigned int i = 0; i < servers.size(); i++) {
        if (!servers[i]->isBusy() && !requestQueue.isEmpty()) {
            Request req = requestQueue.dequeue();
            servers[i]->assignRequest(req);
            log("Assigned request #" + std::to_string(req.requestID) + " to server " + std::to_string(servers[i]->getId()) + " (" + req.ipIn + " -> " + req.ipOut + ") type=" + req.jobType + " time=" + std::to_string(req.processTime), WHITE);
        }
    }
}

void LoadBalancer::addServer() {
    int newId = servers.size();
    servers.push_back(new WebServer(newId));
    numServers++;
    serversAdded++;
    log("Added server #" + std::to_string(newId) + " (total servers: " + std::to_string(numServers) + ")", GREEN);
}

void LoadBalancer::removeServer() {
    if (numServers <= 1)
        return;

    for (int i = servers.size() - 1; i >= 0; i--) {
        if (!servers[i]->isBusy()) {
            log("Removed server #" + std::to_string(servers[i]->getId()) + " (remaining servers: " + std::to_string(numServers - 1) + ")", RED);
            delete servers[i];
            servers.erase(servers.begin() + i);
            numServers--;
            serversRemoved++;
            return;
        }
    }
}

void LoadBalancer::adjustServers() {
    if (cooldownRemaining > 0) {
        cooldownRemaining--;
        return;
    }

    int queueSize = requestQueue.size();
    int low = 50 * numServers;
    int high = 80 * numServers;

    if (queueSize < low && numServers > 1) {
        log("Queue size=" + std::to_string(queueSize) + ", below threshold (" + std::to_string(low) + ")", YELLOW);
        removeServer();
        cooldownRemaining = cooldownTime;
    } else if (queueSize > high) {
        log("Queue size=" + std::to_string(queueSize) + ", above threshold (" + std::to_string(high) + ")", YELLOW);
        addServer();
        cooldownRemaining = cooldownTime;
    }
}

void LoadBalancer::addRandomRequests() {
    if (rand() % 10 == 0) {
        Request req = genRandomRequest();
        if (isBlocked(req.ipIn) || isBlocked(req.ipOut)) {
            requestsBlocked++;
            log("New random request #" + std::to_string(req.requestID) + " blocked", RED);
        } else {
            requestQueue.enqueue(req);
            log("New random request #" + std::to_string(req.requestID) + " added to queue", BLUE);
        }
    }
}

void LoadBalancer::run() {
    log("Starting with " + std::to_string(numServers) + " servers for " + std::to_string(totalTime) + " clock cycles", GREEN);
    log("Starting queue size: " + std::to_string(startingQueueSize), GREEN);
    log("Task time range: 10 - 1000 clock cycles", GREEN);

    for (clockCycle = 0; clockCycle < totalTime; clockCycle++) {
        for (long unsigned int i = 0; i < servers.size(); i++) {
            if (servers[i]->isBusy()) {
                servers[i]->increaseTime();
                if (!servers[i]->isBusy()) {
                    requestsProcessed++;
                    log("Server " + std::to_string(servers[i]->getId()) + " finished request #" + std::to_string(servers[i]->getCurrRequest().requestID), BLUE);
                }
            }
        }

        assignRequests();
        addRandomRequests();
        adjustServers();
    }

    log("Complete.", GREEN);
    printSummary();
}

void LoadBalancer::printSummary() {
    int activeServers = 0;
    int inactiveServers = 0;
    for (long unsigned int i = 0; i < servers.size(); i++) {
        if (servers[i]->isBusy())
            activeServers++;
        else
            inactiveServers++;
    }

    std::string summary = "\n=====Summary=====\n";
    summary += "Starting queue size: " + std::to_string(startingQueueSize) + "\n";
    summary += "Ending queue size: " + std::to_string(requestQueue.size()) + "\n";
    summary += "Task time range: 10 - 1000\n";
    summary += "Requests processed: " + std::to_string(requestsProcessed) + "\n";
    summary += "Requests remaining in queue: " + std::to_string(requestQueue.size()) + "\n";
    summary += "Requests rejected (firewall): " + std::to_string(requestsBlocked) + "\n";
    summary += "Final server count: " + std::to_string(numServers) + "\n";
    summary += "Active servers: " + std::to_string(activeServers) + "\n";
    summary += "Inactive servers: " + std::to_string(inactiveServers) + "\n";
    summary += "Servers added during run: " + std::to_string(serversAdded) + "\n";
    summary += "Servers removed during run: " + std::to_string(serversRemoved) + "\n";
    summary += "======================\n";

    std::cout << GREEN << summary << RESET << std::endl;
    if (logFile.is_open()) {
        logFile << summary << std::endl;
    }
}
