#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

/*
enum{

};
*/

int
buffering(int fd)
{
	char c;
	int count = 0;
	FILE *f;

	f = fdopen(fd, "r");
	if(f == NULL)
		err(EXIT_FAILURE, "cant fopen fd");
	while(fread(&c, 1, 1, f) != 0){
		count++;
	}
	if(! feof(f))
		errx(EXIT_FAILURE, "fread failed");
	fclose(f);
	return count;
}



int main(int argc, char * argv[]){
  int fdin;

  if (argc != 3) {
    usage();
  }

  fdin = open(argv[1], O_RDONLY);
  if(fdin < 0)
    err(1, "can't open input file");

}
