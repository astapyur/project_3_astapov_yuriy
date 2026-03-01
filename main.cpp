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
