#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <errno.h> 
#include <signal.h>
#include <time.h> 

//This program create two processes: the first inputs an array of integer values from standard input sends to the second via pipe; the second process sorts the array and prints results.

void logFile(char *msgStatus) {
	FILE *f;
	f = fopen("logFileB.log", "a+");
	time_t currentTime;
	char* timeString;
	currentTime = time(NULL);
	timeString = ctime(&currentTime);
	fprintf(f, "%sPID %d. %s: %s\n", timeString, getpid(), msgStatus, strerror(errno));
	fclose(f);
} //function for the creation of the log file

int main(int argc, char *argv[])
{
	char readPipe[20]; //string for reading
	char writePipe[20]; //string for writing
	int fd[2]; //file descriptor 
	int pipeState, execState1, execState2;
	pid_t child1;
	pid_t child2;

	FILE *f;
	f = fopen("logFileB.log", "w");
	fclose(f);

	pipeState = pipe (fd);	//pipe creation
	logFile("Creation of the pipe: ");
	if (pipeState < 0) {
		perror("Pipe error");
		return -1;
	}

	//fd conversion from integer to string
	sprintf(readPipe, "%d", fd[0]);
	sprintf(writePipe, "%d", fd[1]);

	//string for function execve
	char *strInput[] = {"arrayInput", readPipe, writePipe, NULL};
	char *strOutput[] = {"arraySort", readPipe, writePipe, NULL};
	
	child1= fork(); 

	if (child1 != 0) {
		logFile("Creation of the child1: ");
	}
	
	if (child1 < 0) {
		perror 	("Fork error in child1");
		return -1;
	}
	
	else if (child1 == 0) { 

		execState1 = execve ("arrayInput", strInput, NULL);

		if (execState1 < 0) 
		{
			perror ("Execve error child1");
			return -1;
		}

		exit (EXIT_SUCCESS);
	}
	
	else {

		wait (NULL); //father waits the first child
		child2 = fork();

		if (child2 != 0) {
			logFile("Creation of the child2: ");
		}    

		if (child2 < 0) {
			perror ("Fork error in child2");
			return -1;
		}

		else if (child2 == 0) {

			execState2 = execve ("arraySort", strOutput, NULL);

    		if (execState2 < 0 ) {
				perror ("Execve error child2");
				return -1;
			}
		exit (EXIT_SUCCESS);
 		}
		
		else { 
			wait (NULL); //father waits the second child
		}
		
	}
	return 0;
}

