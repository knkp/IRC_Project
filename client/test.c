//#include "../old_code/terminal_Server.h"

#include "../old_code/terminal_Server.h"

void testAlgorithm(char *input, char *output);

int main(int argc, char *argv[]){
  //char *message = malloc(strlen(argv[1])*sizeof(char));
  //char *message;
  //copy_message_over(argv[1], message);
  char testString[45] = "yolo hello ./knkp . not be included";
  char *result;
  parse_message2(testString, &result);
  //const char delim[2] = ".";
  //char* token;
  /*
  printf("%s\n",testString);
  token = strtok(testString, delim);

  while(token!=NULL){
    printf("%s\n",token);
    token = strtok(NULL, delim);
  }*/
  //printf("input: %s\n", testString);
  //printf("output: %s\n", token);
  printf("%s\n",&result);
  printf("%c\n",&result[0]);
  return 0;
}

void testAlgorithm(char* input, char*output){
  const char delim[2] = ".";
  char* token;
  token = strtok(input, delim);
  token = strtok(NULL, delim);
  //printf("%s\n",token);
  //strcat(output, token);
  snprintf(output, strlen(token), "%s",token);
  return 0;
}
/*
int main()
{
  char str[80] = "This is - www.tutorialspoint.com - website";
  const char s[2] = "-";
  char *token;
   
  /* get the first token */
//token = strtok(str, s);
   
  /* walk through other tokens */
  /*while( token != NULL ) 
    {
      printf( " %s\n", token );
    
      token = strtok(NULL, s);
    }
   
  return(0);
}*/
