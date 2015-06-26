#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <iostream>
#include<ctype.h>
using namespace std;

const int MAX_LINE_LEN=1024; //each command line is at most 1023 character long
const int WORD_LEN=51; //each word in the command line is at most 50 character long
const int MAX_WORD_NUM=20; //each command has at most 20 words in it ...

int main(int argc, char* argv[])
{
	pid_t  pid;
	char * pwd, * host, * usr;
	char cmdline[MAX_LINE_LEN];
	int length, ret;
	int count = 0;
	
	//Calling getenv to find the current values of envrironment variables
	pwd = getenv ("PWD");
	host = getenv ("HOSTNAME");
	usr = getenv ("USER");
	
	while (1)
	{
		//Todo: Generate a prompt message similar to bash,
		//  using some other character for $  to end,
		//  and using () instead of []
		// Print out the prompt message:
		
		cout <<"(" << usr <<"@"<<host<<" "<<pwd<<")% ";

		cin.getline (cmdline,256);
		
		char * Word[MAX_WORD_NUM]; //an array of pointer to char ...
		
//


// break cmd lines into an array of words,
		//    ignoring anything starting from character # (if any)
		// You can assume diffrent words (command line arguments) are always separated by space
		//   (you can use function strlen(cmdline) to get the length of a C string...)
		//  You need to split the cmdline into multiple words, each word is an argument
		//       1) Relace space by \0 (terminating char)
		//       2)  use Word[0] to point to the first char of the first word,
		//      use Word[1] to point to the first char of the second word,
		//       use word[2] to ............................... third word,
		//       ...
		//       use NULL to indicate the end of Word array.

		//   we assume the whole cmdline is a single word
//Word[0] points to cmdline

		length = strlen(cmdline);

		Word[0] = cmdline;
		
		
		if(cmdline[0] == '#'){
			exit(1);
		}

		for(int i = 0; i < length; i++){
			
			if(cmdline[i] == ' '){
				cmdline[i] = '\0';
				count++;
				Word[count] = &(cmdline[i+1]);
				
			}
			
		}	

		count++;

		Word[count] = NULL; //We use NULL to indidate this is the last

		
//entry in this array of pointers...
		
		
		if (!strcmp (cmdline,"exit"))
			exit(0);		
		/* create a child process */
		pid = fork();
		if (pid < 0) { /* error occurred */
			fprintf(stderr, "Fork Failed");
			exit(-1);
		}
		else if (pid == 0) { /* child process */
			//printf ("Child process ...\n");

			//Todo: checking return value of execvp...
			ret = execvp(Word[0], Word);

			cout << "Error executing"<< Word[0] <<endl;
			
			
			exit(1);
		}
		else { /* parent process */
			/* parent will wait for the child to complete */
			wait (NULL);
			//printf ("Child Complete");
		}
	}
}
