/**
 * @file WebServer.h
 * @brief Defines the WebServer class that processes requests.
 */
#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "Request.h"

/**
 * @class WebServer
 * @brief Simulates a web server that processes one request at a time.
 */
class WebServer {
    public:
        int id;                 ///< Server ID
        bool busy;              ///< Whether the server is currently processing
        Request currRequest;    ///< The request currently being processed
        int timeRemaining;      ///< Clock cycles left on current request

        /**
         * @brief Constructor that sets the server ID.
         * @param id The server's unique ID.
         */
        WebServer(int id);

        /**
         * @brief Assigns a request to this server and starts processing it.
         * @param request The request to process.
         */
        void assignRequest(Request request);

        /**
         * @brief Decrements time remaining. Sets busy to false when done.
         */
        void increaseTime();

        /**
         * @brief Checks if the server is busy.
         * @return True if currently processing a request.
         */
        bool isBusy();

        /**
         * @brief Returns the server ID.
         * @return Server ID.
         */
        int getId();

        /**
         * @brief Returns the current request being processed.
         * @return Current request.
         */
        Request getCurrRequest();
};

#endif
