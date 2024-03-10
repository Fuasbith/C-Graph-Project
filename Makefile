CC = gcc
CFLAGS = -g -ansi -pedantic-errors -Wall -fstack-protector-all -Werror 

all: public01.x public02.x public03.x public04.x public05.x \
	public06.x public07.x public08.x public09.x public10.x

public01.x: public01.o string-graph.o compare-vertex-lists.o
	$(CC) public01.o string-graph.o compare-vertex-lists.o \
	-o public01.x

public02.x: public02.o string-graph.o 
	$(CC) public02.o string-graph.o -o public02.x

public03.x: public03.o string-graph.o compare-vertex-lists.o
	$(CC) public03.o string-graph.o compare-vertex-lists.o \
	-o public03.x

public04.x: public04.o string-graph.o 
	$(CC) public04.o string-graph.o -o public04.x

public05.x: public05.o string-graph.o compare-vertex-lists.o \
	memory-functions.o
	$(CC) public05.o string-graph.o compare-vertex-lists.o \
	memory-functions.o -o public05.x

public06.x: public06.o string-graph.o memory-functions.o
	$(CC) public06.o string-graph.o memory-functions.o \
	-o public06.x

public07.x: public07.o string-graph.o compare-vertex-lists.o \
	memory-functions.o
	$(CC) public07.o string-graph.o compare-vertex-lists.o \
	memory-functions.o -o public07.x

public08.x: public08.o string-graph.o memory-functions.o
	$(CC) public08.o string-graph.o memory-functions.o \
	-o public08.x

public09.x: public09.o string-graph.o compare-vertex-lists.o \
	memory-functions.o
	$(CC) public09.o string-graph.o compare-vertex-lists.o \
	memory-functions.o -o public09.x

public10.x: public10.o string-graph.o compare-vertex-lists.o \
	memory-functions.o
	$(CC) public10.o string-graph.o compare-vertex-lists.o \
	memory-functions.o -o public10.x


#string-graph.h: string-graph-datastructure.h
#	touch string-graph.h
#The above is another possibility as compared to putting
#string-graph-datastructure.h into every .o dependency line
#This is b/c string-graph.h includes string-graph-datastructure.h

string-graph.o: string-graph.c string-graph.h string-graph-datastructure.h
	$(CC) $(CFLAGS) -c string-graph.c

public01.o: public01.c string-graph.h compare-vertex-lists.h \
	string-graph-datastructure.h
	$(CC) $(CFLAGS) -c public01.c

public02.o: public02.c string-graph.h string-graph-datastructure.h
	$(CC) $(CFLAGS) -c public02.c

public03.o: public03.c string-graph.h compare-vertex-lists.h \
	string-graph-datastructure.h
	$(CC) $(CFLAGS) -c public03.c

public04.o: public04.c string-graph.h string-graph-datastructure.h
	$(CC) $(CFLAGS) -c public04.c

public05.o: public05.c string-graph.h compare-vertex-lists.h \
	memory-functions.h string-graph-datastructure.h
	$(CC) $(CFLAGS) -c public05.c

public06.o: public06.c string-graph.h memory-functions.h \
	string-graph-datastructure.h
	$(CC) $(CFLAGS) -c public06.c

public07.o: public07.c string-graph.h compare-vertex-lists.h \
	memory-functions.h string-graph-datastructure.h
	$(CC) $(CFLAGS) -c public07.c

public08.o: public08.c string-graph.h memory-functions.h \
	string-graph-datastructure.h
	$(CC) $(CFLAGS) -c public08.c

public09.o: public09.c string-graph.h compare-vertex-lists.h \
	memory-functions.h string-graph-datastructure.h
	$(CC) $(CFLAGS) -c public09.c

public10.o: public10.c string-graph.h compare-vertex-lists.h \
	memory-functions.h string-graph-datastructure.h
	$(CC) $(CFLAGS) -c public10.c

clean:	
	- rm public*.o *.x string-graph.o string-graph.c.* \
        string-graph-datastructure.h.* Makefile.*
