#include "Server_Manager.h"

int main(int argc, char* argv[]){
  int RUNNING = 1;

  initialize_socket_server();

  while(RUNNING){
    RUNNING = proc_events();
  }
  return 0;
}
