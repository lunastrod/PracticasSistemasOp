#include <stdlib.h>
#include <stdio.h>
#include <string.h>

enum{
  FALSE,
  TRUE,
  CAPITALIZE='A'-'a'
};

void uppercase(char * str){
  for(int i=0; str[i]!='\0'; i++){
    if(str[i]>='a'&&str[i]<='z'){
      str[i]=str[i]+CAPITALIZE;
    }
  }
}

void lowercase(char * str){
  for(int i=0; str[i]!='\0'; i++){
    if(str[i]>='A'&&str[i]<='Z'){
      str[i]=str[i]-CAPITALIZE;
    }
  }
}

int printvar_case_sensitive(char * namevar){
  //if the variable exists prints it and returns true
  //warning: case sensitive
  char * value;
  value=getenv(namevar);
  if(value!=NULL){
    printf("%s: %s\n",namevar,value);
    return TRUE;
  }
  return FALSE;
}

int printvar(char * namevar_input, int size){
  //if the variable exists prints it and returns true
  char * var;

  var=malloc((size+1)*sizeof(char));
  strncpy(var, namevar_input, size);

  if (printvar_case_sensitive(var)){
    free(var);
    return TRUE;
  }

  lowercase(var);
  if (printvar_case_sensitive(var)){
    free(var);
    return TRUE;
  }

  uppercase(var);
  if (printvar_case_sensitive(var)){
    free(var);
    return TRUE;
  }

  fprintf(stderr, "error, la variable '%s' no existe\n",namevar_input);
  free(var);
  return 0;
}

int main(int argc, char *argv[]){
  int i;
  int exitcode=EXIT_SUCCESS;
  if(argc==1){
    fprintf(stderr, "usage: printvars name [name ...]\n");
    exit(EXIT_FAILURE);
  }
  for(i=1; i<argc; i++){
    if(!printvar(argv[i],strlen(argv[i])))
      exitcode=EXIT_FAILURE;
  }
  exit(exitcode);
}
