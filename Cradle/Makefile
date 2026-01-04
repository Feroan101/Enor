CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g
INCLUDES = -Ivm/include

SRC = vm/main.c \
      vm/vm.c \
      vm/stack.c \
      vm/memory.c \
      vm/instructions.c

OBJ = $(SRC:vm/%.c=builds/obj/%.o)

BIN = builds/machine

.PHONY: all clean run

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

builds/obj/%.o: vm/%.c
	@mkdir -p builds/obj
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf builds

run: $(BIN)
	./$(BIN)
