#include "path.h"


int main(int argc, char* argv[])
{
    struct addrinfo hints;
    struct sockaddr srvAddress;
    struct addrinfo* result = NULL;
    int fdSocket, addrinfoResult, fdAccept;
    socklen_t srvAddressLen = 0;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags =  AI_NUMERICSERV | AI_PASSIVE;
    addrinfoResult = getaddrinfo(NULL, PORT_NUM, &hints, &result);

    if(addrinfoResult != 0) {
        const char* errMsge = gai_strerror(addrinfoResult);
        printf("%s\n", errMsge);
        exit(EXIT_FAILURE);
    }

    while(result != NULL) {
        fdSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

        if(fdSocket == -1)
            continue;
        else {
            srvAddress = *(result->ai_addr);
            srvAddressLen = result->ai_addrlen;
            break;
        }
        result = result->ai_next;
    }

    freeaddrinfo(result);

    if(bind(fdSocket, &srvAddress, srvAddressLen) == -1)
        errExit("bind() server");

    if(listen(fdSocket, SOMAXCONN) == -1)
        errExit("listen() server");

    for(;;) {
        fdAccept = accept(fdSocket, &srvAddress, &srvAddressLen);

        if(fdAccept != -1)
            break;
            
    }

    while(read(fdAccept, buffer, BuffSize) > 0) {
        printf("client: ");
        fflush(stdout);
        write(STDOUT_FILENO, buffer, BuffSize);
    }    

    close(fdAccept);
    close(fdSocket);
    

    exit(EXIT_SUCCESS);

}