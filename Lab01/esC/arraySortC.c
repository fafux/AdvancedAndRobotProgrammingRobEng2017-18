#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <errno.h> 
#include <signal.h>
#include <time.h> 


//the second child sorts the array and sends to first the sorted array.

int funcSort (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

void logFile(char *msgStatus) {
	FILE *f;
	f = fopen("logFileC.log", "a+");
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
	int rP2, wP;
	int data, data2;

	//conversion of argv from char to integer to read
	rP2 = atoi(argv[1]);
	wP = atoi(argv[2]);

	read(rP2, &n, sizeof(int)); //read from pipe 2 the size of array
	logFile("Reading from pipe 2 the size of array: ");

	int arrayInput[n];

	//read from pipe 2
	for (i = 0; i < n; i++) {
		data = read(rP2, &arrayInput[i], sizeof(int));
		if (data < 0) { //if readed value is not valid
			perror("Reading error");
			return -1;
		}
	}

	logFile("Reading from pipe 2 the array: ");

	close(rP2);//file for reading closed

	qsort(&arrayInput, n, sizeof(int), funcSort); //sort the array

	data2 = write(wP, &arrayInput, sizeof(arrayInput)); //write on pipe 1
	logFile("Writing on pipe 1 the array: ");
	
	if (data2 < 0) { //if readed value is not valid
		perror("Writing error");
		return -1;
	}

 	close (wP); //file for writing closed

	exit (EXIT_SUCCESS);
}
