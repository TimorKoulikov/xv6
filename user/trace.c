#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"


int main(int argc,char* argv[])
{
    //int trace_num;
    char* xargs[MAXARG];
    if(argc<2){
        fprintf(2,"trace:not enought paramters\n");
        exit(-1);
    }
    if(trace(atoi(argv[1]))<0){
        fprintf(2,"trace:could not trace proc\n");
        exit(-1);
    }

    for(int i=2;i<argc;i++)
    {
        xargs[i-2]=argv[i];
    }
    
    if(fork()==0){
        exec(xargs[0],xargs);
    }
    wait(0);
    exit(1);   
}