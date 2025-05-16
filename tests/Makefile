CC = gcc
CFLAGS = -std=c99 -Wall -Wextra
CPPFLAGS = -I../include \
           -I../src \
           -I../unity \
           -I../src/dll \
           -I../src/shared
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
COMMON_SRC = $(ATTR_SRC) $(UTIL_SRC) $(STATUS_SRC) ../unity/unity.c

# Container source files
DLL_SRC = ../src/dll/ccol_dll.c					\
 		  ../src/dll/internal.c 				\
 		  ../src/shared/internal_dll_cdll.c 	\
 		  ../src/iterator/ccol_dll_iterator.c 	\

# Test source files
TEST_DLL_SRC = test_dll.c $(DLL_SRC) $(COMMON_SRC)
TEST_TARGETS = test_dll

.PHONY: all test clean

all: $(TEST_TARGETS)

test_dll: $(TEST_DLL_SRC)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $^ $(LDFLAGS)

test: $(TEST_TARGETS)
	@echo "Running test_dll..."
	@$(MAKE) test_dll
	@./test_dll

clean:
	$(RM) -f $(TEST_TARGETS) *.exe
