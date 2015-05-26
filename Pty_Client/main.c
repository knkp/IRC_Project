#include "Client_Node.h"


int main(int argc, char* argv[]){
  int notQuit = 1;

  init_node_client();

  while(notQuit){
    notQuit = proc_events();
  }

  return 0;

}
