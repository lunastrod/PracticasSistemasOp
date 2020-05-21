#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

const char NAME[] = "filterin";
const char EXEC_ERROR[] = "command not found";
const char FORK_ERROR[] = "can't fork";
const char PIPE_ERROR[] = "pipe error";
const char USAGE_ERROR[] = "usage: filterin regexp command [args]";

const char * PATH[] = {"/bin", "/usr/bin"};
enum{
  N_PATHS=2,
  MAX_PATH_SIZE=100
};

int search_command_path(char * name, char * path, int size){
  int i;
  int found=0;

  for(i=0;i<N_PATHS;i++){
    snprintf(path,size,"%s/%s",PATH[i],name);
    //printf("%s\n",path);
    if(access(path,X_OK)==0){
      found=1;
      break;
    }
  }
  return found;
}

pid_t exec_command(char * path, char ** args, int input[2], int output[2]){
  pid_t child_pid=fork();
  switch(child_pid){
    case 0:
      if(input!=NULL){
        close(input[1]);//close output of input pipe
        close(0);//Close stdin
        dup2(input[0],0);//Duplicate the input side of input pipe to stdin
      }

      if(output!=NULL){
        close(output[0]);//close input of output pipe
        close(1);//Close stdout
        dup2(output[1],1);//Duplicate the out side of output pipe to stdout
      }
      execv(path, args);
      fprintf(stderr, "[%s]:'%s' %s\n", NAME, path, EXEC_ERROR);
      exit(EXIT_FAILURE);
    case -1:
      fprintf(stderr, "[%s]: %s\n", NAME, FORK_ERROR);
      exit(EXIT_FAILURE);
  }
  return child_pid;
}

int wait_command(pid_t pid){
  int status;
  waitpid(pid,&status,0);
  return status;
}

int main(int argc, char * argv[]){
  if(argc<3){
    fprintf(stderr, "[%s]: %s\n", NAME, USAGE_ERROR);
    exit(EXIT_FAILURE);
  }
  //fprintf(stderr,"start\n");
  char * regexp=argv[1];
  char ** child_args=&argv[2];
  char * child_name=child_args[0];


  //searching path
  char * child_path=malloc(MAX_PATH_SIZE);
  if(search_command_path(child_name, child_path, MAX_PATH_SIZE)==0){
    fprintf(stderr, "[%s]:'%s' %s\n", NAME, child_name, EXEC_ERROR);
    exit(EXIT_FAILURE);
  }
  //fprintf(stderr,"path\n");


  //opening pipes
  int p1[2];//pipe from here to child
  int p2[2];//pipe from child to here
  if(pipe(p1) < 0||pipe(p2) < 0){
    fprintf(stderr, "[%s]: %s\n", NAME, PIPE_ERROR);
    exit(EXIT_FAILURE);
  }
  //fprintf(stderr,"pipe\n");

  //fork
  pid_t child_pid=exec_command(child_path,child_args,p1,p2);

  char readbuffer[1000];
  read(0, readbuffer, sizeof(readbuffer));//read from stdin

  //writing in the pipe
  close(p1[0]);//close input
  //printf("Sent string: %s", readbuffer);
  write(p1[1], readbuffer, strlen(readbuffer)+1);
  close(p1[1]);//close output

  //filtering output
  char * grep_args[]={"grep","-E","--text",regexp,NULL};
  pid_t grep_pid=exec_command("/bin/egrep",grep_args,p2,NULL);


  wait_command(child_pid);
  close(p2[1]);
  wait_command(grep_pid);
  exit(EXIT_SUCCESS);

}
