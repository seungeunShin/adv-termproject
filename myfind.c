#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

#include <stdio.h>

int dir_list(char*, char*, char*);
char* mystrcpy(char*, char*);
char* mystrcat(char*, char*);
int mystrcmp(char*, char*);
int mystrlen(char*);

int main(int argc, char* argv[]){

	dir_list(argv[1], argv[2], argv[3]);

	return 0;
}
int dir_list(char *path, char *option, char *option2){
	struct stat buf;
	struct stat file;
	struct dirent *dent;
	DIR *dp;
	int dir_err, n;
	char filepath[255];
	char filename[255];

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

		if((mystrcmp(dent->d_name, ".")==0)||(mystrcmp(dent->d_name, "..")==0)){
			continue;
		}

		dir_err=stat(filepath, &buf);
		if(dir_err==-1){
			perror("dir_err");
			exit(1);
		}

		if(mystrcmp(option, "-newer")==0){

		}
		else if(mystrcmp(option, "-anewer")==0){
			dir_err=stat(option2, &file);
			if(dir_err==-1){
				perror("dir_err");
				exit(1);
			}
			if((file.st_atime)>(buf.st_atime)){
				if(S_ISDIR(buf.st_mode)){
					mystrcpy(filename, dent->d_name);

					write(1, filename, mystrlen(filename));
					write(1, "\n", 2);
					mystrcat(filepath, "/");
					dir_list(filepath, option, option2);
				}
				else if(S_ISREG(buf.st_mode)){
					mystrcpy(filename, dent->d_name);

					write(1, filename, mystrlen(filename));
					write(1, "\n", 2);
				}
			}
		}
		else if(mystrcmp(option, "-cnewer")==0){
			dir_err=stat(option2, &file);
			if(dir_err==-1){
				perror("dir_err");
				exit(1);
			}
			if((file.st_ctime)>(buf.st_ctime)){
				if(S_ISDIR(buf.st_mode)){
					mystrcpy(filename, dent->d_name);

					write(1, filename, mystrlen(filename));
					write(1, "\n", 2);
					mystrcat(filepath, "/");
					dir_list(filepath, option, option2);
				}
				else if(S_ISREG(buf.st_mode)){
					mystrcpy(filename, dent->d_name);

					write(1, filename, mystrlen(filename));
					write(1, "\n", 2);
				}
			}
		}

		else if(mystrcmp(option, "-atime")==0){
			if(option2[0]=='-'){

			}
			else if(option2[0]=='+'){

			}
			else{

			}
		}
		else if(mystrcmp(option, "-ctime")==0){
			if(option2[0]=='-'){

			}
			else if(option2[0]=='+'){

			}
			else{

			}
		}
		else if(mystrcmp(option, "-mtime")==0){
			if(option2[0]=='-'){

			}
			else if(option2[0]=='+'){

			}
			else{

			}
		}

		if(mystrcmp(option,"-name")==0)
		{
				
		}
		else if(mystrcmp(option,"-perm")==0)
		{
			if(dir_err==1)
			{
				perror("dir_err");
				exit(1);
			}

		}
		else if(mystrcmp(option,"-user")==0)
		{
			if(dir_err==1)
			{
				perror("dir_err");
				exit(1);
			}
		}
		else if(mystrcmp(option,"-group")==0)
		{
			if(dir_err==1)
			{
				perror("dir_err");
				exit(1);
			}
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
int mystrcmp(char* first, char* second){
	int result=1;
	int i=0, j=0;

	while((first[i]!='\0')||(second[j]!='\0')){
		if(first[i++]==second[j++]) result=0;
		else result=1;
	}

	return result;
}
int mystrlen(char* buf){
	int i=0, count=0;
	while(buf[i++]!='\0'){
		count++;
	}
	return count;
}
