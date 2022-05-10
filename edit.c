#include <stdio.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>


int main(void){

    pid_t pid = fork();
	if(pid < 0){
		perror("fork fail");
	} else if (pid == 0){
            execl("/usr/bin/vim", "/usr/bin/vim", "map.txt", NULL);
	}

	wait(NULL);	

	execl("MAIN", "MAIN", ">output.txt", NULL);

    return 0;
}