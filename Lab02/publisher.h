//Fabio Fusaro 4068572
//Assignment 2: publisher.h

#include <iostream>
#include <unistd.h>
#include "logfile.h"

using namespace std;

class Publisher {
     
     private:
		int fdPub; // file descriptor of publisher
		int n; // number of publisher

     public:
     	Publisher();
     	~Publisher();
     	void publishChar(char letter, int fdPub, int n);
};

Publisher::Publisher() {
}

Publisher::~Publisher() {
}

void Publisher::publishChar(char letter, int fdPub, int n){

	int writePub;
	cout<<"Publisher"<<n<<" writing the character: "<<letter<<endl;

	// write the character on the publisher pipe
	writePub = write(fdPub, &letter, sizeof(letter));
	logFile("Publisher writes on its pipe the character: ");

	if (writePub <0){
		perror("Publisher writing error");
		exit(-1);
	}
}
