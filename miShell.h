
extern char prompt[6];
extern char * argumentos[BUFFER_SIZE];
extern char historial[100][20];
extern int fd;
void separa( char *argumentos_buffer,char  *argumentos[]){
/* Esta función recibe de argumento el buffer y va separar el buffer 
 * en subcadenas cada vez que encuente un espacio */
	int i = 0;
	char * token;
	if (!strcmp(argumentos_buffer,"\n")){
		}
	else{
	token = strtok(argumentos_buffer," \n");
	while (token != NULL){
		argumentos[i] = token;
		i++;
		token = strtok(NULL," \n");
	}
	argumentos[i] = NULL;
}
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
void cambiarPrompt(int signal){
	
	switch(signal){
		case 30:
			strcpy(prompt,"%");
			break;
		case 31:
			strcpy(prompt,":)");
			break;
		case 32:
			strcpy(prompt,":0");
			break;
		default:
			break;
		}
	}
void prepararSenales(){
	int i;
	for(i=30;i<33;i++){
		signal(i,cambiarPrompt);
	
	}
}
void redireccion(){
	char *infile, *outfile;
	char **cp;
	int status;
	infile = NULL;
        outfile = NULL;

        for (cp = argumentos; *cp != NULL; cp++){
            if (strcmp(*cp, "<") == 0){
                if (*(cp+1) == NULL){
                    fprintf(stderr,"Debes especificar un archivo de entrada\n");
			break;
                }
                *cp++ = NULL;
                infile = *cp;
            	}
            else if (strcmp(*cp, ">") == 0){
                if (*(cp+1) == NULL){
                    fprintf(stderr, "Debes especificar un archivo de salida\n");
	            break;
                }
                *cp++ = NULL;
                outfile = *cp;
            	}
        }
	status = execute(argumentos, infile, outfile);
}


int execute(char **argumentos, char *infile, char *outfile)
{
    int status;
    int in, out;
    in = -1;
    out = -1;
    //Si un archivo de entrada fue recibido, abrirlo
    if (infile != NULL) {
        if ((in = open(infile, O_RDONLY)) < 0) {
            perror(infile);
            return(-1);
        }
    }

    //Si un archivo de salida fue recibido, crearlo
    if (outfile != NULL) {
        if ((out = creat(outfile, 0666)) < 0) {
            close(in);
            return(-1);
        }
    }
   //Hacer el direccionamiento de salida
        if (in > 0)
            dup2(in, 0);

        if (out > 0)
            dup2(out, 1);   

	// Cerrar los descriptores
    close(out);
    close(in);
 
    return(status);
}


 void mostrarHistorial(void)
    {
        int i = 0;

        while(historial[i][0] != '\0')
        {
                printf("%d  %s\n", i+1, *(historial + i));
                i++;
        }
}

void setHistorial(char *arg)
{
	char historialCuenta;   
	// Guardar el historial desde linea de comandos
        int i = 0;

        while(historial[i][0] != '\0')
            {
             i++;
            }
        strcpy(historial[i], arg);
        historialCuenta++;
}

void writer(char *buffer)
{
	int fd;
	char *myfifo="/tmp/myfifo";
	mkfifo(myfifo, 0666);
	fd=open(myfifo, O_WRONLY);
	write(fd, buffer, sizeof(BUFFER_SIZE));
	close(fd);
	unlink(myfifo);
}

void reader(int fd)
{
	char *myfifo="/tmp/myfifo";
	char buf[BUFFER_SIZE];
	if(fork() == 0){
	
	read(fd, buf, BUFFER_SIZE);
	printf("Recibido: %s\n", buf);
	unlink(myfifo);
	}
	//close(fd);
}



