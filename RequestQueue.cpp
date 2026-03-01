#include "RequestQueue.h"

void RequestQueue::enqueue(Request request) {
    queue.push(request);
}

Request RequestQueue::dequeue() {
    Request front = queue.front();
    queue.pop();
    return front;
}

int RequestQueue::size() {
    return queue.size();
}

bool RequestQueue::isEmpty() {
    return queue.empty();
}
