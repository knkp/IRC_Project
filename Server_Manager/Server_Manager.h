#include<stdio.h> //printf
#include<string.h>    //strlen
#include<sys/socket.h>    //socket
#include<arpa/inet.h> //inet_addr
#include<errno.h>

#define SS_PORT 9002

typedef enum{
  CREATE_CHANNEL,
  LIST_CHANNELS,
  LIST_USERS,
  REGISTER_USERS,
  SEND_MESSAGE
} EVENTS_TO_PROC;

struct USER{
  char *name;
  int size_name;
  int auth; // id
};

struct MESSAGE_EVENT{
  struct USER user;
  EVENTS_TO_PROC events;
};

void initialize_socket_socker(void);
int proc_events(void);
