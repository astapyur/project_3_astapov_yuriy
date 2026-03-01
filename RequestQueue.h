/**
 * @file RequestQueue.h
 * @brief Defines the RequestQueue class for managing a queue of requests.
 */
#ifndef REQUESTQUEUE_H
#define REQUESTQUEUE_H
#include "Request.h"
#include <queue>

/**
 * @class RequestQueue
 * @brief Wrapper around std::queue to manage web requests.
 */
class RequestQueue {
    public:
        std::queue<Request> queue;  ///< Internal queue of Request objects

        /**
         * @brief Adds a request to the back of the queue.
         * @param request The request to add.
         */
        void enqueue(Request request);

        /**
         * @brief Removes and returns the request at the front of the queue.
         * @return The front request.
         */
        Request dequeue();

        /**
         * @brief Returns the number of requests in the queue.
         * @return Queue size.
         */
        int size();

        /**
         * @brief Checks if the queue has no requests.
         * @return True if queue is empty.
         */
        bool isEmpty();
};

#endif
