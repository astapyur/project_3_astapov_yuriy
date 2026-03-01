/**
 * @file Request.h
 * @brief Defines the Request struct used to represent a web request.
 */
#ifndef REQUEST_H
#define REQUEST_H
#include <string>

/**
 * @struct Request
 * @brief Represents a web request with sender/receiver IPs, processing time, and job type.
 */
struct Request {
    public:
        int requestID;          ///< Unique ID for this request
        static int nextID;      ///< Static counter for assigning IDs
        std::string ipIn;       ///< Sender IP address
        std::string ipOut;      ///< Receiver IP address
        int processTime;        ///< Time in clock cycles to process
        char jobType;           ///< 'P' for processing, 'S' for streaming

        /**
         * @brief Default constructor. Sets empty IPs, time 0, type P.
         */
        Request();

        /**
         * @brief Parameterized constructor.
         * @param ipIn Sender IP address.
         * @param ipOut Receiver IP address.
         * @param processTime Clock cycles needed to process.
         * @param jobType 'P' for processing, 'S' for streaming.
         */
        Request(std::string ipIn, std::string ipOut, int processTime, char jobType);
};

/**
 * @brief Generates a random IP address string in x.x.x.x format.
 * @return Random IP address string.
 */
std::string genRandomIP();

/**
 * @brief Creates a Request with random IPs, random time (10-1000), and random job type.
 * @return Randomly generated Request.
 */
Request genRandomRequest();

#endif
