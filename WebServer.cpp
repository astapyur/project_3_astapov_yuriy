/**
 * @file WebServer.cpp
 * @brief Implements the WebServer class.
 */
#include "WebServer.h"

WebServer::WebServer(int id) {
    this->id = id;
    this->busy = false;
    this->timeRemaining = 0;
}

void WebServer::assignRequest(Request request) {
    this->currRequest = request;
    this->timeRemaining = request.processTime;
    this->busy = true;
}

void WebServer::increaseTime() {
    if (busy) {
        timeRemaining--;
        if (timeRemaining <= 0) {
            busy = false;
        }
    }
}

bool WebServer::isBusy() {
    return busy;
}

int WebServer::getId() {
    return id;
}

Request WebServer::getCurrRequest() {
    return currRequest;
}
