#include "shell.h"
#include "miShell.h"

char * argumentos[BUFFER_SIZE];
char * token;
char  prompt[6];
int shellPid;
main (){
  
  char buffer[BUFFER_SIZE];
  strcpy(prompt,"#");
  prepararSenales();
  
  while (1){
	argumentos[0] = "\n"; //inicializar el arreglo para que no haya errores de punteros
	argumentos[1] = "\n";
	printf("[%s-%s] %s ", getlogin(), miPwd(), prompt);
	fgets(buffer, BUFFER_SIZE, stdin);
		separa(buffer,argumentos);

	if (!strcmp(argumentos[0],"salir")){
		exit(0);
    }
    else if(!strcmp(argumentos[0],"cd")){
      chdir(argumentos[1]);
    }

	else if (!strcmp(argumentos[0], "kill") ){
		shellPid =(int) getpid();
		if (!strcmp(argumentos[1],"-30") || !strcmp(argumentos[1],"-31") || !strcmp(argumentos[1],"-32") )
			{
				
				printf("%s", argumentos[1]);
				//sprintf(argumentos[2], "%d",shellPid);
				
				}
				
		execvp(argumentos[0], argumentos);
		
			}
    else {
		
	  
      if(fork() == 0){
		redireccion();
		if(execvp(argumentos[0], argumentos)<0 ){
			if (argumentos[0] == "\n"){}
			else{
			printf ("ese comando no existe\n");
			}
			exit(0);//matar al hijo
		}

      }
      /* el padre espera al hijo */
       wait(NULL); 	
    }
}
}
