//Fabio Fusaro 4068572
//Assignment 2: publisher2

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

	int numPub = 2; // number of publisher

	int writePub2= atoi(argv[1]); //conversion of argv from char to integer for write

	Publisher publisher;
    cout<<"Executing publisher2"<< endl;
    
    while(true){

		sleep(2); // publisher frequence

		char upperCaseChar = 'A' + rand()%26; // random upper case character

		publisher.publishChar(upperCaseChar, writePub2, numPub);

    }

	return 0;
}
