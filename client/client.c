#include "terminal_Server.h"
#define handle_error(msg)\
  do{perror(msg);exit(-1);} while(0)



int main(int argc, char* argv[]){
  char *name = NULL;
  char *message = NULL;
  char *message_que = NULL;
  mqd_t *messageQue_descriptor = malloc(sizeof(mqd_t));

  setup_user_account(&name);

  setup_que(argv[1],&message_que,messageQue_descriptor);  

  setup_client_handler(client_handler,messageQue_descriptor);

  while(1){
    update_que(name,message_que);
  }

  free(messageQue_descriptor);
  return 0;
}

void removeGodDamnNewLine(char *assholeString){
  int iterator;
  for(iterator=0;iterator<sizeof(assholeString);iterator++){
    if(assholeString[iterator]=='\n'){
      assholeString[iterator]= ' ';
    }
  }
}
