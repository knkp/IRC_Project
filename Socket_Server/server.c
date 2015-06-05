/*
    C socket server example
*/
 
#include<stdio.h>
#include<string.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write
#include<errno.h>
#include "libanc/ancillary.h"
 
int main(int argc , char *argv[])
{
  int socket_desc , client_sock , c , read_size;
  // int incomingConnections;
  FILE* incomingConnections;
  struct sockaddr_in server , client;
  char client_message[29] = "this is from the test Server";
  //Create socket descriptor to place received descriptors into:
  // incomingConnections = socket(AF_INET, SOCK_STREAM, 0);

  //Create socket
  socket_desc = socket(AF_INET , SOCK_STREAM , 0);
  if (socket_desc == -1)
    {
      printf("Could not create socket");
    }
  puts("Socket created");
     
  //Prepare the sockaddr_in structure
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = htons( 9001 );
     
  //Bind
  if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
      //print the error message
      perror("bind failed. Error");
      return 1;
    }
  puts("bind done");
     
  //Listen
  listen(socket_desc , 3);
     
  //Accept and incoming connection
  puts("Waiting for incoming connections...");
  c = sizeof(struct sockaddr_in);
     
  //accept connection from an incoming client
  client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
  if (client_sock < 0)
    {
      perror("accept failed");
      return 1;
    }
  puts("Connection accepted");
     
  //Receive a message from client
  /* while( (read_size = recv(client_sock , client_message , 200 , 0)) > 0 )
    {
      //Send the message back to client
      // write(client_sock , client_message , strlen(client_message));

      printf("%s", &client_message);
    }
*/  
  int loop = 1;
  while(loop!=0){
    loop = ancil_recv_fd(client_sock, &incomingConnections);
    if(loop == -1){
      printf("getting file descriptor failed with error: %d\n", errno);
    }
  }

  printf("writing to received socket\n");
  if(send(incomingConnections, client_message, strlen(client_message),0) == -1){
      printf("could not write to received socket\n");
    }
   
  if(read_size == 0)
    {
      puts("Client disconnected");
      fflush(stdout);
    }
  else if(read_size == -1)
    {
      perror("recv failed");
    }
     
  return 0;
}
