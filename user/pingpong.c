#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void
main()
{
    int pipefd[2]; 
    //pipefd[0] - read end
    //pipefd[1] - write

    int pid;
    char writemessages[2][20]={"Hi", "Hello"};
    char readmessage[20];
    
    int returnstatus = pipe(pipefd);
    
    if (returnstatus == -1){
        printf("Unable to create pipe\n");
        exit(0);
    }
    else{
        printf("Successfully established a single pipe.\n\n");
    }

    pid = fork();
    if (pid < 0){
        printf("fork unsuccessful.");
        exit(0);
    }

    // parent process
    if (pid > 0) {
        close(pipefd[0]);
        write(pipefd[1], writemessages[0], sizeof(writemessages[0]));
        close(pipefd[1]);
        
        //printf("Child reading msg : %s\n", readmessage);
        // read(pipefd[0], readmessage, sizeof(readmessage));
        // printf("Child Process - Reading from pipe - Message 2 is %s\n", readmessage);
        // printf("Child write - Message %s\n",writemessages[1]);
        // write(pipefd[0], writemessages[1], sizeof(writemessages[1]));
    }
    //child process
    else if (pid == 0) {
        close(pipefd[1]);
        read(pipefd[0], readmessage, sizeof(readmessage));
        close(pipefd[0]);
        printf("Message from parent: %s\n\n", readmessage);
        
        
        // printf("Message from parent : %s\n", writemessages[0]);
        //write(pipefd[1], writemessages[0], sizeof(writemessages[0]));
        //close(pipefd[1]);
        // wait(6);
        // printf("Parent Process - Writing to pipe - Message 2 is %s\n", writemessages[1]);
        // write(pipefd[1], writemessages[1], sizeof(writemessages[1]));
    }
    wait(10*);
    if (pid == 0) {
        close(pipefd[0]);
        write(pipefd[1], writemessages[1], sizeof(writemessages[1]));
        close(pipefd[1]);      
        
    }
    //child process
    else if (pid > 0) {
        close(pipefd[1]);
        read(pipefd[0], readmessage, sizeof(readmessage));
        close(pipefd[0]);
        printf("Message from child: %s\n", readmessage);
        
        // printf("Message from parent : %s\n", writemessages[0]);
        //write(pipefd[1], writemessages[0], sizeof(writemessages[0]));
        //close(pipefd[1]);
        // wait(6);
        // printf("Parent Process - Writing to pipe - Message 2 is %s\n", writemessages[1]);
        // write(pipefd[1], writemessages[1], sizeof(writemessages[1]));
    }

 


    exit(1);
}
