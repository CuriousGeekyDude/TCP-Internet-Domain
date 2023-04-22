#include "path.h"

int main(int argc, char* argv[])
{
    struct addrinfo hints;
    struct addrinfo* results;
    struct sockaddr srvAddress;
    int addrInfoRes, fdSocket;
    socklen_t srvAddressLen;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_NUMERICSERV;


    addrInfoRes = getaddrinfo("localhost", PORT_NUM, &hints, &results);

    if(addrInfoRes != 0) {
        const char* errorMsge = gai_strerror(addrInfoRes);
        exit(EXIT_FAILURE);
    }

    while(results != NULL) {
        fdSocket = socket(results->ai_family, results->ai_socktype, results->ai_protocol);

        if(fdSocket != -1)
            break;
        results = results->ai_next; 
    }

    srvAddress = *(results->ai_addr);
    srvAddressLen = results->ai_addrlen;

    freeaddrinfo(results);

    
    connect(fdSocket, &srvAddress, srvAddressLen);

    while(read(STDIN_FILENO, buffer, BuffSize) > 0) {
        write(fdSocket, buffer, BuffSize);
        initializeBuffer(buffer, BuffSize);
    }

    close(fdSocket);

    exit(EXIT_SUCCESS);
}