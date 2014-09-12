IRC like server client using posix message ques.

Decided to take a whole new direction for this project.

For now, the way it works is you create or destroy a que by running:
./server "que_name" 

then attch to it with the client by:
./client "que_name"

Currently, the client and server can "function" in a sense. But the issue is
whoever runs the client first gets priority on the message que and thus no one else can see
any output. Will be remeding that soon...

For compilation:

compile client:

gcc -o client client.c terminal_Server.c -lrt

and server:

gcc -o server server.c terminal_Server.c -lrt


Once I get the basic functionality sorted out, we will be making a makefile to make all this easier, or at least a bash script


-Cheers!
