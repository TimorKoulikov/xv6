#include "kernel/fcntl.h"
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

//cant write 
#define SIZE_BUF 20 
int main()
{
    int p[2];
    char* buffer[SIZE_BUF]={0};
    pipe(p);
    //child sending info
    if(fork()==0)
    {
        write(p[1],"hello world!",SIZE_BUF);
        close(p[1]);


    }else{
    //parent reciving info
        read(p[0],buffer,SIZE_BUF);
        printf("recived %s\n",buffer);
    }
    close(p[0]);
    close(p[1]);
    exit(1);
}