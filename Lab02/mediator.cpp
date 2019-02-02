//Fabio Fusaro 4068572
//Assignment 2: mediator

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <errno.h> 
#include <signal.h>
#include <queue>
#include "mediator.h"

using namespace std;

int main(int argc, char *argv[])
{
	int req;

	//conversion of argv from char to integer for write and read
	int readPub1 = atoi(argv[1]);
	int readPub2 = atoi(argv[2]);
	int readSubReq1 = atoi(argv[3]);
	int readSubReq2 = atoi(argv[4]);
	int readSubReq3 = atoi(argv[5]);
	int writeSub1 = atoi(argv[6]);
	int writeSub2 = atoi(argv[7]);
	int writeSub3 = atoi(argv[8]);

	Mediator *mediator = new Mediator(writeSub1, writeSub2, writeSub3);
	cout<<"Executing mediator"<< endl;

	fd_set filesDescriptorSet; // file descriptors set creation

	while (true) {

		int selectState;

		// finding highest file descriptors integer
		int maxFd = -1;

		if(readPub1 > maxFd)
			maxFd = readPub1;

		if(readPub2 > maxFd) 
			maxFd = readPub2;
 
		if(readSubReq1 > maxFd)
			maxFd = readSubReq1;

		if(readSubReq2 > maxFd)
			maxFd = readSubReq2;

		if(readSubReq3 > maxFd)
			maxFd = readSubReq3;
		
		FD_ZERO(&filesDescriptorSet); // file descriptors set initialization

		// insert file descriptors in the set
		FD_SET(readPub1, &filesDescriptorSet);
		FD_SET(readPub2, &filesDescriptorSet);
		FD_SET(readSubReq1, &filesDescriptorSet);
		FD_SET(readSubReq2, &filesDescriptorSet);
		FD_SET(readSubReq3, &filesDescriptorSet);

		selectState = select(maxFd + 1, &filesDescriptorSet, NULL, NULL, NULL);

		if (selectState < 0) {
			perror ("select error mediator");
			return -1;
		}

		if(FD_ISSET(readPub1, &filesDescriptorSet)) { // control if the file descriptor is in the set

			//to write in queueSub1 and queueSub2
			char letter1;

			int rPub1 = read(readPub1, &letter1, sizeof(char));

			if (rPub1 < 0) {
				perror("Mediator reading from publisher error");
			}

			mediator->addCharQueue( 1, letter1);
		}

		if(FD_ISSET(readPub2, &filesDescriptorSet)) {

			//to write in queueSub2 and queueSub3
			char letter2;

			int rPub2 = read(readPub2, &letter2, sizeof(char));

			if(rPub2 < 0){
				perror("Mediator reading from publisher error");
			}

			mediator->addCharQueue( 2, letter2);
		}
		
		if(FD_ISSET(readSubReq1, &filesDescriptorSet)) {

			// read if there is a request in subscriber1
			int readReq = read (readSubReq1, &req, sizeof(int));
			logFile("Mediator reads from subscriber1 request pipe the request: ");

			if (readReq < 0) {
				perror ("Read error mediator on subscriber1 request");
				return -1;
			}

			mediator->writeToSub(1);			
		}

		if(FD_ISSET(readSubReq2, &filesDescriptorSet)) {
	
			// read if there is a request in subscriber2
			int readReq2 = read (readSubReq2, &req, sizeof(int));
			logFile("Mediator reads from subscriber2 request pipe the request: ");

			if (readReq2 < 0) {
				perror ("Read error mediator on subscriber2 request");
				return -1;
			}

			mediator->writeToSub(2);
		}

		if(FD_ISSET(readSubReq3, &filesDescriptorSet)) {

			// read if there is a request in subscriber3
			int readReq3 = read (readSubReq3, &req, sizeof(int));
			logFile("Mediator reads from subscriber2 request pipe the request: ");

			if (readReq3 < 0) {
				perror ("Read error mediator on subscriber2 request");
				return -1;
			}

			mediator->writeToSub(3);
		}
		
	}

	return 0;
}


