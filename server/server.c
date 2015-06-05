#include "../old_code/terminal_Server.h"

int main(int argc,char* argv[]){
  char* server_que = malloc((sizeof(argv[1])+1)*sizeof(char));
  mqd_t serverQ;

  printf("initiating server\n");
  printf("instantiating server message que\n");
  serverQ = setup_mque(argv[1], server_que);
  printf("setting up server handler\n");
  setup_handler(server_handler, &serverQ);
  printf("looping");
  while(1){
    continue;
  }
  return 0;
}
