#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "string.h"


char*
fmtname(char *path)
{
  static char buf[DIRSIZ+1];
  char *p;

  // Find first character after last slash.
  for(p=path+strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;

  // Return blank-padded name.
  if(strlen(p) >= DIRSIZ)
    return p;
  memmove(buf, p, strlen(p));
  memset(buf+strlen(p), ' ', DIRSIZ-strlen(p));
  return buf;
}

int main(int argc,char* argv[])
{
    int fd;
    char
    if((fd==open(path,0))<0)
    {
        fprintf(2, "ls: cannot open %s\n", path);
        exit(-1);
    }

    exit(1);
}