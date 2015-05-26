#include "Client_Node.h"

//int notQuit = 1;

void init_node_client(){
  // this function exists soley for the purpose's of testing,
  // normally it will connect only to socket_server and SS will pass
  // it where it needs to go -- Stephen C
  connect_to_Authenticator();
  initial_communication();
}

void connect_to_Authenticator(){


}

void initial_communication(){

}

int proc_events(){
  return 1;
}
