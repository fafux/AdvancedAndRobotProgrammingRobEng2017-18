//Fabio Fusaro 4068572
//Assignment 2: init

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <errno.h> 
#include <signal.h>
#include "logfile.h"

int main(int argc, char *argv[])
{

	FILE *f;
	f = fopen("logFile.log", "w");
	fclose(f);

	pid_t publisher1;
    pid_t publisher2;
    pid_t mediator; 
    pid_t subscriber1;
    pid_t subscriber2;
    pid_t subscriber3;

	int pipeState, pipeState2, pipeState3, pipeState4, pipeState5, pipeState6, pipeState7, pipeState8;
	int execState, execState2, execState3, execState4, execState5, execState6;

	int fdPub1[2]; //publisher1 file descriptor
	int fdPub2[2]; //publisher2 file descriptor
	int fdSub1[2]; //subscriber1 file descriptor
	int fdSub2[2]; //subscriber2 file descriptor
	int fdSub3[2]; //subscriber3 file descriptor
	int fdSubReq1[2]; //subscriber1 request file descriptor
	int fdSubReq2[2]; //subscriber2 request file descriptor
	int fdSubReq3[2]; //subscriber3 request file descriptor

	pipeState = pipe (fdPub1); //publisher1 pipe creation
	logFile("Creation of the publisher1 pipe: ");
	if (pipeState < 0) {
		perror("Publisher1 pipe error");
		return -1;
	}

	pipeState2 = pipe (fdPub2); //publisher2 pipe creation
	logFile("Creation of the publisher2 pipe: ");
	if (pipeState2 < 0) {
		perror("Publisher2 pipe error");
		return -1;
	}

	pipeState3 = pipe (fdSub1); //subscriber1 pipe creation
	logFile("Creation of the subscriber1 pipe: ");
	if (pipeState3 < 0) {
		perror("Subscriber1 pipe error");
		return -1;
	}

	pipeState4 = pipe (fdSub2); //subscriber2 pipe creation
	logFile("Creation of the subscriber2 pipe: ");
	if (pipeState4 < 0) {
		perror("Subscriber2 pipe error");
		return -1;
	}

	pipeState5 = pipe (fdSub3); //subscriber3 pipe creation
	logFile("Creation of the subscriber3 pipe: ");
	if (pipeState5 < 0) {
		perror("Subscriber3 pipe error");
		return -1;
	}

	pipeState6 = pipe (fdSubReq1); //subscriber1 request pipe creation
	logFile("Creation of the subscriber1 request pipe: ");
	if (pipeState6 < 0) {
		perror("Subscriber1 request pipe error");
		return -1;
	}

	pipeState7 = pipe (fdSubReq2); //subscriber2 request pipe creation
	logFile("Creation of the subscriber2 request pipe: ");
	if (pipeState7 < 0) {
		perror("Subscriber2 request pipe error");
		return -1;
	}

	pipeState8 = pipe (fdSubReq3); //subscriber3 request pipe creation
	logFile("Creation of the subscriber3 request pipe: ");
	if (pipeState8 < 0) {
		perror("Subscriber3 request pipe error");
		return -1;
	}

	publisher1= fork();

	if (publisher1 != 0) {
		logFile("Creation of the publisher1: ");
	} 
	
	if (publisher1 < 0) {
		perror 	("Fork error in publisher1");
		return -1;
	}
	
	else if (publisher1 == 0) { 

		char writePipePub1[20]; //string for writing
		sprintf(writePipePub1, "%d", fdPub1[1]); //fd conversion from integer to string

		//string for function execve
		char *strWritePub1[3]; 
		strWritePub1[0] = "publisher1";
		strWritePub1[1] = writePipePub1; 
		strWritePub1[2] = NULL;

		execState = execve ("publisher1", strWritePub1, NULL);
		logFile("Execution of publisher1: ");

		if (execState < 0) 
		{
			perror ("Execve error publisher1");
			return -1;
		}


		exit (EXIT_SUCCESS);
	}
	
	else {


		publisher2 = fork();

		if (publisher2 != 0) {
			logFile("Creation of the publisher2: ");
		}

		if (publisher2 < 0) {
			perror ("Fork error in publisher2");
			return -1;
		}

		else if (publisher2 == 0) {

			char writePipePub2[20]; //string for writing
			sprintf(writePipePub2, "%d", fdPub2[1]); //fd conversion from integer to string

			//string for function execve
			char *strWritePub2[3];
			strWritePub2[0] = "publisher2";
			strWritePub2[1] = writePipePub2; 
			strWritePub2[2] = NULL;

			execState2 = execve ("publisher2", strWritePub2, NULL);
			logFile("Execution of publisher2: ");

			if (execState2 < 0) 
			{
				perror ("Execve error publisher2");
				return -1;
			}


			exit (EXIT_SUCCESS);
 		}
		
		else { 
			
			mediator=fork();

			if (mediator != 0) {
				logFile("Creation of the mediator: ");
			}

			if (mediator < 0) {
				perror ("Fork error in mediator");
				return -1;
			}

			else if (mediator==0) {
				
				// strings for writing and reading
				char readPipePub1[20];
				char readPipePub2[20];
				char readPipeSubReq1[20];
				char readPipeSubReq2[20];
				char readPipeSubReq3[20];
				char writePipeSub1[20];
				char writePipeSub2[20];
				char writePipeSub3[20];

				//fd conversion from integer to string
				sprintf(readPipePub1, "%d", fdPub1[0]);
				sprintf(readPipePub2, "%d", fdPub2[0]);
				sprintf(readPipeSubReq1, "%d", fdSubReq1[0]);
				sprintf(readPipeSubReq2, "%d", fdSubReq2[0]);
				sprintf(readPipeSubReq3, "%d", fdSubReq3[0]);
				sprintf(writePipeSub1, "%d", fdSub1[1]);
				sprintf(writePipeSub2, "%d", fdSub2[1]);
				sprintf(writePipeSub3, "%d", fdSub3[1]);

				//string for function execve
				char *strMediator[10];
				strMediator[0] = "mediator";
				strMediator[1] = readPipePub1;
				strMediator[2] = readPipePub2;
				strMediator[3] = readPipeSubReq1;
				strMediator[4] = readPipeSubReq2;
				strMediator[5] = readPipeSubReq3;
				strMediator[6] = writePipeSub1;
				strMediator[7] = writePipeSub2;
				strMediator[8] = writePipeSub3;
				strMediator[9] = NULL;

				execState3 = execve ("mediator", strMediator, NULL);
				logFile("Execution of mediator: ");

				if (execState3 < 0) 
				{
					perror ("Execve error mediator");
					return -1;
				}

			}

			else {
				
				subscriber1 = fork();

				if (subscriber1 != 0) {
					logFile("Creation of the subscriber1: ");
				}

				if (subscriber1 < 0) {
					perror ("Fork error in subscriber1");
					return -1;
				}

				else if (subscriber1==0) {

					// strings for writing and reading
					char readPipeSub1[20];
					char writePipeSubReq1[20];

					//fd conversion from integer to string
					sprintf(readPipeSub1, "%d", fdSub1[0]);
					sprintf(writePipeSubReq1, "%d", fdSubReq1[1]);

					//string for function execve
					char *strSub1[4]; 
					strSub1[0] = "subscriber1";
					strSub1[1] = readPipeSub1;
					strSub1[2] = writePipeSubReq1;
					strSub1[3] = NULL;

					execState4 = execve ("subscriber1", strSub1, NULL);
					logFile("Execution of subscriber1: ");

					if (execState4 < 0) 
					{
						perror ("Execve error subscriber1");
						return -1;
					}


					exit (EXIT_SUCCESS);
			}

			else {
				
				subscriber2 = fork();

				if (subscriber2 != 0) {
					logFile("Creation of the subscriber2: ");
				}

				if (subscriber2 < 0) {
					perror ("Fork error in subscriber2");
					return -1;
				}

				else if (subscriber2==0) {

					// strings for writing and reading
					char readPipeSub2[20];
					char writePipeSubReq2[20];

					//fd conversion from integer to string
					sprintf(readPipeSub2, "%d", fdSub2[0]);
					sprintf(writePipeSubReq2, "%d", fdSubReq2[1]);

					//string for function execve
					char *strSub2[4]; 
					strSub2[0] = "subscriber2";
					strSub2[1] = readPipeSub2;
					strSub2[2] = writePipeSubReq2;
					strSub2[3] = NULL;

					execState5 = execve ("subscriber2", strSub2, NULL);
					logFile("Execution of subscriber2: ");

					if (execState5 < 0) 
					{
						perror ("Execve error subscriber2");
						return -1;
					}


					exit (EXIT_SUCCESS);
			}

			else {
				
				subscriber3 = fork();

				if (subscriber3 != 0) {
					logFile("Creation of the subscriber3: ");
				}

				if (subscriber3 < 0) {
					perror ("Fork error in subscriber3");
					return -1;
				}

				else if (subscriber3==0) {

					// strings for writing and reading
					char readPipeSub3[20];
					char writePipeSubReq3[20];

					//fd conversion from integer to string
					sprintf(readPipeSub3, "%d", fdSub3[0]);
					sprintf(writePipeSubReq3, "%d", fdSubReq3[1]);

					//string for function execve
					char *strSub3[4]; 
					strSub3[0] = "subscriber3";
					strSub3[1] = readPipeSub3;
					strSub3[2] = writePipeSubReq3;
					strSub3[3] = NULL;

					execState6 = execve ("subscriber3", strSub3, NULL);
					logFile("Execution of subscriber3: ");

					if (execState6 < 0) 
					{
						perror ("Execve error subscriber3");
						return -1;
					}


					exit (EXIT_SUCCESS);
			}

			else {

				wait (NULL); //father waits the childs
			}
	}
	}
	}
	}
	}

	return 0;
}

