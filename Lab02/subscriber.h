//Fabio Fusaro 4068572
//Assignment 2: subscriber.h

#include <iostream>
#include <unistd.h>
#include <time.h>
#include "logfile.h"

using namespace std;

class Subscriber {
     
     private:
	    int fdSub; // file descriptor of subscriber
		int fdSubReq; // file descriptor of subscriber request
		int n; // number of subscriber
		int num; // number of subscriber

     public:
     	Subscriber();
     	~Subscriber();
     	void subscribeRequest(int fdSubReq, int n);
		void subscribeReading(int fdSub, int num);
};

Subscriber::Subscriber() {
}

Subscriber::~Subscriber() {
}

void Subscriber::subscribeRequest(int fdSubReq, int n){

	int writeSubReq;

	int nReq = 1; // assign 1 to the sending of the request
		
	// write the request on the subscriber request pipe
	writeSubReq = write(fdSubReq, &nReq, sizeof(nReq));
	logFile("Subscriber writes on request pipe the request: ");

	if (writeSubReq <0){
		perror("Subscriber request error");
		exit(-1);
	}

	cout<<"Subscriber"<<n<<" writing request"<< endl;

}

void Subscriber::subscribeReading(int fdSub, int num){

	int readSub;
	char letter;

	cout<<"Accepted subscriber"<<num<<" request"<< endl;
	
	// read the character from subscriber pipe
	readSub = read(fdSub, &letter, sizeof(char));
	logFile("Subscriber reads on its pipe the character: ");

	if (readSub <0){
		perror("Subscriber reading error");
		exit(-1);
	}

	cout<<"Subscriber"<<num<<" reading the character: "<<letter<< endl;
	
}
