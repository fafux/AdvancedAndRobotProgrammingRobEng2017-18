//Fabio Fusaro 4068572
//Assignment 2: subscriber3

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
	
	int numSub = 3; // number of subscriber

	//conversion of argv from char to integer for write and read
	int writeSubReq3 = atoi(argv[2]);
	int readSub3 = atoi(argv[1]);

	Subscriber subscriber;
	
	sleep(1);

	cout<<"Executing subscriber3"<< endl;

	while(true){

		sleep(3); // subscriber frequence

		subscriber.subscribeRequest(writeSubReq3, numSub);

		subscriber.subscribeReading(readSub3, numSub);


    }

	return 0;
}
