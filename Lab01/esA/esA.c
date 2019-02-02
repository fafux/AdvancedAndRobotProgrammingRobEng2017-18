//Create two processes. The first waits until the second dies and returns an exit status from it.

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <time.h>
#include <errno.h>
#include <string.h>

void logFile(char *msgStatus) {
	FILE *f;
	f = fopen("logFileA.log", "a+");
	time_t currentTime;
	char* timeString;
	currentTime = time(NULL);
	timeString = ctime(&currentTime);
	fprintf(f, "%sPID %d. %s: %s\n", timeString, getpid(), msgStatus, strerror(errno));
	fclose(f);
} //function for the creation of the log file

static int counter;

static void body(const char *s){
int i;
for (i = 0; i < 5; i++) {
    printf("%s: %d\n", s, counter++);
}
}

int main(int argc, char *argv[]){
pid_t child; //defined child process
counter = 5;
FILE *f;
f = fopen("logFileA.log", "w");
fclose(f);
child = fork();
if (child != 0) {
	logFile("Creation of the child: ");
}
if (child < 0) {
    perror("Fork error");
    return -1;
}
if (child == 0) {
    body("Child"); //print child body
    return 0;
}
wait(NULL); //waiting the complete end of the child
logFile("Father waits the complete end of the child: ");
body("Father"); //print father body
return 0;
}
