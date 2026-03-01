#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "Request.h"

class WebServer {
    public:
        int id;
        bool busy;
        Request currRequest;
        int timeRemaining;

        WebServer(int id);

        void assignRequest(Request request);

        void increaseTime();

        bool isBusy();

        int getId();

        Request getCurrRequest();
};

#endif
