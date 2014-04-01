TARGET = shell
OBJECTS= main.c
HEADERS= miShell.h pipes.h shell.h
CC= gcc
.PHONY= clean



shell:  $(OBJECTS) $(HEADERS)
	$(CC) $(OBJECTS) -o shell

clean:
	rm -f  *.o *.c~ *.o~ *.h~ Makefile~
