// projectB.cpp
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <sys/wait.h>

using namespace std;

int main() {
    int fd[2];
    // Create the pipe
    if (pipe(fd) == -1) {
        cerr << "Pipe creation failed." << endl;
        return 1;
    }
    
    pid_t pid = fork();
    if (pid < 0) {
        cerr << "Fork failed." << endl;
        return 1;
    } else if (pid > 0) {
        // Parent process: send car data through the pipe.
        close(fd[0]); // Close the read end in the parent.
        const char* carData = "Car 1: Speed=70 mph; Car 2: Speed=65 mph; Car 3: Speed=80 mph";
        if (write(fd[1], carData, strlen(carData) + 1) == -1) {
            cerr << "Write to pipe failed." << endl;
        }
        close(fd[1]); // Close the write end after sending.
        wait(NULL);   // Wait for the child to finish.
    } else {
        // Child process: receive and display the car data.
        close(fd[1]); // Close the write end in the child.
        char buffer[256];
        if (read(fd[0], buffer, sizeof(buffer)) < 0) {
            cerr << "Read from pipe failed." << endl;
        } else {
            cout << "Child process received car data: " << buffer << endl;
        }
        close(fd[0]);
    }
    
    return 0;
}
