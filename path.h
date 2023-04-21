#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include "error_functions.c"
#define PORT_NUM "55000"
#define BuffSize 4096

static char buffer[BuffSize];