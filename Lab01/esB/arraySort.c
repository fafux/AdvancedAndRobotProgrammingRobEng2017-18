#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <errno.h> 
#include <signal.h>
#include <time.h> 


//the second child sorts the array and prints results.

int funcSort (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

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
	int i, n;
	int rP, wP;
	int buffer;

	//conversion of argv from char to integer to read
	rP = atoi(argv[1]);
	wP = atoi(argv[2]);

	close(wP); //file for writing closed

	read(rP, &n, sizeof(int)); //read size of array
	logFile("Reading the size of array: ");

	int arrayInput[n];

	//read from pipe
	for (i = 0; i < n; i++) {
		buffer = read(rP, &arrayInput[i], sizeof(int));
		if (buffer < 0) { //if readed value is not valid
			perror("Reading error");
			return -1;
		}
	}

	logFile("Reading the array: ");

	close(rP);//file for reading closed

	qsort(arrayInput, n, sizeof(int), funcSort); //sort the array

	//print the sort array
	printf( "The sorted array is:\n");
	for (i = 0; i < n; i++) {
		printf("%d \n", arrayInput[i]);
	}
	exit (EXIT_SUCCESS);
}
