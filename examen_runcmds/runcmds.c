#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#include <sys/file.h>

const char NAME[] = "runcmds";
const char EXEC_ERROR[] = "command not found";
const char FORK_ERROR[] = "can't fork";
const char FILE_ERROR[] = "can't open file";
const char PIPE_ERROR[] = "pipe error";
const char USAGE_ERROR[] = "usage: runcmds regexp [file]";

const char * PATH[] = {"." ,"/bin", "/usr/bin"};
enum{
  FALSE,
  TRUE,
  N_PATHS=3,
  MAX_ARGS=256,
  MAX_PATH_LENGTH=512,
  MAX_LINE_LENGTH=1024
};

void tokenize(char * input, char * output[]){
  //tokenizes [input] in [output]
  char * rest = input;
  int i=0;
  while ((output[i] = strtok_r(rest, " \n", &rest))){
    i++;
  }
  output[i]=NULL;
}

int search_command_path(const char * name, char * path){
  //writes the path of the command [name] in [path]
  int i;
  int found=FALSE;

  for(i=0;i<N_PATHS;i++){
    snprintf(path,MAX_PATH_LENGTH,"%s/%s",PATH[i],name);
    if(access(path,X_OK)==0){
      found=TRUE;
      break;
    }
  }
  return found;
}

