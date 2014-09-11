#include "terminal_Server.h"

int main(int argc,char* argv[]){
  char *registered_User;
  registered_User = malloc(20*sizeof(char));

  create_mQue("/register",registered_User);
  write_to_file("registration.info",registered_User);
  mq_unlink("/register");
  return 0;
}
