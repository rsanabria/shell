#ifndef _MISHELL_H_   /* Include guard */
#define _MISHELL_H_
#include <unistd.h>
#include <string.h>
#define BUFFER_SIZE 1024

void separa( char *argumentos_buffer,char  *argumentos[]){
/* Esta función recibe de argumento el buffer y va separar el buffer 
 * en subcadenas cada vez que encuente un espacio */
	int i = 0;
	char * token;
	
	token = strtok(argumentos_buffer," \n");
	while (token != NULL){
		argumentos[i] = token;
		i++;
		token = strtok(NULL," \n");
	}
	argumentos[i] = NULL;

}
const char * miPwd(){
/* Funcion que consigue el actual directorio y regresa la ultima carpeta
 * del path */         
	char buffer[BUFFER_SIZE];
	char *cwd;
	char * dir;
	char * token;
	
	cwd = getcwd(buffer, BUFFER_SIZE);
	token = strtok( cwd, "/");
	while (token != NULL){
		dir = token;
		token = strtok(NULL,"/");
		}
	return dir;
}

#endif
