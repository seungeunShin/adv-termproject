#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

int main(int argc, char* argv[]){

	dir_list(argv[1], argv[2], argv[3]);

	return 0;
}
int dir_list(char *path, char *option, char *option2){
	struct stat buf;
	struct dirent *dent;
	DIR *dp;

	int dir_err;
	char filepath[255];

	if((dp=opendir(path))==NULL){
		perror("opendir");
		exit(1);
	}
	if((dent=readdir(dp))==NULL){
		perror("readdir");
		exit(1);
	}
	do{
		dir_err=stat(path, *buf);

		if(dir_err==-1){
			perror("dir_err");
			exit(1);
		}


		if(option=="-newer"){

		}
		else if(option=="-anewer"){

		}
		else if(option=="-cnewer"){

		}
		else if(option=="-atime"){

		}
		else if(option=="-ctime"){

		}
		else if(option=="-mtime"){

		}
	}while((dent=readdir(dp))!=NULL);

	closedir(dp);

	return 0;
}
