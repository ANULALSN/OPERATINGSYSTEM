#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
int main(int argc ,char *argv[]){
if(argc<2){
fprintf(stderr,"Usage: %s <program_to_execute> [args..]\n",argv[0]);
exit(EXIT_FAILURE);
}
pid_t pid=fork();

if(pid>0){
//parent process
wait(NULL);
printf("/n Process creation completed\n");
exit(EXIT_SUCCESS);
}
else if(pid==0){
//child process

execvp(argv[1],&argv[1]);
perror("execvp failed");
exit(EXIT_FAILURE);
}
else{
//fork failed
perror("Fork failed");
exit(EXIT_FAILURE);
}

}
