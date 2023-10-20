#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

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

void find( char* dir_path, char* filename)
{
    int fd=0;
    char buf[512],*p;
    //char filename[512];   
    //char* dir_path;
    
    struct dirent de;
    struct stat st;
    

    //dir_path=argv[1];
    
    //memmove(filename,argv[2],strlen(argv[2]));
    //printf("find args:%s\n",dir_path);
    if((fd=open(dir_path,0))<0){
      fprintf(2,"find:cannot open   %s\n",dir_path);
    }
    if(fstat(fd, & st)<0){
      fprintf(2,"find:cannot stat %s\n",dir_path);
      close(fd);
      exit(-1);
    }

    switch(st.type){
    case T_DEVICE:
    case T_FILE:
      printf("%s \n",fmtname(dir_path));
      break;
    case T_DIR:
      if(strlen(dir_path)+1+DIRSIZ+1>sizeof buf){
        printf("find:directory path too long\n");
        break;
      }
      strcpy(buf,dir_path);
      p=buf+strlen(buf);
      *p++='/';
      while(read(fd,&de,sizeof(de))==sizeof(de)){
        if(de.inum == 0)
          continue;
      
         
        memmove(p, de.name, DIRSIZ);
        p[DIRSIZ] = 0;
        if(stat(buf, &st) < 0){
            printf("find: cannot stat %s\n", buf);
            continue;
        }
            if(st.type==T_DIR && *p!='.'){
              
              find(buf,filename);
            }else if(strcmp(p,filename)==0)   
              printf("%s\n",buf);
    }
      break;       
      }
}

int main(int argc,char* argv[])
{
    
    if(argc!=3){
      fprintf(2,"find:should be 2 arguments\n");
      exit(-1);
    }
    find(argv[1],argv[2]);
    exit(0);
}