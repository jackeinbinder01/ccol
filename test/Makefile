CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -I../include -I../unity

SRC = test_dll.c \
	  ../src/dll/dll.c \
	  ../src/dll/dll_internal.c \
	  ../src/dll/dll_iterator.c \
      ../src/shared/ccol_status.c \
      ../src/comparator.c \
      ../src/copy.c \
      ../src/free.c \
      ../src/print.c \
      ../src/swap.c \
	  ../unity/unity.c

TARGET = test_dll

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)