TOPDIR=./
CC:=gcc
CFLAGS:=-I$(TOPDIR)include/ -g3 -Wall -pedantic -std=c99
LDFLAGS:=
MFLAGS:=
COST_TYPE:=ui
SOURCES:=$(TOPDIR)src/pqueue.c \
		$(TOPDIR)src/scgl_attr.c \
		$(TOPDIR)src/scgl_edge.c \
		$(TOPDIR)src/scgl_vertex.c \
		$(TOPDIR)src/scgl_graph.c \
		$(TOPDIR)src/scgl_algorithms.c
OBJECTS:=$(SOURCES:.c=.o)
LIBRARY:=scgl

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
ifneq (,$(findstring l,$(COST_TYPE)))
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

all: $(LIBRARY)

$(LIBRARY): $(OBJECTS)
#$(CC) $(CFLAGS) $(LDFLAGS) $(MFLAGS) $^ -o $@
	ar sr $(TOPDIR)lib/lib$(LIBRARY).a $^

$(OBJECTS): $(SOURCES)
	$(CC) $(CFLAGS) $(MFLAGS) -c $*.c -o $@

tests: $(LIBRARY)
	$(CC) $(CFLAGS) $(MFLAGS) $(TOPDIR)tests/scgl.test/tests.c -o $(TOPDIR)tests/scgl.test/tests.out $(TOPDIR)lib/libscgl.a
	runtest --tool scgl TEST_APP=$(TOPDIR)tests/scgl.test/tests.out --srcdir=./tests/ --outdir=./tests/ --all test01.exp test02.exp test03.exp test04.exp test05.exp

clean:
	rm -rf $(TOPDIR)src/*.o
	rm -rf $(TOPDIR)lib/libscgl.a
	rm -rf $(TOPDIR)testsuite/tests/tests
