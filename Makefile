CC:=gcc
CFLAGS:=-g3 -Wall -pedantic -std=c99
LDFLAGS:=
MFLAGS:=-Dcost_type="int"
SOURCES:=scgl_attr.c scgl_edge.c scgl_vertex.c scgl_graph.c
OBJECTS:=$(SOURCES:.c=.o)
EXECUTABLE:=test

ifneq (,$(findstring short,$(MFLAGS)))
	override MLAGS+="-Dcost_fmt=\"%hd\""
endif
ifneq (,$(findstring unsigned short,$(MFLAGS)))
	override MFLAGS+="-Dcost_fmt=\"%hd\""
endif
ifneq (,$(findstring int,$(MFLAGS)))
	override MFLAGS+="-Dcost_fmt=\"%d\""
endif
	ifneq (,$(findstring unsigned int,$(MFLAGS)))
	override MFLAGS+="-Dcost_fmt=\"%d\""
endif
ifneq (,$(findstring long,$(MFLAGS)))
	override MFLAGS+="-Dcost_fmt=\"%ld\""
endif
ifneq (,$(findstring unsigned long,$(MFLAGS)))
	override MFLAGS+="-Dcost_fmt=\"%ld\""
endif
ifneq (,$(findstring long long,$(MFLAGS)))
	override MFLAGS+="-Dcost_fmt=\"%lld\""
endif
ifneq (,$(findstring unsigned long long,$(MFLAGS)))
	override MFLAGS+="-Dcost_fmt=\"%lld\""
endif
ifneq (,$(findstring float,$(MFLAGS)))
	override MFLAGS+="-Dcost_fmt=\"%f\""
endif
ifneq (,$(findstring double,$(MFLAGS)))
	override MFLAGS+="-Dcost_fmt=\"%f\""
endif
ifneq (,$(findstring long double,$(MFLAGS)))
	override MFLAGS+="-Dcost_fmt=\"%Lf\""
endif


all: $(EXECUTABLE)

$(EXECUTABLE): test.c $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(MFLAGS) $^ -o $@

$(OBJECTS): $(SOURCES)
	$(CC) $(CFLAGS) $(MFLAGS) -c $*.c -o $@

clean:
	rm -rf *.o test
