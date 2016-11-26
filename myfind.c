#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

#include <stdio.h>

int dir_list(char*, char*, char*);
char* mystrcpy(char*, char*);
char* mystrcat(char*, char*);

int main(int argc, char* argv[]){

	dir_list(argv[1], argv[2], argv[3]);

	return 0;
}
int dir_list(char *path, char *option, char *option2){
	struct stat buf;
	struct dirent *dent;
	DIR *dp;

	int dir_err, n;
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
		mystrcpy(filepath, path);
		mystrcat(filepath, "/");
		mystrcat(filepath, dent->d_name);

		if((strcmp(dent->d_name, ".")==0)||(strcmp(dent->d_name, "..")==0)){
			continue;
		}

		dir_err=stat(filepath, &buf);

		if(dir_err==-1){
			perror("dir_err");
			exit(1);
		}

		if(S_ISDIR(buf.st_mode)){
			printf("dir %s\n", dent->d_name);
			mystrcat(filepath, "/");
			dir_list(filepath, option, option2);
		}
		else if(S_ISREG(buf.st_mode)){
			printf("file %s\n", dent->d_name);
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
char* mystrcpy(char* first, char* second){
	int i=0, j=0;
	
	while(second[j]!='\0'){
		first[i++]=second[j++];
	}
	first[i]='\0';

	return first;
}

char* mystrcat(char* first, char* second){
	int i=0, j=0;

	while(first[i]!='\0'){
		i++;
	}
	while(second[j]!='\0'){
		first[i++]=second[j++];
	}
	first[i]='\0';

	return first;
}
