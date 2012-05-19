override TOPDIR=../
SCGL_SRC:=$(sort \
            $(TOPDIR)perf_tests/mem_size_d_s.c \
            $(TOPDIR)perf_tests/mem_size_u_s.c \
            $(TOPDIR)perf_tests/mem_speed_d_s.c \
            $(TOPDIR)perf_tests/mem_speed_u_s.c \
            $(TOPDIR)perf_tests/dijkstra_d_s.c \
            $(TOPDIR)perf_tests/dijkstra_u_s.c \
          )
SCGL_TESTS:=$(SCGL_SRC:.c=.out)

IGRAPH_SRC:=$(sort \
              $(TOPDIR)perf_tests/mem_size_d_i.c \
              $(TOPDIR)perf_tests/mem_size_u_i.c \
              $(TOPDIR)perf_tests/mem_speed_d_i.c \
              $(TOPDIR)perf_tests/mem_speed_u_i.c \
              $(TOPDIR)perf_tests/dijkstra_d_i.c \
              $(TOPDIR)perf_tests/dijkstra_u_i.c \
            )
IGRAPH_TESTS:=$(IGRAPH_SRC:.c=.out)

BOOST_SRC:=$(sort \
             $(TOPDIR)perf_tests/mem_size_d_b.cc \
             $(TOPDIR)perf_tests/mem_size_u_b.cc \
             $(TOPDIR)perf_tests/mem_speed_d_b.cc \
             $(TOPDIR)perf_tests/mem_speed_u_b.cc \
             $(TOPDIR)perf_tests/dijkstra_d_b.cc \
             $(TOPDIR)perf_tests/dijkstra_u_b.cc \
           )
BOOST_TESTS:=$(BOOST_SRC:.cc=.out)

include ../Makefile

all: scgl $(SCGL_TESTS) $(IGRAPH_TESTS) $(BOOST_TESTS)

$(SCGL_TESTS) : $(SCGL_SRC)
	@echo "Building SCGL test: $@"
	@$(CC) $(CFLAGS) $(MFLAGS) $*.c -o $@ $(TOPDIR)lib/libscgl.a

$(IGRAPH_TESTS) : $(IGRAPH_SRC)
	@echo "Building IGRAPH test: $@"
	@$(CC) $(CFLAGS) $(LDFLAGS) $*.c -o $@

$(BOOST_TESTS) : $(BOOST_SRC)
	@echo "Building BOOST::GRAPH test: $@"
	@$(CXX) $(CXXFLAGS) $*.cc -o $@

clean::
	@echo "Removing tests"
	@rm -rf *.out
