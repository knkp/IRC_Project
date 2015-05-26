#include "Client_Node.h"

int notQuit = 1;


int main(int argc, char* argv[]){

  init_node_client();

  while(notQuit){
    notQuit = proc_events();
  }

  return 0;

}
