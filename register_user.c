#include "terminal_Server.h"

int main(int argc, char*argv[]){
  send_message("/register",argv[1]);
  return 0;
}
