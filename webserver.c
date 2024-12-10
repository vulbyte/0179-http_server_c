#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>

// struct sockaddr_in {
// 	sa_family_t	sin_family; /* address family: AF_INET */
// 	in_port_t	sin_port; /* port in network byte order */	
// 	struct in_addr 	sin_addr; /*internet address*/
// };
// 
// struct in_addr {
// 	uint32_t	s_addr; /* address in network byte order */
// };

//{{{1
int main() {
	printf("starting server \n");

	int port = 8080;
	
	// {{{2 creating the socket
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	if(sockfd == -1){
		perror("webserver (socket)\n");
		return 1;
	}
	printf("socket created successfully\n");
	// }}} 2


	// {{{2 create the addr and bind to socket
	struct sockaddr_in host_addr;
	int host_addrlen = sizeof(host_addr);

	host_addr.sin_family = AF_INET;
	host_addr.sin_port = htons(port);
	host_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	// }}}2
	
	// {{{2 bind the socket to addr
	if (bind(sockfd, (struct sockaddr *)&host_addr, host_addrlen) != 0) {
		perror("webserver (bind)\n");
		return 1;
	}	
	printf("socket successfully bound to address\n");
	// }}}2

	//{{{2 listen for incoming connections
	if (listen(sockfd, SOMAXCONN) != 0) {
		perror("webserver (listen)");
		return 1;
	}
	printf("listening for connetions\n");
	//}}}2

	//{{{2 accept/refuse connection
	for (;;){
		//accept connections
		int newsockfd = accept(
			sockfd, (struct sockaddr*) &host_addr, 
			(socklen_t*)&host_addrlen
		);
		
		if(newsockfd < 0){
			perror("webserver (accept)"); 
			continue;
		}
		printf("connection accepted \n");

		close(newsockfd);
	}
	//}}}2

	//{{{2 read/write
	//}}}2

	return 0;
};
//}}}1
