/**
 * @file Request.cpp
 * @brief Implements the Request struct and random generation functions.
 */
#include "Request.h"
#include <cstdlib>
#include <ctime>

int Request::nextID = 0;

Request::Request(){
    requestID = nextID++;
    ipIn = "";
    ipOut = "";
    processTime = 0;
    jobType = 'P';
}

Request::Request(std::string ipIn, std::string ipOut, int processTime, char jobType){
    this->requestID = nextID++;
    this->ipIn = ipIn;
    this->ipOut = ipOut;
    this->processTime = processTime;
    this->jobType = jobType;
}
std::string genRandomIP() {
    return std::to_string(rand() % 256) + "." +
        std::to_string(rand() % 256) + "." +
        std::to_string(rand() % 256) + "." +
        std::to_string(rand() % 256);
}

Request genRandomRequest() {
    std::string ipIn = genRandomIP();
    std::string ipOut = genRandomIP();
    int processTime = 10 + rand() % (1000 - 10 + 1);   //generates number between 10 and 1000
    char jobType = (rand() % 2 == 0) ? 'P' : 'S';
    return Request(ipIn, ipOut, processTime, jobType);
}
