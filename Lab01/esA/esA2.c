//The second process send the first a signal that asks it to terminate.

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <errno.h> 
#include <signal.h>
#include <time.h> 

static int pidF, pidC;
pid_t child; //defined child process

void logFile(char *msgStatus) {
	FILE *f;
	f = fopen("logFileA2.log", "a+");
	time_t currentTime;
	char* timeString;
	currentTime = time(NULL);
	timeString = ctime(&currentTime);
	fprintf(f, "%sPID %d. %s: %s\n", timeString, getpid(), msgStatus, strerror(errno));
	fclose(f);
} //function for the creation of the log file

void segnale(int sig){
	if(sig==SIGUSR1){
		logFile("Receiving signal: ");
		printf ("I'm the father and I received the signal\n");
		kill(child,SIGKILL); //sending kill signal to child
		logFile("Father sent termination signal to child: ");
		printf("Father sent termination signal to child %d\n", child);
    }
}

int main()
{
	FILE *f;
	f = fopen("logFileA2.log", "w");
	fclose(f);

	child=fork();

	if (child != 0) {
		logFile("Creation of the child: ");
	}

	if (child < 0) {
		perror("Fork error");
		return -1;
	}

	if (child == 0) {

		pidC = getpid();
		pidF = getppid();
		printf("I'm child process %d with father %d\n", pidC, pidF);
		kill(pidF,SIGUSR1); //child asks father to terminate with sending signal
		logFile("Child sent signal to father asking termination: ");
		printf("Child sent signal to father %d asking termination\n", pidF);
	}
	else{

        if(signal(SIGUSR1,segnale) == SIG_ERR) { //father receives child signal
				printf("\ncan't catch signal\n");
			} 	
      	
		pause(); //father waits child signal

		return 0;
   }
           
}
