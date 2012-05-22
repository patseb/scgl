TOPDIR=./
CC:=gcc
CFLAGS:=-I$(TOPDIR)include/ -I/usr/include/igraph -s -Os -Wall -pedantic -std=c99
CXX=g++
CXXFLAGS:=-s -Os -Wall -pedantic
LDFLAGS:=-ligraph
MFLAGS:=
COST_TYPE:=ui
SOURCES:=$(sort \
           $(TOPDIR)src/pqueue.c \
           $(TOPDIR)src/scgl_attr.c \
           $(TOPDIR)src/scgl_edge.c \
           $(TOPDIR)src/scgl_vertex.c \
           $(TOPDIR)src/scgl_graph.c \
           $(TOPDIR)src/scgl_algorithms.c \
         )
OBJECTS:=$(SOURCES:.c=.o)

ifneq (,$(findstring s,$(COST_TYPE)))
	override MFLAGS:=-Dcost_type="short" -Dcost_fmt=\"%hd\" -Dcost_max=SHRT_MAX -Dcost_min=SHRT_MIN
endif
ifneq (,$(findstring us,$(COST_TYPE)))
	override MFLAGS:=-Dcost_type="unsigned short" -Dcost_fmt=\"%hd\" -Dcost_max=USHRT_MAX -Dcost_min=USHRT_MIN
endif
ifneq (,$(findstring i,$(COST_TYPE)))
	override MFLAGS:=-Dcost_type="int" -Dcost_fmt=\"%d\" -Dcost_max=INT_MAX -Dcost_min=INT_MIN
endif
ifneq (,$(findstring ui,$(COST_TYPE)))
	override MFLAGS:=-Dcost_type="unsigned int" -Dcost_fmt=\"%d\" -Dcost_max=UINT_MAX -Dcost_min=UINT_MIN
endif
ifneq (,$(findstring l,$(COST_TYPE)))
	override MFLAGS:=-Dcost_type="long" -Dcost_fmt=\"%ld\" -Dcost_max=LONG_MAX -Dcost_min=LONG_MIN
endif
ifneq (,$(findstring ul,$(COST_TYPE)))
	override MFLAGS:=-Dcost_type="unsigned long" -Dcost_fmt=\"%ld\" -Dcost_max=ULONG_MAX -Dcost_min=ULONG_MIN
endif
ifneq (,$(findstring ll,$(COST_TYPE)))
	override MFLAGS:=-Dcost_type="long long" -Dcost_fmt=\"%lld\" -Dcost_max=LLONG_MAX -Dcost_min=LLONG_MIN
endif
ifneq (,$(findstring ull,$(COST_TYPE)))
	override MFLAGS:=-Dcost_type="unsigned long long" -Dcost_fmt=\"%lld\" -Dcost_max=ULLONG_MAX -Dcost_min=ULLONG_MIN
endif
ifneq (,$(findstring f,$(COST_TYPE)))
	override MFLAGS:=-Dcost_type="float" -Dcost_fmt=\"%f\" -Dcost_max=FLT_MAX -Dcost_min=FLT_MIN
endif
ifneq (,$(findstring d,$(COST_TYPE)))
	override MFLAGS:=-Dcost_type="double" -Dcost_fmt=\"%f\" -Dcost_max=DBL_MAX -Dcost_min=DBL_MIN
endif
ifneq (,$(findstring ld,$(COST_TYPE)))
	override MFLAGS:=-Dcost_type="long double" -Dcost_fmt=\"%Lf\" -Dcost_max=LDBL_MAX -Dcost_min=LDBL_MIN
endif

.PHONY: all clean tests scgl

all: scgl

scgl: $(OBJECTS)
	@echo "Linking object files into $(TOPDIR)lib/libscgl.a library"
	@mkdir -p $(TOPDIR)lib
	@ar sr $(TOPDIR)lib/libscgl.a $^

$(OBJECTS): $(SOURCES)
	@echo "Building $@ object"
	@$(CC) $(CFLAGS) $(MFLAGS) -c $*.c -o $@

tests: scgl
	@echo "Building DejaGNU's tests interface"
	@$(CC) $(CFLAGS) $(MFLAGS) $(TOPDIR)unit_tests/scgl.test/tests.c -o $(TOPDIR)unit_tests/scgl.test/tests.out $(TOPDIR)lib/libscgl.a
	@echo "Running DejaGNU tests"
	runtest --tool scgl TEST_APP=$(TOPDIR)unit_tests/scgl.test/tests.out --srcdir=$(TOPDIR)unit_tests/ --outdir=$(TOPDIR)unit_tests/ --all test.exp

clean::
	@echo "Removing object (src/), library (lib/), and DejaGNU's test files"
	@rm -rf $(TOPDIR)src/*.o
	@rm -rf $(TOPDIR)lib/libscgl.a
	@rm -rf $(TOPDIR)unit_tests/scgl.test/tests.out
	@rm -rf $(TOPDIR)unit_tests/scgl.log $(TOPDIR)unit_tests/scgl.sum
