CC:=gcc
CFLAGS:=-g3 -Wall -pedantic -std=c99
LDFLAGS:=
MFLAGS:=-Dweight_type="int" -Dweight_fmt=\"%d\"
SOURCES:=simclist.c scgl_edge.c scgl_pair.c scgl_vertex.c scgl_graph.c
OBJECTS:=$(SOURCES:.c=.o)
EXECUTABLE:=test

all: $(EXECUTABLE)

$(EXECUTABLE): test.c $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(MFLAGS) $^ -o $@

$(OBJECTS): $(SOURCES)
	$(CC) $(CFLAGS) $(MFLAGS) -c $*.c -o $@

clean:
	rm -rf *o test
