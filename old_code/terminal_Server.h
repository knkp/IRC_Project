/*Programmer: Stephen Copeland
  This will define the functions for the service that will run on the local machine 
  for inter-terminal communication. The idea of it is will act almost like a server where the machine itself
  is the network. Once the program is started it will run in the background as a service and one can run a command from their shell
  to register themsleves, it then records an identifier for the shell as well as the user and can route information from one shell to another
  based on a users intended recepient.
*/

#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/msg.h>
#include <mqueue.h>
#include <malloc.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <sys/mman.h>

// to compile, you must build with the real time library or as a gcc command: 'gcc -o _EXECUTABLE _SOURCE -lrt'
// not that we are using signals we must also compile using -signal
typedef struct SC_STREAM{
  mqd_t server;
  mqd_t client;
};

extern enum MESSAGE {
  NO_RESPONSE,
  REGISTERED_USER,
  USER_ALREADY_EXISTS
};

extern enum REQUEST {
  _REGISTER
};

extern void update_que(char *name,mqd_t *message_que);
 
extern void client_handler(union sigval sv);

extern void server_handler(union sigval sv);

extern void setup_que(char *input,char **message_que, mqd_t *messageQue_descriptor);

extern void setup_user_account(char **name);

extern mqd_t open_que(char *name, char *qname);

extern mqd_t setup_mque(char *name, char *message_que_name);

extern void removeNewLine(char *value);

extern int setup_handler(void (*func)(union sigval sv), mqd_t *message_que_descriptor);  
//SC_STREAM register(char *name);

extern void message(char *from, unsigned char *too);

extern void requestClientList(char *user);

extern void parse_file(char *CONFIG_FILE_PATH, char **LINES);

extern int count_lines(FILE* file);

// note1 this is a blocking call it may be best to run it in a child process
// note2 the "que_name" must start with a forward slash so if the name is to be "test" is must be "/test"
extern mqd_t create_mQue(char* que_name);

extern int client_que_creator(char *name);

extern int send_message(mqd_t* que, char* message);

extern void write_to_file(char *file,char *line);

//extern REQUEST message_received(char *MESSAGE);
