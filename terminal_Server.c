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

extern int create_mQue(char* que_name,char* response){
  mqd_t q2;
  struct mq_attr *attr1;
  attr1 = malloc(sizeof(struct mq_attr));
  q2 = mq_open(que_name,O_CREAT,0666,NULL);
  if(q2 == -1){
    printf("Error");
    return 0;
  }
  mq_getattr(q2,attr1);
  mq_receive(q2,response,attr1->mq_msgsize,NULL);
  //  printf("\n %s \n",response);
  return 1;
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
