#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void lowercase(char * str){
  for(int i=0; str[i]!='\0'; i++){
    if(str[i]>='A'&&str[i]<='Z'){//if uppercase
      str[i]=str[i]+('a'-'A');//lowercase(char);
    }
  }
}

void uppercase(char * str){
  for(int i=0; str[i]!='\0'; i++){
    if(str[i]>='a'&&str[i]<='z'){//if lowercase
      str[i]=str[i]-('a'-'A');//uppercase(char);
    }
  }
}

int printvar(char * vararg, int size){
  char * var;
  char * result;

  var=malloc(size*sizeof(char));
  strncpy(var, vararg, size);

  result=getenv(var);

  if(result!=NULL){
    printf("%s: %s\n",var,result);
    return 1;
  }
  lowercase(var);
  result=getenv(var);
  if(result!=NULL){
    printf("%s: %s\n",var,result);
    return 1;
  }
  uppercase(var);
  result=getenv(var);
  if(result!=NULL){
    printf("%s: %s\n",var,result);
    return 1;
  }
  fprintf(stderr, "error, la variable '%s' no existe\n",vararg);
  free(var);
  return 0;
}

int main(int argc, char *argv[]){
  int i;
  int exitcode=EXIT_SUCCESS;
  if(argc==1){
    fprintf(stderr, "usage: printvars name [name ...]\n");
    int exitcode=EXIT_FAILURE;
  }
  for(i=1; i<argc; i++){
    if(!printvar(argv[i],strlen(argv[i]))) exitcode=EXIT_FAILURE;
  }
  return exitcode;
}
