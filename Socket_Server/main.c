
int main(int argc, char *argv[]){

  if(init_authenticator_connection() == -1){
    return 1;
  }

  if(init_main_handler() == -1){
    return 2;
  }

  while(1){
    handle_incoming_connections();
  }
  return 0;
}


