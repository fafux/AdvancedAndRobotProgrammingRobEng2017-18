//Fabio Fusaro 4068572
//Assignment 2: subscriber2

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

	int numSub = 2; // number of subscriber
	
	//conversion of argv from char to integer for write and read
	int writeSubReq2 = atoi(argv[2]);
	int readSub2 = atoi(argv[1]);

	Subscriber subscriber;
	
	sleep(1);

	cout<<"Executing subscriber2"<< endl;

	while(true){

		sleep(2); // subscriber frequence

		subscriber.subscribeRequest(writeSubReq2, numSub);

		subscriber.subscribeReading(readSub2, numSub);

    }

	return 0;
}
