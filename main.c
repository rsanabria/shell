#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include "miShell.h"
#define BUFFER_SIZE 1024


//void separa( char *argumentos_buffer);
//const char * miPwd();
char * argumentos[BUFFER_SIZE];
char * token;

main ( int argc, char *argv[]){
	
	char buffer[BUFFER_SIZE];
	pid_t pid;
	char prompt;
	prompt =  '#';
	while (1){
		printf("[%s-%s] %c ", getlogin(), miPwd(), prompt);
		fflush(stdin);                    /*limpia la entrada */
		fgets(buffer, BUFFER_SIZE, stdin); /*Se obtiene el input del 
												*usuario*/
		separa(buffer,argumentos); 
		if (!strcmp(argumentos[0],"salir")){
			exit(0);
		}
		else if(!strcmp(argumentos[0],"cd")){
			chdir(argumentos[1]);
		}
		else {
		pid = fork();
		if(pid == 0){
			if(execvp(argumentos[0], argumentos)<0)
				printf ("ese comando no existe\n");
		}
/* el padre espera al hijo */
		wait();
		}
	}
	
}

//void separa( char *argumentos_buffer, argumentos){
///* Esta función recibe de argumento el buffer y va separar el buffer 
 //* en subcadenas cada vez que encuente un espacio */
	//int i = 0;
	//token = strtok(argumentos_buffer," \n");
	//while (token != NULL){
		//argumentos[i] = token;
		//i++;
		//token = strtok(NULL," \n");
	//}
	//argumentos[i] = NULL;

//}
//const char * miPwd(){
///* Funcion que consigue el actual directorio y regresa la ultima carpeta
 //* del path */         
	//char buffer[BUFFER_SIZE];
	//char *cwd;
	//char * dir;
	//char * token;
	
	//cwd = getcwd(buffer, BUFFER_SIZE);
	//token = strtok( cwd, "/");
	//while (token != NULL){
		//dir = token;
		//token = strtok(NULL,"/");
		//}
	//return dir;
//}

