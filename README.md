So, here's the basic run down. 

The major goal of this project is basically just a server system 
that will allow multiple users who may be remotely logged onto a 
linux based system via ssh to communicate to eachother as if they 
were using an IRC. Eventually we want this to be able to expand 
over several machines but act as if it was still on one to the end 
user. I also have plans for using this to control some home-automation 
related machines

This has a ridiculous amount of work that it needs before I would 
even be remotely proud to say that I've worked on it and I've been 
experimenting with different APIs to see which one's I like better 
for multi-threading and FIFO's and what-not. But I think I should 
build at least some basic functionality for the intial commit. So 
for now: terminal_Server.h is worth going through to see some of 
the basic functions available right now. There's not much but it's 
something - still deciding on how I want the design to look so it's 
neat when it's finished. 

testServer.c once compiled and run will create a message que and 
will block until a transmission take's place. Once it does, it 
writes the contents of the message to a local file and then 
shutsdown.

register_user.c takes the first argument and simply transmits it as 
a string to the message que created by testServer.c, so be sure to
run it after you have the server running.

when compiling these files you must link with the real-time library 
and the source code for the header are needed so for example:

gcc -o server testServer.c terminal_Server.c -lrt

"-lrt" specifies that you are linking with the real time library 
environment. (see the man page's for message ques, start with 
mq_overview if you want the basic run down)

I hope it is intuitive from there.
