CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -O2 -I../include -I../benchmarks/utils
LDFLAGS =

# Enable cross platform (Unix, Linux, Windows) build
ifeq ($(OS),Windows_NT)
    RM = del /F /Q
endif
RM ?= rm -f

# Shared source files
ATTR_SRC = ../src/shared/copy.c ../src/shared/free.c ../src/shared/print.c ../src/shared/comparator.c
UTIL_SRC = ../src/shared/swap.c
STATUS_SRC = ../src/shared/ccol_status.c
COMMON_SRC = $(ATTR_SRC) $(UTIL_SRC) $(STATUS_SRC)

# Container source files
DLL_SRC = ../src/dll/dll.c ../src/dll/dll_internal.c ../src/dll/dll_iterator.c

# Benchmark source files
BENCH_DLL_SRC = bench_dll.c $(DLL_SRC) $(COMMON_SRC)

BENCH_TARGETS = bench_dll

.PHONY: all bench clean

all: $(BENCH_TARGETS)

bench_dll: $(BENCH_DLL_SRC)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

bench: $(BENCH_TARGETS)
	@echo "Running bench_dll..."
	@./bench_dll

clean:
	$(RM) -f $(BENCH_TARGETS) *.exe
