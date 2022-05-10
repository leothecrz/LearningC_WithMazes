
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(void){

	pid_t pid = fork();
	if(pid < 0){
		perror("fork fail");
	} else if (pid == 0){
		execl("GEN", "GEN", NULL);
	}

	wait(NULL);	

	FILE* fFile;
	char choice = ' ';
	int replace = 0;
	int noMap = 1;
	if( access( "map.txt", F_OK ) == 0 ){
		noMap = 0;
		printf("MAP.txt EXIST\n Do you wish to replace it?(Y/n)?: ");
		scanf("%c", &choice);
		switch(choice){
			case 'Y':
			case 'y':
				replace = 1;
				break;
			case 'N':
			case 'n':
				break;
		
		}
	}
	
	int flag1 = 0;
	if(replace){
		flag1 = 1;
		remove("map.txt");
		rename("newMap.txt", "map.txt");
	}else if(noMap) {
		flag1 = 1;
		printf("\n map.txt created \n");
		rename("newMap.txt", "map.txt");
	} else {
		printf("newMap.txt created\n");
	}

	if (flag1){

		execl("/usr/bin/vim", "/usr/bin/vim", "map.txt", NULL);
		wait(NULL); // TO BE FIXED
		execl("MAIN", "MAIN", ">output.txt", NULL);
	}
	return 0;
}
