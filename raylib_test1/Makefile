CC = clang
CFLAGS = -std=c99 -Wall -Werror -lraylib -lm
SRCS = main.c
TARGET = main

all:
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)