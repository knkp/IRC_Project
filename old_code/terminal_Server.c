#include "terminal_Server.h"
#define handle_error(msg) \
  do { perror(msg); exit(-1); } while(0)



// handlers
void client_handler(union sigval sv){
  struct mq_attr attributes;
  char *buf;
  mqd_t mqdes = *((mqd_t *)sv.sival_ptr);
  if(mq_getattr(mqdes, &attributes)==-1){
    handle_error("mq_getattr");
  }

  while(1){
    buf = malloc(attributes.mq_msgsize+1);
    mq_receive(mqdes,buf,attributes.mq_msgsize,NULL);
    printf("\n%s\n",buf);
    free(buf);
  }
}

void server_handler(union sigval sv){
  struct mq_attr attributes;
  char *buf;
  mqd_t mqdes = *((mqd_t *)sv.sival_ptr);
  if(mq_getattr(mqdes, &attributes)==-1){
    handle_error("mq_getattr");
  }

  while(1){
    buf = malloc(attributes.mq_msgsize+1);
    mq_receive(mqdes,buf,attributes.mq_msgsize,NULL);
    printf("\n%s\n",buf);
    free(buf);
  }
}


// regular functions

void update_que(char *name, mqd_t *message_que){
  char *str = NULL;
  char *message = NULL;
  size_t len = 0;

  printf("\n Enter Message: \n");
  getline(&str, &len, stdin);
  message = malloc(strlen(name)*sizeof(char) + len*sizeof(char));
  snprintf(message,strlen(name),"%s",name);
  strcat(message,": ");
  strcat(message,str);
  //printf("\n this is the Q: %s\n", message_que);
  send_message(message_que,message);
  free(message);
}

void setup_que(char *argument, char **que, mqd_t *messageQue_descriptor){
  mqd_t descriptor;
  char *message_que = malloc(strlen(argument)*sizeof(char)+1);
  
  strcat(message_que,"/");
  strcat(message_que,argument);
  *que = malloc(strlen(message_que)*sizeof(char)+1);
  snprintf(*que,strlen(message_que)+1,"%s",message_que);
  descriptor = create_mQue(message_que);
  memcpy(messageQue_descriptor,&descriptor,sizeof(mqd_t));
  if(descriptor == (mqd_t)-1){
    handle_error("mq_open");
  }
}

void setup_user_account(char **name){
  size_t len = 0;
  char *buffer=NULL;

  printf("Enter your name: \n");
  getline(&buffer, &len,stdin);
  removeNewLine(buffer);
  //*name = malloc(strlen(buffer));
  //snprintf(*name,strlen(buffer),"%s",buffer);
   *name = buffer;
   // free(buffer);
}

mqd_t open_que(char *name, char *qname){
  mqd_t q_descriptor;
  qname = malloc((strlen(name)*sizeof(char))+1);
  strcat(qname, "/");
  strcat(qname, name);
  printf("\nopening q: %s\n",qname);
  q_descriptor = mq_open(qname,O_RDWR);
  if(q_descriptor == (mqd_t)-1){
    handle_error("mq_open");
  }
  return q_descriptor;
}

mqd_t setup_mque(char *name, char *message_que_name){
  message_que_name = malloc((strlen(name)*sizeof(char))+1);
  mqd_t q_descriptor;

  strcat(message_que_name, "/");
  strcat(message_que_name, name);
  printf("\n%s\n",message_que_name);
  q_descriptor = create_mQue(message_que_name);
  if(q_descriptor == (mqd_t)-1){
    handle_error("mq_open");
  }
  return q_descriptor;
}


void removeNewLine(char *value){
  int iterator;
  for(iterator = 0; iterator<sizeof(value);iterator++){
      if(value[iterator] == '\n'){
	value[iterator] = ' ';
      }
    }

}

int setup_handler(void (*func)(union sigval sv), mqd_t* message_que_descriptor){
  struct sigevent signal_event;

  signal_event.sigev_notify = SIGEV_THREAD;
  signal_event.sigev_notify_function = func;
  signal_event.sigev_notify_attributes = NULL;
  signal_event.sigev_value.sival_ptr = message_que_descriptor;

  if(mq_notify(*message_que_descriptor, &signal_event)==-1){
     handle_error("mq_notify");
  }
  return 0;
}

// create the stream for client/server interaction
struct SC_STREAM register_user(char *name){
  struct SC_STREAM message_Ques;
  char *receive_que;
  mqd_t mq = mq_open("/register",O_WRONLY);
  mqd_t mq_server;
  size_t size = strlen(name);
  mq_send(mq,name,size,1); // register this user with server
  mq_close("/register");
  message_Ques.server = mq_open("/server",O_WRONLY); //send messages to server to handle
  strcat(receive_que,"/");
  strcat(receive_que,name);
  message_Ques.client = mq_open(receive_que,O_RDONLY); //receive messages from server (all users)
  return message_Ques;
}



extern int send_message(mqd_t *que,char *message){
  mqd_t q1;
  size_t size = strlen(message)+1;
  //q1 = mq_open(que,O_RDWR);
  if(q1 == -1){
    printf("\n Error Opening Que \n");
    return -1;
  }
  mq_send(que,message,size,1);

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
  que = mq_open(que_name,O_RDONLY | O_CREAT,0666,NULL);
  if(que == -1){
    printf("Error");
    return 0;
  }
  //mq_getattr(que,attr1);
  //mq_receive(que,response,attr1->mq_msgsize,NULL);
  //  printf("\n %s \n",response);
  return que;
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
