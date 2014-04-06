TARGET = shell
FLAGS = -lpthread
OBJECTS= main.c
HEADERS= miShell.h pipes.h shell.h
CC= gcc
.PHONY= clean



shell:  $(OBJECTS) $(HEADERS)
	$(CC) $(FLAGS) $(OBJECTS) -o shell

clean:
	rm -f  *.o *.c~ *.o~ *.h~ Makefile~ *.txt
