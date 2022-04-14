#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void
main()
{
    int pipefds[2];
    int pid;

    int returnstatus = pipe(pipefds);
    exit(0);
}
