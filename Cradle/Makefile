CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g
INCLUDES = -Ivm/include

SRC = vm/main.c \
      vm/vm.c \
      vm/stack.c \
      vm/arena.c \
      vm/instructions.c \
	  vm/errors.c

OBJ = $(SRC:vm/%.c=builds/obj/%.o)

BIN = builds/machine

.PHONY: all clean run asm test

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

builds/obj/%.o: vm/%.c
	@mkdir -p builds/obj
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

run: $(BIN)
	./$(BIN)

asm:
	@if [ -z "$(PROGRAM)" ]; then \
		echo "Usage: make asm PROGRAM=<program_name>"; \
		exit 1; \
	fi
	./scripts/asm.sh $(PROGRAM)

test: $(BIN)
	./scripts/test.sh

clean:
	./scripts/clean.sh