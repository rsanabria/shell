
OBJECTS: main.c
HEADERS: miShell.h pipes.h shell.h
CC: gcc
.PHONY: clean

all: shell

shell:  $(OBJECTS) $(HEADERS)
	$(CC) $(OBJECTS) -o shell

clean:
	rm -f  $(OBJECTS) *.o *.o~ *.h~ Makefile~
