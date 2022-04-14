#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void
main()
{
    int pipefds[2];
    int pid;
    char writemessages[2][20]={"Hi", "Hello"};
    char readmessage[20];
    
    int returnstatus = pipe(pipefds);
    
    if (returnstatus == -1){
        printf("Unable to create pipe\n");
    }
    else{
        printf("Successfully established a single pipe.\n");
    }

    pid = fork();

    // Child process
    if (pid == 0) {
        read(pipefds[0], readmessage, sizeof(readmessage));
        printf("Message received by child from parent is: %s\n", readmessage);
        //read(pipefds[0], readmessage, sizeof(readmessage));
        // printf("Child Process - Reading from pipe - Message 2 is %s\n", readmessage);
    } 
    else { //Parent process
        printf("Message from Parent - %s\n", writemessages[0]);
        write(pipefds[1], writemessages[0], sizeof(writemessages[0]));
        // printf("Parent Process - Writing to pipe - Message 2 is %s\n", writemessages[1]);
        // write(pipefds[1], writemessages[1], sizeof(writemessages[1]));
    }


    exit(0);
}
