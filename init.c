#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include "init.h"

#define GIT_DIR ".git_gud"

void init(){
	if (mkdir(GIT_DIR,0777) == 0) {
		char cwd[1024];
		if (getcwd(cwd, sizeof(cwd)) != NULL) {
			printf("Initialized empty git_gud repository in %s%s\n",cwd,GIT_DIR);
		} else {
			perror("getcwd");
		}
	} else {
		perror("mkdir");
	}

}
