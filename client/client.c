#include "../old_code/terminal_Server.h"
#define handle_error(msg)\
  do{perror(msg);exit(-1);} while(0)



int main(int argc, char* argv[]){
  char *name = NULL;
  char *message = NULL;
  char *server_que = NULL;
  char *client_que = NULL;
  mqd_t *server_descriptor;
  mqd_t *client_descriptor;

  setup_user_account(&name);
  
  client_descriptor = setup_mque(name, client_que);

  server_descriptor = open_que(argv[1], server_que);

  setup_handler(client_handler, &client_descriptor);

  printf("\nEnter Message:\n");
  while(1){
    update_que(&name, server_descriptor);
  }

  free(&server_que);
  free(&client_que);

  return 0;
}
