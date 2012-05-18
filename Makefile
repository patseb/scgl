TOPDIR=./
CC:=gcc
CFLAGS:=-I$(TOPDIR)include/ -s -Os -Wall -pedantic -std=c99
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

all: $(LIBRARY) tests

$(LIBRARY): $(OBJECTS)
	@echo "Linking object files into $(TOPDIR)lib/lib$(LIBRARY).a library"
	@mkdir -p $(TOPDIR)lib
	@ar sr $(TOPDIR)lib/lib$(LIBRARY).a $^

$(OBJECTS): $(SOURCES)
	@echo "Building $@ object"
	@$(CC) $(CFLAGS) $(MFLAGS) -c $*.c -o $@

tests:
	@echo "Building DejaGNU's tests interface"
	@$(CC) $(CFLAGS) $(MFLAGS) $(TOPDIR)unit_tests/scgl.test/tests.c -o $(TOPDIR)unit_tests/scgl.test/tests.out $(TOPDIR)lib/libscgl.a
	@echo "Running DejaGNU tests"
	runtest --tool scgl TEST_APP=$(TOPDIR)unit_tests/scgl.test/tests.out --srcdir=$(TOPDIR)unit_tests/ --outdir=$(TOPDIR)unit_tests/ --all test.exp

test: $(LIBRARY)
	$(CC) $(CFLAGS) $(MFLAGS) $(TOPDIR)perf_tests/mem_size_d.c -o $(TOPDIR)perf_tests/mem_size_d_c $(TOPDIR)lib/libscgl.a
	$(CC) $(CFLAGS) $(MFLAGS) $(TOPDIR)perf_tests/mem_size_u.c -o $(TOPDIR)perf_tests/mem_size_u_c $(TOPDIR)lib/libscgl.a
	$(CC) $(CFLAGS) $(MFLAGS) $(TOPDIR)perf_tests/mem_speed_d.c -o $(TOPDIR)perf_tests/mem_speed_d_c $(TOPDIR)lib/libscgl.a
	$(CC) $(CFLAGS) $(MFLAGS) $(TOPDIR)perf_tests/mem_speed_u.c -o $(TOPDIR)perf_tests/mem_speed_u_c $(TOPDIR)lib/libscgl.a
	$(CC) $(CFLAGS) $(MFLAGS) $(TOPDIR)perf_tests/d_u.c -o $(TOPDIR)perf_tests/d_u_c $(TOPDIR)lib/libscgl.a
	$(CC) $(CFLAGS) $(MFLAGS) $(TOPDIR)perf_tests/d_d.c -o $(TOPDIR)perf_tests/d_d_c $(TOPDIR)lib/libscgl.a

clean:
	@echo "Removing object (src/), library (lib/), and tests files"
	@rm -rf $(TOPDIR)src/*.o
	@rm -rf $(TOPDIR)lib/libscgl.a
	@rm -rf $(TOPDIR)unit_tests/scgl.test/tests.out
	@rm -rf $(TOPDIR)unit_tests/scgl.log $(TOPDIR)unit_tests/scgl.sum
