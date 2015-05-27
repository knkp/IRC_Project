#include "Client_Node.h"


int main(int argc, char* argv[]){
  int notQuit = 1;

  init_node_client();
  
  printf("got past the init function\n");

  while(notQuit){

    printf("made it into the while loop\n");

    notQuit = proc_events();

  }

  printf("got past the whie loop\n");

  return 0;

}
