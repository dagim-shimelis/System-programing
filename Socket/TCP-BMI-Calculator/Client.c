#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<netinet/in.h>
#include<netdb.h>

void error(const char *msg){
	perror(msg);
	exit(1);
}

int main(int argc,char *argv[]){
	
	int sockfd,portno,n;
	struct sockaddr_in serv_addr;
	struct hostent *server;

	char buffer[256];
	if(argc < 3){
		fprintf(stderr,"usage %s hotname pport\n",argv[0]);
		exit(1);
	}

	portno = atoi(argv[2]);
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	
	if(sockfd < 0){
		error("Error opening socket");
	}

	server = gethostbyname(argv[1]);
	if(server == NULL){
		fprintf(stderr,"no Such host");
        exit(0);
	}
	bzero((char *) &serv_addr,sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	bcopy((char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr,server->h_length);
	serv_addr.sin_port = htons(portno);
	if(connect(sockfd, (struct sockaddr *) &serv_addr , sizeof(serv_addr)) < 0){
		error("Connection Failed !!");
	}
      	
  
	float num1,num2,ans;

	//Reading Server String 
S:      bzero(buffer,256);
	num1 = read(sockfd,buffer,256);
	if(num1 < 0){
		error("Error reading From Socket");
	}

	printf("Server - %s\n",buffer);
	scanf("%d",&num1);
	write(sockfd,&num1,sizeof(float));

	bzero(buffer,256);
        num2 = read(sockfd,buffer,256);
        if(num2 < 0){
                error("Error reading From Socket");
        }

        printf("Server - %s\n",buffer);
        scanf("%d",&num2);
        write(sockfd,&num2,sizeof(float));


	read(sockfd,&ans,sizeof(float));
	printf("Server : The BMI is : %d\n",ans);


	close(sockfd);
	return 0;

}