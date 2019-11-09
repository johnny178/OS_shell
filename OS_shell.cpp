#include <iostream>
#include <string>
#include <unistd.h>
#include <cstring>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
using namespace std;

bool isCut(string);
bool isPipe(string);
bool isDirect_out(string);
bool isDirect_in(string);

int main(){
	string input;
	int j;
	string sub1 = input;
	string sub2;
	char user[64];
	char cwd[128];
    string argv;

	getlogin_r(user,sizeof(user)-1);
	string username(user);
	for (; 1 == 1;){
		getcwd(cwd,sizeof(cwd)-1);
		string path(cwd);
		cout<<username<<"@"<<path<<">";

		getline(cin, input, '\n');
		if (input == "exit"){
			cout << "ByeBye!"<<endl;
			break;
		}
		if (input[0] == 'c'&&input[1] == 'd'){
			sub2=input.substr(3);
			char result[20];
			strcpy(result,sub2.c_str());
			chdir(result);
		}
		else{
			if (isCut(input)==1){
				j = input.find(' ');
				sub1 = input.substr(0, j);
				sub2 = input.substr(j + 1);
				string comma = sub2;
				if(isCut(sub2)==1 || isPipe(sub2)==1){
					j=sub2.find(' ');
					string sub3=sub2.substr(0,j);

					string sub4=sub2.substr(j+3);
					j = sub4.find(' ');
					string sub5 = sub4.substr(0,j);
					string sub6 = sub4.substr(j+1);
					if(isPipe(sub6)==1){
						j = sub6.find('|');
						string sub7 = sub6.substr(j+2);
						j = sub6.find(' ');
						sub6 = sub6.substr(0,j);
						j = sub7.find(' ');
						string sub8 = sub7.substr(0,j);
						string sub9 = sub7.substr(j+1);
						
						if(isPipe(sub9)==1){
							j = sub9.find('|');
							string sub10 = sub9.substr(j+2);
							j = sub9.find(' ');
							sub9 = sub9.substr(0,j);
							j = sub10.find(' ');
							string sub11 = sub10.substr(0,j);
							string sub12 = sub10.substr(j+1);


							int fd1[2];
							pipe(fd1);

							int fd2[2];
							pipe(fd2);

							int fd3[2];
							pipe(fd3);

							char* porcess_A[3];

							porcess_A[0]=(char*)sub1.c_str();
							porcess_A[1]=(char*)sub3.c_str();
							porcess_A[2]=NULL;
							
							pid_t pid_A=fork();
							
							if(pid_A==0){
								dup2(fd1[1],1);
								close(fd1[0]);
								close(fd1[1]);
								if(execvp(porcess_A[0],porcess_A)==-1){
									perror("exec");
								}
							}
							if(pid_A==-1){
							perror("fork");
							}//Process A

							char* porcess_B[3];

							porcess_B[0]=(char*)sub5.c_str();
							porcess_B[1]=(char*)sub6.c_str();
							porcess_B[2]=NULL;
							pid_t pid_B=fork();

							if(pid_B==0){
								dup2(fd1[0],0);
								close(fd1[0]);
								close(fd1[1]);
								dup2(fd2[1],1);
								close(fd2[0]);
								close(fd2[1]);
								if(execvp(porcess_B[0],porcess_B)==-1){
									perror("exec");
								}
							}
							if(pid_B>0){
								close(fd1[0]);
								close(fd1[1]);
								if(waitpid(pid_B,NULL,0)==-1){
									perror("wait");
								}
							}
							if(pid_B==-1){
							perror("fork");
							}//Process B

							char* porcess_C[3];

							porcess_C[0]=(char*)sub8.c_str();
							porcess_C[1]=(char*)sub9.c_str();
							porcess_C[2]=NULL;
							pid_t pid_C=fork();

							if(pid_C==0){
								dup2(fd2[0],0);
								close(fd2[0]);
								close(fd2[1]);
								dup2(fd3[1],1);
								close(fd3[0]);
								close(fd3[1]);
								if(execvp(porcess_C[0],porcess_C)==-1){
									perror("exec");
								}
							}
							if(pid_C>0){
								close(fd2[0]);
								close(fd2[1]);
							}
							if(pid_C==-1){
							perror("fork");
							}//Process C

							char* porcess_D[3];

							porcess_D[0]=(char*)sub11.c_str();
							porcess_D[1]=(char*)sub12.c_str();
							porcess_D[2]=NULL;
							pid_t pid_D=fork();

							if(pid_D==0){
								dup2(fd3[0],0);
								close(fd3[0]);
								close(fd3[1]);
								if(execvp(porcess_D[0],porcess_D)==-1){
									perror("exec");
								}
							}
							if(pid_D>0){
								close(fd3[0]);
								close(fd3[1]);
								if(waitpid(pid_D,NULL,0)==-1){
									perror("wait");
								}
							}
							if(pid_D==-1){
							perror("fork");
							}//Process D
						}
						else{
							int fd1[2];
							pipe(fd1);

							int fd2[2];
							pipe(fd2);

							char* porcess_A[3];

							porcess_A[0]=(char*)sub1.c_str();
							porcess_A[1]=(char*)sub3.c_str();
							porcess_A[2]=NULL;
							
							pid_t pid_A=fork();
							
							if(pid_A==0){
								dup2(fd1[1],1);
								close(fd1[0]);
								close(fd1[1]);
								if(execvp(porcess_A[0],porcess_A)==-1){
									perror("exec");
								}
							}
							if(pid_A==-1){
							perror("fork");
							}//Process A

							char* porcess_B[3];

							porcess_B[0]=(char*)sub5.c_str();
							porcess_B[1]=(char*)sub6.c_str();
							porcess_B[2]=NULL;
							pid_t pid_B=fork();

							if(pid_B==0){
								dup2(fd1[0],0);
								close(fd1[0]);
								close(fd1[1]);
								dup2(fd2[1],1);
								close(fd2[0]);
								close(fd2[1]);
								if(execvp(porcess_B[0],porcess_B)==-1){
									perror("exec");
								}
							}
							if(pid_B>0){
								close(fd1[0]);
								close(fd1[1]);
								if(waitpid(pid_B,NULL,0)==-1){
									perror("wait");
								}
							}
							if(pid_B==-1){
							perror("fork");
							}//Process B

							char* porcess_C[3];

							porcess_C[0]=(char*)sub8.c_str();
							porcess_C[1]=(char*)sub9.c_str();
							porcess_C[2]=NULL;
							pid_t pid_C=fork();

							if(pid_C==0){
								dup2(fd2[0],0);
								close(fd2[0]);
								close(fd2[1]);
								if(execvp(porcess_C[0],porcess_C)==-1){
									perror("exec");
								}
							}
							if(pid_C>0){
								close(fd2[0]);
								close(fd2[1]);
								if(waitpid(pid_C,NULL,0)==-1){
									perror("wait");
								}
							}
							if(pid_C==-1){
							perror("fork");
							}//Process C
						}
					}

					else{
						if(isDirect_out(sub6)==1){
							j = sub6.find('>');
							string sub7 = sub6.substr(j+2);
							j = sub6.find(' ');
							sub6 = sub6.substr(0,j);
							char* pathname[1];
							pathname[0]=(char*)sub7.c_str();

							int fd[2];
							pipe(fd);
							char* porcess_A[3];

							porcess_A[0]=(char*)sub1.c_str();
							porcess_A[1]=(char*)sub3.c_str();
							porcess_A[2]=NULL;
							
							pid_t pid_A=fork();
							
							if(pid_A==0){
								dup2(fd[1],1);
								close(fd[0]);
								close(fd[1]);
								if(execvp(porcess_A[0],porcess_A)==-1){
									perror("exec");
								}
							}
							if(pid_A==-1){
							perror("fork");
							}//Process A

							char* porcess_B[3];

							porcess_B[0]=(char*)sub5.c_str();
							porcess_B[1]=(char*)sub6.c_str();
							porcess_B[2]=NULL;
							pid_t pid_B=fork();

							if(pid_B==0){
								dup2(fd[0],0);
								close(fd[0]);
								close(fd[1]);

								int fd = open(pathname[0],O_RDWR | O_CREAT,S_IRUSR | S_IWUSR);
								dup2(fd,1);
								dup2(fd,2);

								close(fd);
								if(execvp(porcess_B[0],porcess_B)==-1){
									perror("exec");
								}
							}
							if(pid_B>0){
								close(fd[0]);
								close(fd[1]);
								if(waitpid(pid_B,NULL,0)==-1){
									perror("wait");
								}
							}
							if(pid_B==-1){
							perror("fork");
							}//Process B
						}
						else{
							int fd[2];
							pipe(fd);
							char* porcess_A[3];

							porcess_A[0]=(char*)sub1.c_str();
							porcess_A[1]=(char*)sub3.c_str();
							porcess_A[2]=NULL;
							
							pid_t pid_A=fork();
							
							if(pid_A==0){
								dup2(fd[1],1);
								close(fd[0]);
								close(fd[1]);
								if(execvp(porcess_A[0],porcess_A)==-1){
									perror("exec");
								}
							}
							if(pid_A==-1){
							perror("fork");
							}//Process A

							char* porcess_B[3];

							porcess_B[0]=(char*)sub5.c_str();
							porcess_B[1]=(char*)sub6.c_str();
							porcess_B[2]=NULL;
							pid_t pid_B=fork();

							if(pid_B==0){
								dup2(fd[0],0);
								close(fd[0]);
								close(fd[1]);
								if(execvp(porcess_B[0],porcess_B)==-1){
									perror("exec");
								}
							}
							if(pid_B>0){
								close(fd[0]);
								close(fd[1]);
								if(waitpid(pid_B,NULL,0)==-1){
									perror("wait");
								}
							}
							if(pid_B==-1){
							perror("fork");
							}//Process B
						}
					}
				}
				else{
					
						char* result[3];

						result[0]=(char*)sub1.c_str();
						result[1]=(char*)sub2.c_str();
						result[2]=NULL;
						
						pid_t pid=fork();
						
						if(pid==0){
							if(execvp(result[0],result)==-1){
								perror("exec");
							}
						}
						if(pid>0){
							if(wait(0)==-1){
								perror("wait");
							}
						}
						if(pid==-1){
							perror("fork");
						}
					}
				}//ls -al
			else{
				char* result[2];

				result[0]=(char*)input.c_str();
    			result[1]=NULL;
				
				pid_t pid=fork();
				
				if(pid==0){
					if(execvp(result[0],result)==-1){
						perror("exec");
					}
				}
				if(pid>0){
					if(wait(0)==-1){
						perror("wait");
					}
				}
                if(pid==-1){
                    perror("fork");
                }
			}//ls
		}
	}
	return 0;
}
bool isCut(string command){
	for (int i = 0; i < command.length(); i++){
		if (command[i] == ' ')
			return 1;
	}
	return 0;
}//判斷是否該切割

bool isPipe(string command){
	for (int i = 0; i < command.length(); i++){
		if (command[i] == '|')
			return 1;
	}
	return 0;
}
bool isDirect_out(string command){
	for (int i = 0; i < command.length(); i++){
		if (command[i] == '>')
			return 1;
	}
	return 0;
}
bool isDirect_in(string command){
	for (int i = 0; i < command.length(); i++){
		if (command[i] == '<')
			return 1;
	}
	return 0;
}