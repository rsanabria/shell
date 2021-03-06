#include "shell.h"
#include "miShell.h"

char * argumentos[BUFFER_SIZE];
char * token;
char  prompt[6];
char historial[HISTORY][20];
int shellPid, fd;
int args;

main (){
  pthread_t history;
  char buffer[BUFFER_SIZE];
  strcpy(prompt,"#");
  prepararSenales();

  while (1){
    argumentos[0] = "\n"; //inicializar el arreglo para que no haya errores de punteros
    argumentos[1] = "\n";
    printf("[%s-%s] %s ", getlogin(), miPwd(), prompt);
    fgets(buffer, BUFFER_SIZE, stdin);	
    separa(buffer,argumentos);  

    pthread_create(&history, NULL, (void *)setHistorial, buffer);
    if (!strcmp(argumentos[0],"salir")){
      printf("Saliendo de shell...\n");	
      exit(0);
    }
    else if (!strcmp(argumentos[0], "historial")){    
      mostrarHistorial();
    }      
    else if(!strcmp(argumentos[0],"cd")){
        chdir(argumentos[1]);
	if(argumentos[1]==0) {
	char *str = getenv( "HOME" );
	if ( chdir ( str ) < 0 ) {
		fprintf( stderr , "cd: ERROR\n");
	   }
	}
    }    
    else if (!strcmp(argumentos[0], "mipid")){
      printf("Mi id de Proceso es %d\n",(int)getpid()); 
    }
    else {
      if(fork() == 0){
	redireccion();	
	if(execvp(argumentos[0], argumentos)<0 )
	  {
	    if (argumentos[0] == "\n"){}
	    else{
	      printf ("ese comando no existe\n");
	    }
	    exit(0);//matar al hijo
	  }	
      }
      /* el padre espera al hijo */
      pthread_join(history, NULL);
      wait(NULL); 	
    }
  }
}