pid_t exec_command(char * path, char ** args, int infd, int outfd){
  //you can give intfd and outfd a negative value if you dont want to redirect them

  pid_t child_pid=fork();
  switch(child_pid){
    case 0:
      if(infd>=0){
        printf("%d%d\n",infd,outfd);
        close(0);//Close stdin
        dup2(infd,0);
      }
      if(outfd>=0){
        printf("%d%d\n",infd,outfd);
        close(1);//Close stdout
        dup2(outfd,1);
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

int exec_line(char * line){
  char * name=malloc(MAX_LINE_LENGTH*sizeof(char));
  char * path=malloc(MAX_LINE_LENGTH*sizeof(char));
  char ** command=malloc(MAX_ARGS*sizeof(char*));

  //extract name and args
  tokenize(line, command);
  strncpy(name, command[0], MAX_LINE_LENGTH);

  //get the path from the name
  if(!search_command_path(name,path)){
    free(name);
    free(path);
    free(command);
    fprintf(stderr, "[%s]: %s\n", NAME, EXEC_ERROR);
    return FALSE;
  }
  //fprintf(stderr,"args: %s,%s,%s",path,command[1],command[2]);
  wait_command(exec_command(path,command,-1,-1));
  free(name);
  free(path);
  free(command);
  return TRUE;
}

int filter(char * regexp, char * input, FILE * fout){

  int p1[2];//pipe from here to grep
  if(pipe(p1) < 0){
    fprintf(stderr, "[%s]: %s\n", NAME, PIPE_ERROR);
    return FALSE;
  }
  close(p1[0]);  // Close reading end of first pipe

  //write(p1[1], input, strlen(input)+1);

  char * grep_args[]={"grep","-E","--text",regexp,NULL};

  pid_t grep_pid=exec_command("/bin/egrep",grep_args,p1[1],fileno(fout));//fileno(fout)


  close(p1[1]);
  fclose(fout);
  wait_command(grep_pid);

  return TRUE;
}

int main(int argc, char * argv[]){

  FILE * fout = fopen("data/f1.out", "w");
  if(fout == NULL){
    fprintf(stderr, "[%s]: '%s' %s\n", NAME, "file.out", FILE_ERROR);
    exit(EXIT_FAILURE);
  }
  char str[]="123456789101112131415";
  //printf("%d",sizeof(str));
  fwrite(str , 1 , sizeof(str)-1 , fout);

  filter("la","hola\nadios",fout);

/*
  if(argc<2 || argc>3){
    fprintf(stderr, "[%s]: %s\n", NAME, USAGE_ERROR);
    exit(EXIT_FAILURE);
  }

  FILE * fp;
  char * file_name;

  if(argc==3){
    fprintf(stderr, "[%s debug]: %s\n", NAME, "file");
    file_name=argv[2];
    fp = fopen(file_name , "r");
  }
  else{
    fprintf(stderr, "[%s debug]: %s\n", NAME, "stdin");
    file_name="stdin";
    fp = stdin;
  }
  if(fp == NULL) {
    fprintf(stderr, "[%s]: '%s' %s\n", NAME, file_name, FILE_ERROR);
    exit(EXIT_FAILURE);
  }

  //read and execute each line
  char line[MAX_LINE_LENGTH];
  int done=FALSE;
  flock(fileno(fp), LOCK_EX);//TODO: lock de escritura???
  while(!done) {
    if(fgets (line, MAX_LINE_LENGTH, fp)==NULL){
      done=TRUE;
    }

    if(!done){
      fprintf(stderr, "[%s debug] line: %s", NAME, line);
      exec_line(line);
    }
  }
  flock(fileno(fp), LOCK_EX);//TODO: hasta que se termine de ejecutar???
  fclose(fp);
*/
  exit(EXIT_SUCCESS);
}

/*
  ----flock del fichero
  ----leo fichero o stdin
  ----ejecuto cada linea
  filtrar la salida de cada linea
  .escribir la salida en un fichero
  .escribir salida de error en otro
  .leer el status de error y escribirlo en stdout
*/


/*
nombre: runcmds.c
objetivo: que lea líneas que contengan comandos (uno por línea) y los ejecute,
  filtrando su salida con una expresión regular
args: 1=regexp [2=fichero]
  si no se pasa el 2 lee de stdin
  cuidado si pasan un fichero, hay que hacer flock
    error flock: "error: another instance of runcmds is running for this commands file: f"
los comandos se ejecutan en orden y no concurrentemente
Los comandos se deben buscar en el directorio actual, /bin y /usr/bin (en ese orden).
límite de 1023 caracteres por cada línea del fichero
límite de 255 argumentos para cada comando

El programa debe escribir por su salida el número de la línea y a continuación
si ha ejecutado correctamente ("SUCCESS") o ha fallado ("FAIL"). El programa
debe intentar ejecutar todos los comandos del fichero.

$ ./runcmds ‘h.la’ f1
0: SUCCESS
1: SUCCESS
2: FAIL
3: SUCCESS
4: SUCCESS

La salida de todos los comandos, filtrada por la expresión regular indicada,
debe escribirse en el fichero f.out, donde f es la ruta del fichero de comandos.
En caso de leer de la entrada estándar, se escribirá la salida en el fichero
“stdin.out”. Si el fichero existe (p. ej. de una ejecución anterior), se debe
truncar. Si no existe, se debe crear. Si no se puede crear/truncar, se debe
abortar la ejecución del programa.

Se debe ejecutar cada comando redirigiendo su entrada estándar a /dev/null y su
salida de errores a un fichero f.número-de-línea.err, siendo f la ruta del
fichero de comandos (en caso de leer de la entrada estándar, se usará "stdin"
como f) y  número-de-línea  la línea correspondiente al comando que se ha
ejecutado.

Si estos ficheros existen (p. ej. de una ejecución anterior), se deben truncar.
Si no existen, se deben crear. Si no se pueden crear/truncar,la ejecución de ese
comando debe fallar.

$ ls
f1        //entrada
f1.0.err  //salida de error del comando
f1.1.err  //salida de error del comando
f1.2.err  //salida de error del comando
f1.3.err  //salida de error del comando
f1.4.err  //salida de error del comando
f1.out    //salida filtrada
runcmds




---------------------------------------------------------------------------------
Escriba un programa runcmds.c en C para GNU/Linux que lea líneas que contengan
comandos (uno por línea) y los ejecute, filtrando su salida con una expresión
regular. El programa tiene un primer parámetro, que es la expresión regular,
y puede admitir segundo argumento que indique el fichero del que tiene que leer
las líneas con los comandos. Si no se pasa el segundo argumento, debe leer
líneas de comandos de su entrada estándar.

Si se leen las líneas de un fichero de comandos pasado como argumento, el
programa se debe asegurar de que no se ejecute este programa sobre el
mismo fichero de comandos hasta que haya terminado (esto es, no se pueden
ejecutar distintas instancias del programa sobre el mismo fichero
concurrentemente). Si se da el caso, se deberá abortar la ejecución de la
segunda instancia y escribir en salida de errores "error: another instance
of runcmds is running for this commands file: f" (donde f es la ruta del
fichero de comandos). Se recomienda usar la llamada al sistema flock(2) para
implementar este requisito.

Los comandos se tienen que ejecutar de forma secuencial, en el orden en el que
aparecen en el fichero de comandos. Se puede suponer que las líneas del fichero
no contienen más de 1023 caracteres. Los comandos descritos en el fichero de
comandos pueden tener argumentos. Se puede establecer un límite de 255
argumentos para cada comando.

La salida de todos los comandos, filtrada por la expresión regular indicada,
debe escribirse en el fichero f.out, donde f es la ruta del fichero de comandos.
En caso de leer de la entrada estándar, se escribirá la salida en el fichero
“stdin.out”. Si el fichero existe (p. ej. de una ejecución anterior), se debe
truncar. Si no existe, se debe crear. Si no se puede crear/truncar, se debe
abortar la ejecución del programa.

Se debe ejecutar cada comando redirigiendo su entrada estándar a /dev/null y su
salida de errores a un fichero f.número-de-línea.err, siendo f la ruta del
fichero de comandos (en caso de leer de la entrada estándar, se usará "stdin"
como f) y  número-de-línea  la línea correspondiente al comando que se ha
ejecutado.

Si estos ficheros existen (p. ej. de una ejecución anterior), se deben truncar.
Si no existen, se deben crear. Si no se pueden crear/truncar,la ejecución de ese
comando debe fallar.
Los comandos se deben buscar en el directorio actual,
/bin y /usr/bin (en ese orden).

El programa debe escribir por su salida el número de la línea y a continuación
si ha ejecutado correctamente ("SUCCESS") o ha fallado ("FAIL"). El programa
debe intentar ejecutar todos los comandos del fichero.
No se permite ejecutar un shell o usar system(). Se debe usar las llamadas
execv(2) / execl(2)  para ejecutar programas.

Un posible ejemplo es:

$ ls
f1
runcmds
$ cat f1
echo hola
echo fsfasf
comandoqueno no existe
echo hIla
ls /
$ ./runcmds ‘h.la’ f1
0: SUCCESS
1: SUCCESS
2: FAIL
3: SUCCESS
4: SUCCESS
$ ls
f1
f1.0.err
f1.1.err
f1.2.err
f1.3.err
f1.4.err
f1.out
runcmds
$ cat f1.out
hola
hIla
$ rm f1*
$ ./runcmds ‘.’
echo hola
0: SUCCESS
echo adios
1: SUCCESS
^D
$ ls
runcmds
stdin.0.err
stdin.1.err
stdin.out
$ cat stdin.out
hola
adios
$
*/
