CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -O2
CPPFLAGS = -I../include -I../src -I../benchmarks/utils -I../src/dll -I../src/iterator -I../src/shared
LDFLAGS =

# Enable cross platform (Unix, Linux, Windows) build
ifeq ($(OS),Windows_NT)
    RM = del /F /Q
endif
RM ?= rm -f

# Core source files
ATTR_SRC = ../src/core/ccol_copy.c ../src/core/ccol_free.c ../src/core/ccol_print.c ../src/core/ccol_comparator.c
UTIL_SRC = ../src/core/ccol_swap.c
STATUS_SRC = ../src/core/ccol_status.c
COMMON_SRC = $(ATTR_SRC) $(UTIL_SRC) $(STATUS_SRC)

# Container source files
DLL_SRC = ../src/dll/ccol_dll.c 				\
		  ../src/dll/internal.c 				\
		  ../src/shared/internal_dll_cdll.c 	\
		  ../src/iterator/ccol_dll_iterator.c	\

# Benchmark source files
BENCH_DLL_SRC = bench_dll.c $(DLL_SRC) $(COMMON_SRC)

BENCH_TARGETS = bench_dll

.PHONY: all bench clean

all: $(BENCH_TARGETS)

bench_dll: $(BENCH_DLL_SRC)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $^ $(LDFLAGS)

bench: $(BENCH_TARGETS)
	@echo "Running bench_dll..."
	@./bench_dll

clean:
	$(RM) -f $(BENCH_TARGETS) *.exe
