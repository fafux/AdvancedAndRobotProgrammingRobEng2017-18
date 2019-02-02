#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <errno.h> 
#include <signal.h>
#include <time.h> 

//the first child inputs an array of integer values from standard input and sends to the second via pipe. After received from the second the sorted array and prints it;

void logFile(char *msgStatus) {
	FILE *f;
	f = fopen("logFileD.log", "a+");
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
	int wP2;
	int rP;
	int data, data2;

	//ask array dimension
	printf ("Insert the array length or 0 if you want to end: ");
	scanf ("%d", &n);

	if(n == 0) {
		kill(getppid(),SIGUSR1); //send termination signal to father
	}

	else {

	int arrayInput[n+1];
	arrayInput[0] = n;

	int arrayOutput[n];
	
	//conversion of argv from char to integer to write 
	wP2 = atoi(argv[2]);
	rP = atoi(argv[1]);

  	//creation array from input
	for (i = 1; i < n+1 ; i++) {
		printf ("Insert an integer:\n");
		scanf ("%d", &arrayInput[i]);
	}
	
	data = write(wP2, &arrayInput, sizeof(arrayInput)); //write on pipe 2
	logFile("Writing on pipe 2 the array: ");

	if (data < 0) {
		perror("Write error");
		return -1;
	}

 	close (wP2); //file for writing closed

	//read from pipe 1
	for (i = 0; i < n; i++) {
		data2 = read(rP, &arrayOutput[i], sizeof(int));
		if (data2 < 0) { //if readed value is not valid
			perror("Reading error");
			return -1;
		}
	}

	logFile("Reading from pipe 1 the array: ");

	close (rP); //file for reading closed

	//print the sort array
	printf( "The sorted array is: \n");
	for (i = 0; i < n; i++) {
		printf("%d \n", arrayOutput[i]);
	}

	}


	exit (EXIT_SUCCESS);
}
