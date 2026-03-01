#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include "RequestQueue.h"
#include "WebServer.h"
#include <vector>
#include <string>
#include <fstream>

class LoadBalancer {
    public:
        std::vector<WebServer*> servers;
        RequestQueue requestQueue;
        int numServers;
        int totalTime;
        int cooldownTime;
        int cooldownRemaining;
        int clockCycle;
        int startingQueueSize;
        int requestsProcessed;
        int requestsBlocked;
        int serversAdded;
        int serversRemoved;

        std::string blockedStartIP;
        std::string blockedEndIP;
        std::ofstream logFile;

        LoadBalancer(int numServers, int runTime, int cooldown);
        ~LoadBalancer();

        void assignRequests();
        void adjustServers();
        void addServer();
        void removeServer();
        void addRandomRequests();
        bool isBlocked(std::string ip);
        void log(std::string message, std::string color);

        void setBlockedRange(std::string start, std::string end);
        void initializeQueue(int count);
        void run();
        void printSummary();
};

#endif
