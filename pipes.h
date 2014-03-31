tee(char *argumento)
{
  pid_t pid;
  int p[2], readbytes, stream;
  char buffer[BUFFER_SIZE], buffer2[BUFFER_SIZE];
  FILE *fp;
  pipe( p );

  if ( (pid=fork()) == 0 )
  { 
    close( p[1] ); 
    fp=fopen(argumento, "w");
    while( (readbytes=read( p[0], buffer, BUFFER_SIZE )) > 0)
      {
	write( 1, buffer, readbytes );
	fprintf(fp,"%s",buffer);
      }
    fclose(fp);
    close( p[0] );    
  }
  else
  { 
    close( p[0] ); 
    dup2(0,p[0]);
    while( (readbytes=read( p[0], buffer, BUFFER_SIZE )) > 0)
      write( p[1], buffer, strlen( buffer ) );    
    close( p[1] );
  }
  waitpid( pid, NULL, 0 );
  exit( 0 );
}
