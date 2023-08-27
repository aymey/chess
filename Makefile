CC = gcc
CFLAGS = -Wall -g -lraylib -lm
TARGET = chess

all: chess

chess: $(TARGET).c board.c
	$(CC) $(CFLAGS) $(TARGET).c board.c -o $(TARGET)

.PHONY: all chess
