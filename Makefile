CC:=gcc
CFLAGS:=-g3 -Wall -pedantic -std=c99
LDFLAGS:=
MFLAGS:=-Dcost_type="int"
SOURCES:=pqueue.c scgl_attr.c scgl_edge.c scgl_vertex.c scgl_graph.c scgl_algorithms.c
OBJECTS:=$(SOURCES:.c=.o)
EXECUTABLE:=test

ifneq (,$(findstring short,$(MFLAGS)))
	override MLAGS+=-Dcost_fmt=\"%hd\" -Dcost_max=SHRT_MAX
endif
ifneq (,$(findstring unsigned short,$(MFLAGS)))
	override MFLAGS+=-Dcost_fmt=\"%hd\" -Dcost_max=USHRT_MAX
endif
ifneq (,$(findstring int,$(MFLAGS)))
	override MFLAGS+=-Dcost_fmt=\"%d\" -Dcost_max=INT_MAX
endif
	ifneq (,$(findstring unsigned int,$(MFLAGS)))
	override MFLAGS+=-Dcost_fmt=\"%d\" -Dcost_max=UINT_MAX
endif
ifneq (,$(findstring long,$(MFLAGS)))
	override MFLAGS+=-Dcost_fmt=\"%ld\" -Dcost_max=LONG_MAX
endif
ifneq (,$(findstring unsigned long,$(MFLAGS)))
	override MFLAGS+=-Dcost_fmt=\"%ld\" -Dcost_max=ULONG_MAX
endif
ifneq (,$(findstring long long,$(MFLAGS)))
	override MFLAGS+=-Dcost_fmt=\"%lld\" -Dcost_max=LLONG_MAX
endif
ifneq (,$(findstring unsigned long long,$(MFLAGS)))
	override MFLAGS+=-Dcost_fmt=\"%lld\" -Dcost_max=ULLONG_MAX
endif
ifneq (,$(findstring float,$(MFLAGS)))
	override MFLAGS+=-Dcost_fmt=\"%f\" -Dcost_max=FLT_MAX
endif
ifneq (,$(findstring double,$(MFLAGS)))
	override MFLAGS+=-Dcost_fmt=\"%f\" -Dcost_max=DBL_MAX
endif
ifneq (,$(findstring long double,$(MFLAGS)))
	override MFLAGS+=-Dcost_fmt=\"%Lf\" -Dcost_max=LDBL_MAX
endif


all: $(EXECUTABLE)

$(EXECUTABLE): test.c $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(MFLAGS) $^ -o $@

$(OBJECTS): $(SOURCES)
	$(CC) $(CFLAGS) $(MFLAGS) -c $*.c -o $@

clean:
	rm -rf *.o test
