#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <errno.h> 
#include <signal.h>
#include <time.h> 


//the first child inputs an array of integer values from standard input and sends to the second via pipe;

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

int main (int argc, char *argv[])
{
	int i,n;
	int wP,rP;
	int data;

	//ask array dimension
	printf ("Insert the array length: ");
	scanf ("%d", &n);

	int arrayInput[n+1];
	arrayInput[0] = n;
	
	//conversion of argv from char to integer to write 
	wP = atoi(argv[2]);
	rP = atoi(argv[1]);

  	//creation array from input
	for (i = 1; i < n+1 ; i++) {
		printf ("Insert an integer:\n");
		scanf ("%d", &arrayInput[i]);
	}

	close(rP); //file for reading closed
	
	data = write(wP, arrayInput, sizeof(arrayInput)); //write on pipe
	logFile("Writing the array: ");

	if (data < 0) { //if readed value is not valid
		perror("Write error\n");
		return -1;
	}

 	close (wP); //file for writing closed
	exit (EXIT_SUCCESS);
}
