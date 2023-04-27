#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

void moo_parallel(int c);

void moo_sequential(int c);

int main(int argc, char** argv){
  if(argc != 3){
    errno = -1;
    perror("Expected 3 arguments.\n Usage: \"./moo -{s/p} {n}\"");
    exit(-1);
  }
  int c = atoi(argv[2]);
  char* f = argv[1];
  if(strcmp(f, "-s") !=0 && strcmp(f, "-p")!=0){
    errno = -1;
    perror("Bad flag set. Usage: \"./moo -{s/p} {n}\"");
    exit(-1);
  }
  if(f[1] == 's') moo_sequential(c);
  else if(f[1] == 'p') moo_parallel(c);
    return 0;
 }

 
void moo_sequential(int c){
  for(int i = 0; i < c; i++){
    int pid = fork();
    if(pid == 0){
      char* command = "apt-get moo";
      execl("/bin/sh", "sh", "-c", command, (char *) NULL);
    }
    int r;
    wait(&r);
  }
}

void moo_parallel(int c){
  int pids[c];
  for(int i = 0; i < c; i++){
    int pid = fork();
    pids[i] = pid;
    if(pid == 0){
      char* command = "apt-get moo";
      execl("/bin/sh", "sh", "-c", command, (char *) NULL);
    }
  }
  for(int i=0; i<c; i++){
    wait(&pids[i]);
  }
}
