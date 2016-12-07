#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>

int dir_list(char*, char*, char*, char*);
char* mystrcpy(char*, char*);
char* mystrcat(char*, char*);
int mystrcmp(char*, char*);
int mystrlen(char*);
int myatoi(char*);

int main(int argc, char* argv[]){

	dir_list(argv[1], argv[2], argv[3], argv[4]);

	return 0;
}
int dir_list(char *path, char *option, char *option2, char *option3){	//옵션2 or 옵션3에 print
	struct stat buf;
	struct stat file;
	struct dirent *dent;
	DIR *dp;
	int dir_err, n;
	char filepath[255];
	time_t tt;

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

		if(mystrcmp(option, "-empty")==0){
			//빈 파일/디렉토리 검색
		}

		if(mystrcmp(option, "-size")==0){
			//파일 크기와 일치하는 파일 탐색(단위로 b c k w 중 1택)
			//b : 512바이트 블럭(기본 설정), c : 1바이트, k : KB, w : 2바이트 (워드)
			if(option2[0]=='-'){
				//검색조건보다 작은 파일 
			}

			if(option2[0]=='+'){
				//검색조건보다 큰 파일 
			}
		}

		if(mystrcmp(option, "-type")==0){
			//지정된 타입의 파일 검색
		}

		if(mystrcmp(option2, "-print")==0 || mystrcmp(option3, "-print")==0){
			//검색 결과를 표준출력으로 출력
			//option3 만들어서 option2 또는 option3에서 print 요구하면 이용 가능하게 해야하지 않나?
			//ex) if(option2 == "-print" || option3 == "-print")
		}

		if(mystrcmp(option, "-maxdepth")==0){
			//0 아닌 정수값으로 깊이 지정하여 검색
		}

		if(mystrcmp(option, "-mindepth")==0){
			//0 아닌 정수값으로 깊이 지정하여 그 깊이부터 하위 디렉토리 검색
		}

		if(mystrcmp(option, "-newer")==0){
			dir_err=stat(option2, &file);
			if(dir_err==-1){
				perror("dir_err");
				exit(1);
			}
			if((file.st_mtime)<(buf.st_mtime)){
				if(S_ISDIR(buf.st_mode)){
					write(1, filepath, mystrlen(filepath));
					write(1, "\n", 2);
					mystrcat(filepath, "/");
					dir_list(filepath, option, option2);
				}
				else if(S_ISREG(buf.st_mode)){
					write(1, filepath, mystrlen(filepath));
					write(1, "\n", 2);
				}
			}
		}
		else if(mystrcmp(option, "-anewer")==0){
			dir_err=stat(option2, &file);
			if(dir_err==-1){
				perror("dir_err");
				exit(1);
			}
			if((file.st_atime)<(buf.st_atime)){
				if(S_ISDIR(buf.st_mode)){
					write(1, filepath, mystrlen(filepath));
					write(1, "\n", 2);
					mystrcat(filepath, "/");
					dir_list(filepath, option, option2);
				}
				else if(S_ISREG(buf.st_mode)){
					write(1, filepath, mystrlen(filepath));
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
			if((file.st_ctime)<(buf.st_ctime)){
				if(S_ISDIR(buf.st_mode)){
					write(1, filepath, mystrlen(filepath));
					write(1, "\n", 2);
					mystrcat(filepath, "/");
					dir_list(filepath, option, option2);
				}
				else if(S_ISREG(buf.st_mode)){
					write(1, filepath, mystrlen(filepath));
					write(1, "\n", 2);
				}
			}
		}
		else if(mystrcmp(option, "-atime")==0){
			if(option2[0]=='-'){
				time(&tt);			
				if(S_ISDIR(buf.st_mode)){
					dir_err=stat(path, &file);
					if(dir_err==-1){
						perror("dir_err");
						exit(1);
					}
					if(file.st_atime>((int)tt-(60*60*24*myatoi(option2)))){
						write(1, filepath, mystrlen(filepath));
						write(1, "\n", 2);
					}
					mystrcat(filepath, "/");
					dir_list(filepath, option, option2);
				}
				else if(S_ISREG(buf.st_mode)){
					dir_err=stat(filepath, &file);
					if(dir_err==-1){
						perror("dir_err");
						exit(1);
					}
					if(file.st_atime>((int)tt-(60*60*24*myatoi(option2)))){
						write(1, filepath, mystrlen(filepath));
						write(1, "\n", 2);
					}
				}
			}
			else if(option2[0]=='+'){
				time(&tt);
				if(S_ISDIR(buf.st_mode)){
					dir_err=stat(path, &file);
					if(dir_err==-1){
						perror("dir_err");
						exit(1);
					}
					if(!(file.st_atime>((int)tt-(60*60*24*myatoi(option2))))){
						write(1, filepath, mystrlen(filepath));
						write(1, "\n", 2);
					}
					mystrcat(filepath, "/");
					dir_list(filepath, option, option2);
				}
				else if(S_ISREG(buf.st_mode)){
					dir_err=stat(filepath, &file);
					if(dir_err==-1){
						perror("dir_err");
						exit(1);
					}
					if(!(file.st_atime>((int)tt-(60*60*24*myatoi(option2))))){
						write(1, filepath, mystrlen(filepath));
						write(1, "\n", 2);
					}
				}
			}
			else{
				time(&tt);
				if(S_ISDIR(buf.st_mode)){
					dir_err=stat(path, &file);
					if(dir_err==-1){
						perror("dir_err");
						exit(1);
					}
					if(file.st_atime>((int)tt-(60*60*24*myatoi(option2)))&&file.st_atime<((int)tt-(60*60*24*(1+myatoi(option2))))){
						write(1, filepath, mystrlen(filepath));
						write(1, "\n", 2);
					}
					mystrcat(filepath, "/");
					dir_list(filepath, option, option2);
				}
				else if(S_ISREG(buf.st_mode)){
					dir_err=stat(filepath, &file);
					if(dir_err==-1){
						perror("dir_err");
						exit(1);
					}
					if(file.st_atime>((int)tt-(60*60*24*myatoi(option2)))&&file.st_atime<((int)tt-(60*60*24*(1+myatoi(option2))))){
						write(1, filepath, mystrlen(filepath));
						write(1, "\n", 2);
					}
				}
			}
		}
		else if(mystrcmp(option, "-ctime")==0){
			if(option2[0]=='-'){
				time(&tt);
				if(S_ISDIR(buf.st_mode)){
					dir_err=stat(path, &file);
					if(dir_err==-1){
						perror("dir_err");
						exit(1);
					}
					if(file.st_ctime>((int)tt-(60*60*24*myatoi(option2)))){
						write(1, filepath, mystrlen(filepath));
						write(1, "\n", 2);
					}
					mystrcat(filepath, "/");
					dir_list(filepath, option, option2);
				}
				else if(S_ISREG(buf.st_mode)){
					dir_err=stat(filepath, &file);
					if(dir_err==-1){
						perror("dir_err");
						exit(1);
					}
					if(file.st_ctime>((int)tt-(60*60*24*myatoi(option2)))){
						write(1, filepath, mystrlen(filepath));
						write(1, "\n", 2);
					}
				}
			}
			else if(option2[0]=='+'){
				time(&tt);
				if(S_ISDIR(buf.st_mode)){
					dir_err=stat(path, &file);
					if(dir_err==-1){
						perror("dir_err");
						exit(1);
					}
					if(!(file.st_ctime>((int)tt-(60*60*24*myatoi(option2))))){
						write(1, filepath, mystrlen(filepath));
						write(1, "\n", 2);
					}
					mystrcat(filepath, "/");
					dir_list(filepath, option, option2);
				}
				else if(S_ISREG(buf.st_mode)){
					dir_err=stat(filepath, &file);
					if(dir_err==-1){
						perror("dir_err");
						exit(1);
					}
					if(!(file.st_ctime>((int)tt-(60*60*24*myatoi(option2))))){
						write(1, filepath, mystrlen(filepath));
						write(1, "\n", 2);
					}
				}
			}
			else{
				time(&tt);
				if(S_ISDIR(buf.st_mode)){
					dir_err=stat(path, &file);
					if(dir_err==-1){
						perror("dir_err");
						exit(1);
					}
					if(file.st_ctime>((int)tt-(60*60*24*myatoi(option2)))&&file.st_ctime<((int)tt-(60*60*24*(1+myatoi(option2))))){
						write(1, filepath, mystrlen(filepath));
						write(1, "\n", 2);
					}
					mystrcat(filepath, "/");
					dir_list(filepath, option, option2);
				}
				else if(S_ISREG(buf.st_mode)){
					dir_err=stat(filepath, &file);
					if(dir_err==-1){
						perror("dir_err");
						exit(1);
					}
					if(file.st_ctime>((int)tt-(60*60*24*myatoi(option2)))&&file.st_ctime<((int)tt-(60*60*24*(1+myatoi(option2))))){
						write(1, filepath, mystrlen(filepath));
						write(1, "\n", 2);
					}
				}
			}
		}
		else if(mystrcmp(option, "-mtime")==0){
			if(option2[0]=='-'){
				time(&tt);
				if(S_ISDIR(buf.st_mode)){
					dir_err=stat(path, &file);
					if(dir_err==-1){
						perror("dir_err");
						exit(1);
					}
					if(file.st_mtime>((int)tt-(60*60*24*myatoi(option2)))){
						write(1, filepath, mystrlen(filepath));
						write(1, "\n", 2);
					}
					mystrcat(filepath, "/");
					dir_list(filepath, option, option2);
				}
				else if(S_ISREG(buf.st_mode)){
					dir_err=stat(filepath, &file);
					if(dir_err==-1){
						perror("dir_err");
						exit(1);
					}
					if(file.st_mtime>((int)tt-(60*60*24))){
						write(1, filepath, mystrlen(filepath));
						write(1, "\n", 2);
					}
				}
			}
			else if(option2[0]=='+'){
				time(&tt);
				if(S_ISDIR(buf.st_mode)){
					dir_err=stat(path, &file);
					if(dir_err==-1){
						perror("dir_err");
						exit(1);
					}
					if(!(file.st_mtime>((int)tt-(60*60*24*myatoi(option2))))){
						write(1, filepath, mystrlen(filepath));
						write(1, "\n", 2);
					}
					mystrcat(filepath, "/");
					dir_list(filepath, option, option2);
				}
				else if(S_ISREG(buf.st_mode)){
					dir_err=stat(filepath, &file);
					if(dir_err==-1){
						perror("dir_err");
						exit(1);
					}
					if(!(file.st_mtime>((int)tt-(60*60*24*myatoi(option2))))){
						write(1, filepath, mystrlen(filepath));
						write(1, "\n", 2);
					}
				}
			}
			else{
				time(&tt);
				if(S_ISDIR(buf.st_mode)){
					dir_err=stat(path, &file);
					if(dir_err==-1){
						perror("dir_err");
						exit(1);
					}
					if(file.st_mtime>((int)tt-(60*60*24*myatoi(option2))&&file.st_mtime<((int)tt-(60*60*24*myatoi(option2))))){
						write(1, filepath, mystrlen(filepath));
						write(1, "\n", 2);
					}
					mystrcat(filepath, "/");
					dir_list(filepath, option, option2);
				}
				else if(S_ISREG(buf.st_mode)){
					dir_err=stat(filepath, &file);
					if(dir_err==-1){
						perror("dir_err");
						exit(1);
					}
					if(file.st_mtime>((int)tt-(60*60*24*myatoi(option2))&&file.st_mtime<((int)tt-(60*60*24*myatoi(option2))))){
						write(1, filepath, mystrlen(filepath));
						write(1, "\n", 2);
					}
				}
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
int myatoi(char* str){
	int value=0, i=1;
	while(str[i]!='\0'){
		if(str[i]>='0'&&str[i]<='9'){
			value=(value*10)+(str[i]-'0');
		}
		i++;
	}
	return value;
}
