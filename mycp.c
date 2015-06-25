//mycp program

//Demo implementation of command cat, display contents of a file 
//in standard output
//will edit things in later
#include <iostream>

#include <stdio.h>
//Need to include the following, required in order to use open
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
//Need to include this, in order to use system call exit
#include <unistd.h>

using namespace std;

int main(int argc, char * argv[])
{
   int i;
	
   if (argc!=3)
   {
	//This cout is C++, as it's an object (of ostream type)...

     cout <<"Usage: mycp src target\n";
	  _exit(1); // a system call to terminate the process (the execution of the program)
	 //, and return 1 to parent process
	 // use command man 2 exit to find out more
   }

	/*
	for(i=0; i<argc; argv[i]){
		printf("argument %d %s\n", i , argv[i]);
		}*/
	
	printf("mycp %s %s\n", argv[1], argv[2]);
	
   //1. make system call open to open source file (given by argv[1]) to read
   int src_fd; //file descriptor for source file 
	
   src_fd = open (argv[1], O_RDONLY);
        //O_RDONLY is a constant defined in one of the header files, meaning we 
	     // are open the file to read (not to modify it)
   
   //!!Always check return value when making system calls, and library calls, and any functions
   //!! The meaning of return valus is documented in the online manual 
   if (src_fd== -1) 
   {
		cout << "Fails to open " <<argv[1]<<" to read\n";
		_exit (1); 
   }

	int cp_fd; //file descriptor for destination file
	
	cp_fd = open (argv[2], O_WRONLY);

	if (cp_fd == -1){
		//if file doesn't exist, create new file (permission granted by mode)
		cp_fd = creat (argv[2], S_IRUSR);
	}
	
   //Read one byte a time from the file, and display the char on screen
   char buf;
	char response;
	
   while (read(src_fd, &buf, 1)==1)
   {
		write (cp_fd, &buf, 1);
		printf ("Press any key to continue:");
		scanf ("%c",&response);
   }

   //Always close the file descriptor, to deallocate os resource 
   close (src_fd);
	close (cp_fd);

}
