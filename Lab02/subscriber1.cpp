//Fabio Fusaro 4068572
//Assignment 2: subscriber1

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <errno.h> 
#include <signal.h>
#include "subscriber.h"

int main(int argc, char *argv[])
{

	int numSub = 1; // number of subscriber
	
	//conversion of argv from char to integer for write and read
	int writeSubReq1 = atoi(argv[2]);
	int readSub1 = atoi(argv[1]);

	Subscriber subscriber;
	
	sleep(1);

	cout<<"Executing subscriber1"<< endl;

	while(true){

		sleep(1); // subscriber frequence

		subscriber.subscribeRequest(writeSubReq1, numSub);

		subscriber.subscribeReading(readSub1, numSub);

    }

	return 0;
}
