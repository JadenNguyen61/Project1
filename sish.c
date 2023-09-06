#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>

 int historySize = 0;
 char* historyCommands[100];

void parseLine(char* line, char* args[]){
    
		
		
		char* arg;
		int i = 0;

		arg = strtok(line, " ");
		
		while(arg != NULL && i < 100){
			args[i++] = arg;
			arg = strtok(NULL, " ");
	
		}

 		args[i] = NULL;
}

void execCommand(char* args[]){
  		if(strcmp(args[0], "exit") == 0){
			printf("exiting\n");
			return;
		}
		else if(strcmp(args[0], "cd") == 0){
			char* path = args[1];
			int result = chdir(path);
			if(result == -1){
				printf("Error changing directory\n");
			}
			printf(getcwd(NULL,0));
			printf("\n");
		}
		else if(strcmp(args[0], "history") == 0){
			printf("history called\n");
			
			//Printing history
      if(args[1] == NULL){
   			for(int i = 0; i < historySize; i++){
			    printf("%d %s\n", i, historyCommands[i]);
          
			}
      }else{  //Clearing History and offset
        
				if((strcmp(args[1], "-c") == 0)){
					historySize = 0;
				}else{
          int offset = atoi(args[1]);
          char* histArgs[100];
          parseLine(historyCommands[offset], histArgs);
          execCommand(histArgs);
        }
  }

	



				
		}
		else{
			pid_t pid;
			int status;

			pid = fork();

			if(pid == 0){ //Child process 
				execvp(args[0], args);
				return;
			}
			else{	//Parent process
				waitpid(pid, &status,0);
			}
		}
}

int main(int argc, char* argv[]){
	printf("dont execture this on cs1 we will lose points or something \n");

	while(1){
		printf("sish> ");

		// gets inputfrom line and converst to args
   char* line = NULL;
		size_t size = 0;
		ssize_t lineSize;
		
 
    
    

		lineSize = getline(&line, &size, stdin);
		if(lineSize == -1){
			printf("failed to read line");
			break;
		}
   
   char* newLine = strchr(line, '\n');

		if(newLine != NULL){
			*newLine = '\0';
		}
    
    char* args[100];
    parseLine(line, args);
    
    
 			//Hisory Shifting commands past 100
			if(historySize >= 100){
				for(int i = 0; i < 99; i++){
					strcpy(historyCommands[i], historyCommands[i+1]);	
          historyCommands[historySize] = line;
				} 
			}else {
          historyCommands[historySize] = line;
          historySize++;
      }
      
    
		//Switch statment (not relly you cant use those nicely for strings) for deciding if the input is   a exe or a command
    execCommand(args);

  

	}
}
