// ./steps/step005.c
/* {{{1 includes */
#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
/*}}}1*/

// #include "simple_dictionary.h"

/*{{{1 MACROS */
#define PORT 8080
#define BUFFER_SIZE 1024
/*}}}1*/

/*{{{1 structs */
	struct sockaddr_in host_addr;
/*}}}1 */

/*{{{1 functions */
/*{{{2 int CreateSocket()*/
int CreateSocket(){
	printf("creating socket");
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockfd == -1) {
		perror("webserver (socket)");
		return 0;
	}
	printf("socket created successfully\n");

	return sockfd;
}
/*}}}2*/
/*}}}1*/

/*{{{2 CreateAddress*/
struct sockaddr_in CreateAddress(int host_addrlen){
	printf("creating address");
	host_addr.sin_family = AF_INET;
	host_addr.sin_port = htons(PORT);
	host_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	printf("address created successfully");
	return(host_addr);
}
/*}}}2*/

/*{{{2*/
int BindSocketToAddress(
	int sockfd, 
	struct sockaddr_in host_addr, 
	int host_addrlen
){ 
    if (bind(sockfd, (struct sockaddr *)&host_addr, host_addrlen) != 0) {
        perror("webserver (bind)");
        return 0;
    }
    printf("socket successfully bound to address\n");
	return 1;
}
/*}}}2*/

/*{{{2 Read()*/
int Read(){
	return(1);
}
/*}}}2*/

/*{{{2 Write()*/
int Write(){
	return(1);
}
/*}}}2*/

/*{{{2*/
int ListenForIncomingConnections(
	char buffer[BUFFER_SIZE],
	int sockfd,
	struct sockaddr_in host_addr, 
	int host_addrlen
){
    if (listen(sockfd, SOMAXCONN) != 0) {
        perror("webserver (listen)");
        return 0;
    }
    printf("server listening for connections\n");

    for (;;) {
        // Accept incoming connections
        int newsockfd = accept(
			sockfd, 
			(struct sockaddr *)&host_addr,
            (socklen_t *)&host_addrlen
		);

        if (newsockfd < 0) {
            perror("webserver (accept)");
            continue;
        }
        printf("connection accepted\n");

        // Read from the socket
		Read();
        int valread = read(
			newsockfd, 
			buffer, 
			BUFFER_SIZE
		);

        if (valread < 0) {
            perror("webserver (read)");
            continue;
        }

        close(newsockfd);
    }

	return (1);
}

/*}}}2*/


/*{{{1 int main()*/
int main() {
    char buffer[BUFFER_SIZE];

    // Create a socket
	int sockfd = CreateSocket();
    // Create the address to bind the socket to
	int host_addrlen = sizeof(host_addr);
	struct sockaddr_in host_addr = CreateAddress(host_addrlen);

    // Bind the socket to the address
	int bind_pass = BindSocketToAddress( sockfd, host_addr, host_addrlen);
	if(bind_pass == 0){
		printf("failed to bind socket");
	}

    // Listen for incoming connections
	int listened = ListenForIncomingConnections(buffer, sockfd, host_addr, host_addrlen);
	if(listened == 0){
		printf("failed to listen to connections");
	}

    return 0;
}
/*}}}1*/
