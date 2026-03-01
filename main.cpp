/**
 * @file main.cpp
 * @brief Driver program for the load balancer simulation.
 *
 * Reads configuration from config.txt, gets user input for
 * number of servers and run time, then runs the simulation.
 */

/**
 * @mainpage Load Balancer Project - CSCE 412
 *
 * @section desc Project Description
 * 
 * This project simulates a load balancer that distributes requests
 * across multiple servers. Requests have random IPs and processing times 
 * and the system must dynamically scale to handle all of them.
 *
 * @section classes Classes
 * - **Request** - Generates random IP addresses, both in and out, and random times for each request to be processed.
 * - **RequestQueue** - Queue that holds pending requests waiting to be assigned.
 * - **WebServer** - Takes requests from the Load Balancer, processes the requests
 * - **LoadBalancer** - Manages the servers, request queue, dynamic scaling, IP blocking, and logging.
 *
 * @section config Configuration
 * The config.txt file supports:
 * - cooldown: clock cycles to wait
 * - blocked_start: start of blocked IP range
 * - blocked_end: end of blocked IP range
 *
 * @section usage Usage
 * Run the program with make -> ./main and enter the number of servers and clock cycles in the terminal.
 * Initial queue is filled with servers x 100 requests.
 *
 * @author Yuriy Astapov
 */
#include "LoadBalancer.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>

int main() {
    //random seed
    srand(time(0));

    int cooldown = 20;
    std::string blockedStart = "";
    std::string blockedEnd = "";

    //read config file
    std::ifstream configFile("config.txt");
    if (configFile.is_open()) {
        std::string str;
        while (configFile >> str) {
            if (str == "cooldown")
                configFile >> cooldown;
            else if (str == "blocked_start")
                configFile >> blockedStart;
            else if (str == "blocked_end")
                configFile >> blockedEnd;
        }
        configFile.close();
    }
    else {
        std::cout << "No config file found" << std::endl;
    }

    //get user input
    int numServers;
    int runTime;

    std::cout << "Enter number of servers: ";
    std::cin >> numServers;
    std::cout << "Enter clock cycles: ";
    std::cin >> runTime;

    LoadBalancer lb(numServers, runTime, cooldown);

    if (blockedStart != "" && blockedEnd != "") {
        lb.setBlockedRange(blockedStart, blockedEnd);
    }

    lb.initializeQueue(numServers * 100);
    lb.run();

    return 0;
}
