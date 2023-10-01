#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"

int main()
{
    int p[2];
    //char *argv[2];
    char buf[13];
    //argv[0] = "echo";
    //argv[1] = 0;
    pipe(p);
    if(fork() == 0) {
        close(0);
        dup(p[0]);      
        close(p[0]);
        close(p[1]);
        read(p[0],buf,12);
        printf("recived %s \n",buf);
        
    } else {
        close(p[1]);
        write(p[1], "hello world\n", 12);
        close(p[1]);
    }
    return 0;
}       