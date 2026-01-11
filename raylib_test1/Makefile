CC = clang
CFLAGS = -std=c99 -Wall -Werror
LINKERS = -lraylib -lm
SRCS = main.c
TARGET = main

all:
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET) $(LINKERS)
clean:
	rm -f $(TARGET)