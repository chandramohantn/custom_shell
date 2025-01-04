cc = GCC
CFLAGS = -Wall -Wextra -g
SRC = src/main.c src/executor.c src/parser.c src/signal_handler.c src/io_redirection.c
OBJ = $(SRC:src/%.c=executables/%.o)
OUT = executables/learner

all: $(OUT)

$(OUT): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

executables/%.o: src/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ) $(OUT)
