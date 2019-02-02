//Fabio Fusaro 4068572
//Assignment 2: mediator.h

#include <iostream>
#include <unistd.h>
#include <queue>
#include "logfile.h"

using namespace std;

class Mediator {
     
     private:
		int writeSub1;
		int writeSub2;
		int writeSub3;
		const int dim = 12; // assign the queues dimension
		queue<char> qSub1; // subscriber1 queue
		queue<char> qSub2; // subscriber2 queue
		queue<char> qSub3; // subscriber3 queue

     public:
     	Mediator();
		Mediator(int Sub1, int Sub2, int Sub3);
     	~Mediator();
		void addCharQueue(int pubNum, char letter);
		void writeToSub(int subNum);
};

Mediator::Mediator() {
}

Mediator::Mediator(int Sub1, int Sub2, int Sub3) {

	// assign file descriptor of subscriber
	writeSub1 = Sub1;
	writeSub2 = Sub2;
	writeSub3 = Sub3;
}

Mediator::~Mediator() {
}

void Mediator::addCharQueue(int pubNum, char letter){

	if (pubNum == 1){ // control which publisher to add character to respective queue subscriber

		if (qSub1.size() > dim) { // control the queue size 
			qSub1.pop(); // remove the element from queue
			qSub1.push(letter); // add the character to queue
		}

		else {
			qSub1.push(letter); // add the character to queue
		}

		if (qSub2.size() > dim) { // control the queue size 
			qSub2.pop(); // remove the element from queue
			qSub2.push(letter); // add the character to queue
		}
		else {
			qSub2.push(letter); // add the character to queue
		}
	}

	if (pubNum == 2) { // control which publisher to add character to respective queue subscriber

		if (qSub2.size()>dim){ // control the queue size 
			qSub2.pop(); // remove the element from queue
			qSub2.push(letter); // add the character to queue
		}

		else {
			qSub2.push(letter); // add the character to queue
		}

		if (qSub3.size() > dim) { // control the queue size 
			qSub3.pop(); // remove the element from queue
			qSub3.push(letter); // add the character to queue
		}

		else {
			qSub3.push(letter); // add the character to queue
		}
	}
}
	
void Mediator::writeToSub(int subNum){

	if (subNum == 1) { // control in which subscriber write

		if (!qSub1.empty()) { // control if the queue is not empty

			char lSub1 = qSub1.front(); // return the oldest character

			// write the character on the subscriber1
			int wSub1 = write(writeSub1, &lSub1, sizeof(lSub1));
			logFile("Mediator writes on subscriber1 pipe the character: ");

			if (wSub1 < 0) {
				perror("Mediator writing on subscriber1 error");
				exit(-1);
			}

			qSub1.pop(); // remove the element from queue
		}
	}

	if (subNum == 2) { // control in which subscriber write

		if (!qSub2.empty()) { // control if the queue is not empty

			char lSub2 = qSub2.front(); // return the oldest character

			// write the character on the subscriber2
			int wSub2 = write(writeSub2, &lSub2, sizeof(lSub2));
			logFile("Mediator writes on subscriber2 pipe the character: ");

			if (wSub2 < 0) {
				perror("Mediator writing on subscriber2 error");
				exit(-1);
			}

			qSub2.pop(); // remove the element from queue
		}
	}

	if (subNum == 3) { // control in which subscriber write

		if (!qSub3.empty()) { // control if the queue is not empty

			char lSub3 = qSub3.front(); // return the oldest character

			// write the character on the subscriber3
			int wSub3 = write(writeSub3, &lSub3, sizeof(lSub3));
			logFile("Mediator writes on subscriber3 pipe the character: ");

			if (wSub3 < 0) {
				perror("Mediator writing on subscriber3 error");
				exit(-1);
			}

			qSub3.pop(); // remove the element from queue
		}
	}
}

