#include "Client_Node.h"


static void removeNewLine(char *buffer){
  int iterator;
  for(iterator = 0; iterator < sizeof(buffer); iterator++){
    if(buffer[iterator] == '\n'){
      buffer[iterator] = ' ';
    }
  }
}


void init_node_client(){
  // struct CLIENT_CONFIG config;

  setup_configuration();

  // this function exists soley for the purpose's of testing,
  // normally it will connect only to socket_server and SS will pass
  // it where it needs to go -- Stephen
  connect_to_Authenticator();

  initial_communication();
}

void connect_to_Authenticator(){
  // create socket for authenticator
  node_connection = socket(AF_INET, SOCK_STREAM, 0);

  if(node_connection == -1){
    printf("Could not create auth socket\n");
  }
  // setup configurations for connection to authenticator
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = inet_addr("127.0.0.1");
  server.sin_port = htons( SOCKSERV_2_AUTH_PORT );
  // connect to authenticator

  int conn = connect(node_connection, (struct sockaddr *) &server, sizeof(server));
  if(conn < 0){
    printf("authentication failed\n");
    // return 2;
  }


}

void initial_communication(){

  // char message[200];
  bzero(&message, sizeof(message));

  message[0] = configuration.id;
  message[1] = configuration.eom;
    
    int n = send(node_connection, &message, sizeof(message), 0);
    
    if(n < 0){
       printf("write failed for some reason error: %d", errno); 
    }
    printf("communication sent\n");
    
}

int proc_events(){
  return 0;
}

void build_message(){
  
}


void get_name(){
  getline(&configuration.name, &configuration.name_size, stdin);
  removeNewLine(&configuration.name);
}

void setup_configuration(){
    configuration.id = DEFAULT;
    configuration.eom = EO_MESSAGE;
    configuration.delim = MESSAGE_DELIMITER;

    printf("Please enter your user name:\n");
    get_name();
  }
