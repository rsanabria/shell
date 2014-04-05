#include "shell.h"
#include "miShell.h"

char * argumentos[BUFFER_SIZE];
char * token;

main ( int argc, char *argv[]){
  
  char buffer[BUFFER_SIZE];
  pid_t pid;
  char prompt;
  prompt = '#';
  while (1){
    printf("[%s-%s] %c ", getlogin(), miPwd(), prompt);
    fflush(stdin); /*limpia la entrada */
    fgets(buffer, BUFFER_SIZE, stdin); /*Se obtiene el input del
					*usuario*/
    separa(buffer,argumentos);
    if (!strcmp(argumentos[0],"salir")){
      exit(0);
    }
    else if(!strcmp(argumentos[0],"cd")){
      chdir(argumentos[1]);
    }

    else if(strcmp(buffer, "clear\n")==0){
        system("clear");    
        continue;   
    }
    //else if(!strcmp(argumentos[
    else { 
      pid = fork();
      if(pid == 0){
	redireccion();
	if(execvp(argumentos[0], argumentos)<0){
	  printf ("ese comando no existe\n");
	  exit(0);//matar al hijo
	}
      }
      /* el padre espera al hijo */
      else{ wait(); }	
    }
  }  
}
