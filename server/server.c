#include "../old_code/terminal_Server.h"

int main(int argc,char* argv[]){
  char* message_que = malloc(sizeof(argv[1]+1)*sizeof(char));
  strcat(message_que,"/");
  strcat(message_que,argv[1]);
  if(argv[2]!=NULL){
     mq_unlink(message_que);
     printf("\n message que: %s was just destroyed\n",argv[1]);
     return 0;
    }
  
  printf("\n message que: %s was just created\n",argv[1]);
  create_mQue(message_que);
  return 0;
}
