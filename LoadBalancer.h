/**
 * @file LoadBalancer.h
 * @brief Defines the LoadBalancer class that manages servers and the request queue.
 */
#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include "RequestQueue.h"
#include "WebServer.h"
#include <vector>
#include <string>
#include <fstream>

/**
 * @class LoadBalancer
 * @brief Manages web servers and a request queue, handling dynamic scaling and IP blocking.
 */
class LoadBalancer {
    public:
        std::vector<WebServer*> servers;    ///< List of web server pointers
        RequestQueue requestQueue;          ///< Queue of pending requests
        int numServers;                     ///< Current number of servers
        int totalTime;                      ///< Total clock cycles to run
        int cooldownTime;                   ///< Cycles to wait between scaling checks
        int cooldownRemaining;              ///< Remaining cooldown cycles
        int clockCycle;                     ///< Current clock cycle
        int startingQueueSize;              ///< Queue size after initial fill
        int requestsProcessed;              ///< Total requests completed
        int requestsBlocked;                ///< Total requests blocked by firewall
        int serversAdded;                   ///< Servers added during simulation
        int serversRemoved;                 ///< Servers removed during simulation

        std::string blockedStartIP;         ///< Start of blocked IP range
        std::string blockedEndIP;           ///< End of blocked IP range
        std::ofstream logFile;              ///< Output stream for log file

        /**
         * @brief Constructor. Creates servers and opens log file.
         * @param numServers Initial number of servers.
         * @param runTime Total clock cycles to simulate.
         * @param cooldown Cycles between scaling adjustments.
         */
        LoadBalancer(int numServers, int runTime, int cooldown);

        /**
         * @brief Destructor. Deletes servers and closes log file.
         */
        ~LoadBalancer();

        /**
         * @brief Assigns queued requests to any free servers.
         */
        void assignRequests();

        /**
         * @brief Checks queue size and adds/removes servers based on thresholds.
         */
        void adjustServers();

        /**
         * @brief Adds a new server to the pool.
         */
        void addServer();

        /**
         * @brief Removes an idle server from the pool.
         */
        void removeServer();

        /**
         * @brief Randomly adds a new request to the queue (10% chance per cycle).
         */
        void addRandomRequests();

        /**
         * @brief Checks if an IP falls within the blocked range.
         * @param ip The IP address to check.
         * @return True if the IP is blocked.
         */
        bool isBlocked(std::string ip);

        /**
         * @brief Logs a message to console with color and to the log file.
         * @param message The message to log.
         * @param color ANSI color code for console output.
         */
        void log(std::string message, std::string color);

        /**
         * @brief Sets the blocked IP range for the firewall.
         * @param start Start of the IP range.
         * @param end End of the IP range.
         */
        void setBlockedRange(std::string start, std::string end);

        /**
         * @brief Fills the queue with random requests, blocking any in the blocked range.
         * @param count Number of requests to attempt to generate.
         */
        void initializeQueue(int count);

        /**
         * @brief Runs the main simulation loop.
         */
        void run();

        /**
         * @brief Prints the end-of-simulation summary to console and log file.
         */
        void printSummary();
};

#endif
