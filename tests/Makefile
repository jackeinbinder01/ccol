CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -I../include -I../unity
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
UNITY_SRC = ../unity/unity.c
COMMON_SRC = $(ATTR_SRC) $(UTIL_SRC) $(STATUS_SRC) $(UNITY_SRC)

# Container source files
DLL_SRC = ../src/dll/dll.c ../src/dll/dll_internal.c ../src/dll/dll_iterator.c

# Test source files
TEST_DLL_SRC = test_dll.c $(DLL_SRC) $(COMMON_SRC)

TEST_TARGETS = test_dll

.PHONY: all test clean

all: $(TEST_TARGETS)

test_dll: $(TEST_DLL_SRC)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

test: $(TEST_TARGETS)
	@echo "Running test_dll..."
	@./test_dll

clean:
	$(RM) -f $(TEST_TARGETS) *.exe
