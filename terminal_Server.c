#include "terminal_Server.h"


extern int send_message(char *que,char *message){
  mqd_t q1;
  size_t size = strlen(message)+1;
  q1 = mq_open(que,O_RDWR);
  if(q1 == -1){
    printf("\n Error Opening Que \n");
    return -1;
  }
  mq_send(q1,message,size,1);

  return 0;
}

extern void parse_file(char *CONFIG_FILE_PATH, char **PARSED_LINES){
  char *line;
  FILE *CONFIG_FILE;
  ssize_t read;
  size_t len = 0;

  int lines = 0;
  int number_of_lines = 0;

  CONFIG_FILE = fopen(CONFIG_FILE_PATH, "r");

  lines = count_lines(CONFIG_FILE);

  while((read = getline(&line, &len, CONFIG_FILE)) != -1){
    
    PARSED_LINES[number_of_lines] = malloc(strlen(line)*sizeof(char));

    snprintf(PARSED_LINES[number_of_lines], strlen(line), "%s", line);

    number_of_lines++;
  }

  // cleanup
  fclose(CONFIG_FILE);
  free(line);

}

extern int count_lines(FILE* file){
  int number_of_lines = 0;
  char ch;

  while(!feof(file)){
    ch = fgetc(file);
    if(ch=='\n'){
	number_of_lines++;
      }
    }

    rewind(file);

    return number_of_lines;
}

extern mqd_t create_mQue(char* que_name){
  mqd_t que;
  struct mq_attr *attr1;
  attr1 = malloc(sizeof(struct mq_attr));
  que = mq_open(que_name,O_CREAT,0666,NULL);
  if(que == -1){
    printf("Error");
    return 0;
  }
  //mq_getattr(que,attr1);
  //mq_receive(que,response,attr1->mq_msgsize,NULL);
  //  printf("\n %s \n",response);
  return que;
}

static int client_handler(union sigval sv){
  struct mq_attr attributes;
  ssize_t nr;
  char *buf;
  mqd_t messageQue_Destination = *((mqd_t *)sv.sival_ptr);
  
  mq_getattr(messageQue_Destination, &attributes);
  
  while(1){
    buf = malloc(attributes.mq_msgsize+1);
    mq_receive(messageQue_Destination,buf,attributes.mq_msgsize,NULL);
    printf("\n%s\n",buf);
    free(buf);
  }
}

extern int setup_client_handler(mqd_t messageQue_Destination){
  struct sigevent signal_event;

  signal_event.sigev_notify = SIGEV_THREAD;
  signal_event.sigev_notify_function = client_handler;
  signal_event.sigev_notify_attributes = NULL;
  signal_event.sigev_value.sival_ptr = &messageQue_Destination;

  mq_notify(messageQue_Destination, &signal_event);
}

extern int message_handling(char* que_name,char* message){
  mqd_t q;
  struct mq_attr *attributes;
  attributes = malloc(sizeof(struct mq_attr));
  q = mq_open(que_name,O_RDWR);
}
extern void write_to_file(char *file,char *line){
  FILE *fp;
  fp = fopen(file,"w");
  fprintf(fp,line);
  // fprintf(fp,"\n");
  fclose(fp);
}

/*
extern REQUEST message_received(char* MESSAGE){
  create_mQue("/registration",MESSAGE);
  return REQUEST = _REGISTER;
  }*/
