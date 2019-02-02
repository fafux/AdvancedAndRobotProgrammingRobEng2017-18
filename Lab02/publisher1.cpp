//Fabio Fusaro 4068572
//Assignment 2: publisher1

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <errno.h> 
#include <signal.h>
#include "publisher.h"

using namespace std;

int main(int argc, char* argv[])
{

	int numPub = 1; // number of publisher

	int writePub1= atoi(argv[1]); //conversion of argv from char to integer for write

	Publisher publisher;
    cout<<"Executing publisher1"<< endl;
    
    while(true){

		sleep(1); // publisher frequence

		char lowerChar = 'a' + rand()%26; // random lower case character

		publisher.publishChar(lowerChar, writePub1, numPub);

    }

	return 0;
}
