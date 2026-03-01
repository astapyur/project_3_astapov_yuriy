#ifndef REQUEST_H
#define REQUEST_H
#include <string>

struct Request {
    public:
        int requestID;
        static int nextID;
        std::string ipIn;
        std::string ipOut;
        int processTime;
        char jobType;

        Request();

        Request(std::string ipIn, std::string ipOut, int processTime, char jobType);
};

std::string genRandomIP();

Request genRandomRequest();

#endif
