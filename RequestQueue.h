#ifndef REQUESTQUEUE_H
#define REQUESTQUEUE_H
#include "Request.h"
#include <queue>

class RequestQueue {
    std::queue<Request> queue;
    
    void enqueue(Request request);

    Request dequeue();

    int size();

    bool isEmpty();
};

#endif
