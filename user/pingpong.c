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
    char readmsg[20];
    
    int buildstatus = pipe(pipefd);
    
    if (buildstatus == -1){
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

    // parent process writes
    if (pid > 0) {
        write(pipefd[1], writemessages[0], sizeof(writemessages[0]));
        
    }
    //child process reads
    else if (pid == 0) {
        read(pipefd[0], readmsg, sizeof(readmsg));
        printf("%d Message from parent: %s\n",(int) getpid(), readmsg);
        
    }
    sleep(5);

    //child process writes
    if (pid == 0) {
        write(pipefd[1], writemessages[1], sizeof(writemessages[1]));    
        
    }
    //parent process reads
    else if (pid > 0) {
        read(pipefd[0], readmsg, sizeof(readmsg));
        printf("%d Message from child: %s\n", (int) getpid(), readmsg);

    }

    sleep (5);


    exit(1);
}
