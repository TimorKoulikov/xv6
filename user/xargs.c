#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"



int main(int argc,char* argv[])
{
    int p[2];
    char buf[512];
    char* cp;
    char command[512];
    if(argc<2){
        fprintf(2,"xargs: not enough arguments");
        exit(-1);
    }
    
    pipe(p);
    //child reads from pipe
    if(fork()==0){   
      close(p[0]);
      for(int i=1;i<argc;i++){
        write(p[1],argv[i],strlen(argv[i]));
        write(p[1]," ",1);

      }  
      close(p[1]);

    }else{//parent write into pipe
        close(0);
        dup(p[0]);
        close(p[0]);
        wait(0);
        read(0,buf,sizeof buf);
        
        cp=buf;
       // memmove(command,"/bin",4);
        //memset(command+4,'/',1);
        while(*cp!=' '){
            cp++;
        }
        memmove(command,buf,cp-buf);
        printf("xargs args:%s\n",command);
        exec(command,argv);
    }

    close(p[0]);
    close(p[1]);
    exit(1);
}