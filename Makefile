CC:=gcc
CFLAGS:=-s -O2 -Wall -pedantic -std=c99
LDFLAGS:=
MFLAGS:=
COST_TYPE:=ui
SOURCES:=pqueue.c scgl_attr.c scgl_edge.c scgl_vertex.c scgl_graph.c scgl_algorithms.c
OBJECTS:=$(SOURCES:.c=.o)
EXECUTABLE:=test

ifneq (,$(findstring s,$(COST_TYPE)))
	override MFLAGS:=-Dcost_type="short" -Dcost_fmt=\"%hd\" -Dcost_max=SHRT_MAX
endif
ifneq (,$(findstring us,$(COST_TYPE)))
	override MFLAGS:=-Dcost_type="unsigned short" -Dcost_fmt=\"%hd\" -Dcost_max=USHRT_MAX
endif
ifneq (,$(findstring i,$(COST_TYPE)))
	override MFLAGS:=-Dcost_type="int" -Dcost_fmt=\"%d\" -Dcost_max=INT_MAX
endif
ifneq (,$(findstring ui,$(COST_TYPE)))
	override MFLAGS:=-Dcost_type="unsigned int" -Dcost_fmt=\"%d\" -Dcost_max=UINT_MAX
endif
ifneq (,$(findstring long,$(COST_TYPE)))
	override MFLAGS:=-Dcost_type="long" -Dcost_fmt=\"%ld\" -Dcost_max=LONG_MAX
endif
ifneq (,$(findstring ul,$(COST_TYPE)))
	override MFLAGS:=-Dcost_type="unsigned long" -Dcost_fmt=\"%ld\" -Dcost_max=ULONG_MAX
endif
ifneq (,$(findstring ll,$(COST_TYPE)))
	override MFLAGS:=-Dcost_type="long long" -Dcost_fmt=\"%lld\" -Dcost_max=LLONG_MAX
endif
ifneq (,$(findstring ull,$(COST_TYPE)))
	override MFLAGS:=-Dcost_type="unsigned long long" -Dcost_fmt=\"%lld\" -Dcost_max=ULLONG_MAX
endif
ifneq (,$(findstring f,$(COST_TYPE)))
	override MFLAGS:=-Dcost_type="float" -Dcost_fmt=\"%f\" -Dcost_max=FLT_MAX
endif
ifneq (,$(findstring d,$(COST_TYPE)))
	override MFLAGS:=-Dcost_type="double" -Dcost_fmt=\"%f\" -Dcost_max=DBL_MAX
endif
ifneq (,$(findstring ld,$(COST_TYPE)))
	override MFLAGS:=-Dcost_type="long double" -Dcost_fmt=\"%Lf\" -Dcost_max=LDBL_MAX
endif

all: $(EXECUTABLE)

$(EXECUTABLE): test.c $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(MFLAGS) $^ -o $@

$(OBJECTS): $(SOURCES)
	$(CC) $(CFLAGS) $(MFLAGS) -c $*.c -o $@

clean:
	rm -rf *.o test

#ifneq (,$(findstring long,$(COST_TYPE))) 
#%	ifneq (,$(findstring long long,$(COST_TYPE))) 
#%		override MFLAGS:=-Dcost_fmt=\"%lld\" -Dcost_max=LLONG_MAX 
#%	endif 
#%		override MFLAGS:=-Dcost_fmt=\"%ld\" -Dcost_max=LONG_MAX 
#%	endif 
#%endif OR 
#%ifneq (long long,$(findstring long long,$(COST_TYPE))) override MFLAGS="EXACTMATCH" endif –  
