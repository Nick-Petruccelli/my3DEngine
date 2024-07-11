CC=gcc
CFLAGS=-lGL -lglfw -lm
SRC=src
OBJ=obj
SRCS=$(wildcard $(SRC)/*.c)
OBJS=$(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))
BINDIR=bin
BIN=$(BINDIR)/main

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(OBJS) -o $@ $(CFLAGS)

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) -c $< -o $@ $(CFLAGS)

run: $(BIN)
	./$(BIN)
clean:
	$(RM) $(BINDIR)/* $(OBJ)/*

test:
	echo($(OBJS))
