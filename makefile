HEADERS = header.h
OBJECTS = program.o

default: program

program.o: source.c $(HEADERS)
	gcc -c source.c -o program.o

program: program.o
	gcc program.o -o program

clean:
	-rm -f $(OBJECTS)
	-rm -f program
