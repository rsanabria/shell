extern char * argumentos[BUFFER_SIZE];

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

void redireccion(){
	char *infile, *outfile;
	char **cp;
	int status;
	infile = NULL;
        outfile = NULL;

        for (cp = argumentos; *cp != NULL; cp++){
            if (strcmp(*cp, "<") == 0){
                if (*(cp+1) == NULL){
                    fprintf(stderr, "You must specify ");
                    fprintf(stderr, "an input file.\n");
                }
                *cp++ = NULL;
                infile = *cp;
            	}
            else if (strcmp(*cp, ">") == 0){
                if (*(cp+1) == NULL){
                    fprintf(stderr, "You must specify ");
                    fprintf(stderr, "an output file.\n");
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
    int infd, outfd;
    infd = -1;
    outfd = -1;
    /*
     * If an input file was given, open it.
     */
    if (infile != NULL) {
        if ((infd = open(infile, O_RDONLY)) < 0) {
            perror(infile);
            return(-1);
        }
    }

    /*
     * If an output file was given, create it.
     */
    if (outfile != NULL) {
        if ((outfd = creat(outfile, 0666)) < 0) {
            perror(outfile);
            close(infd);
            return(-1);
        }
    }
        /*
         * Perform output redirection.
         */
        if (infd > 0)
            dup2(infd, 0);

        if (outfd > 0)
            dup2(outfd, 1);   

    /*
     * Close file descriptors.
     */
    close(outfd);
    close(infd);
 
    return(status);
}


