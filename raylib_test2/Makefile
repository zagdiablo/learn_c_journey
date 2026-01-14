CC = clang
CFLAGS = -std=c99 -Wall -Werror
LINKERS = -lraylib -lm
SRCS = main.c save_io.c
TARGET = main

all:
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET) $(LINKERS)

clean:
	rm -f $(TARGET)
