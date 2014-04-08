
extern char prompt[6];
extern char * argumentos[BUFFER_SIZE];
extern char historial[100][20];
extern int fd;
extern int args;
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
	char *infile, *outfile, *outa, *outerr, *outamp;
	char **cp;
	int status;
	infile = NULL;
        outfile = NULL;
	outa = NULL;
	outerr = NULL;
	outamp = NULL;

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
	  else if (strcmp(*cp, ">>") == 0){
                if (*(cp+1) == NULL){
                    fprintf(stderr, "Debes especificar un archivo de salida\n");
	            break;
                }
                *cp++ = NULL;
                outa = *cp;
        }

	else if (strcmp(*cp, "2>") == 0){
                if (*(cp+1) == NULL){
                    fprintf(stderr, "Debes especificar un archivo de salida\n");
	            break;
                }
                *cp++ = NULL;
                outerr = *cp;
        }        

	else if (strcmp(*cp, "&>") == 0){
                if (*(cp+1) == NULL){
                    fprintf(stderr, "Debes especificar un archivo de salida\n");
	            break;
                }
                *cp++ = NULL;
                outamp = *cp;
            	}
        }
	status = execute(argumentos, infile, outfile, outa, outerr, outamp);
}


int execute(char **argumentos, char *infile, char *outfile, char *outfilea, char *outfilerr, char *outfileamp)
{
    int status;
    int in, out, outa, outerr, outamp;
    in = -1;
    out = -1;
    outa = -1;
    outerr = -1;
    outamp = -1;
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

    if (outfilea != NULL) {
        if ((outa = open(outfilea, 0666)) < 0) {
            close(in);
            return(-1);
        }
    }

    if (outfilerr != NULL) {
        if ((outerr = creat(outfilerr, 0666)) < 0) {
            close(in);
            return(-1);
        }
    }

    if (outfileamp != NULL) {
        if ((outamp = creat(outfileamp, 0666)) < 0) {
            close(in);
            return(-1);
        }
    }
   //Hacer redireccionamientos
        if (in > 0){
            dup2(in, 0);
	}

        if (out > 0)
            dup2(out, 1);   

	if(outa > 0)
	      freopen(outfilea, "a+", stdout);  

	if(outerr > 0)
	      freopen(outfilerr, "w+", stderr);  

	if(outamp > 0){
	      freopen(outfileamp, "w+", stderr);  
	      freopen(outfileamp, "w+", stdout);  
 	}
	// Cerrar los descriptores
    close(out);
    close(in);
    close(outa);
    close(outerr);
    close(outamp);
 
    return(status);
}


 void mostrarHistorial(void)
    {
        int i = 0;
        while(historial[i][0])
        {
                printf("%d  %s\n", i+1, *(historial + i));
                i++;
        }
}

void setHistorial(char *arg)
{
	// Guardar el historial desde linea de comandos
        int i = 0;
	FILE *fp;
	fp = fopen("/home/edgarmch/tmp/archivo.txt","w");
        while(historial[i][0])
            {
		fprintf(fp, "%s\n", *(historial + i) );
             	i++;
            }
        strcpy(historial[i], arg);
	fclose(fp);
}
