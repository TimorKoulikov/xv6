#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
int main(int argc,char* argv[])
{
    int fd=0;
    if(fd<3){
      fd=5;
    }

    exit(1);
}