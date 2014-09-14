#include "terminal_Server.h"

static void client_handler(union sigval sv){
  struct mq_attr attributes;
  char *buf;
  mqd_t mqdes = *((mqd_t *)sv.sival_ptr);
  mq_getattr(mqdes,&attributes);
  
  while(1){
    buf = malloc(attributes.mq_msgsize+1);
    mq_receive(mqdes,buf,attributes.mq_msgsize,NULL);
    printf("\n%s\n",buf);
    free(buf);
  }
}

int main(int argc, char* argv[]){
  struct sigevent signal_event;
  char *str = NULL;
  char *name = NULL;
  char *message = NULL;
  char *message_que = malloc(sizeof(argv[1])*sizeof(char)+1);
  size_t len = 0;
  mqd_t messageQue_descriptor;

  //setup for user interaction
  printf("Enter your name:\n");
  getline(&str,&len,stdin);
  name = malloc(len*sizeof(char));
  snprintf(name,len,"%s",str);
  removeGodDamnNewLine(name);

  //setup queing
  strcat(message_que,"/");
  strcat(message_que,argv[1]);
  messageQue_descriptor = mq_open(message_que,O_RDWR);
  
  //setup handler
  signal_event.sigev_notify = SIGEV_THREAD;
  signal_event.sigev_notify_function = client_handler;
  signal_event.sigev_notify_attributes = NULL;
  signal_event.sigev_value.sival_ptr = &messageQue_descriptor;
  
  mq_notify(messageQue_descriptor, &signal_event);

  while(1){
    printf("\nEnter Message:\n");
    getline(&str,&len,stdin);
    message = malloc(sizeof(name)*sizeof(char)+len*sizeof(char));
    snprintf(message,sizeof(name),"%s",name);
    strcat(message,":  ");
    strcat(message,str);
    // printf("%s\n",message);
    send_message(message_que,message);
    free(message);
  }
  
  
  printf("\n%s\n",str);
  free(str);
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
