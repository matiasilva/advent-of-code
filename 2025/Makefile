CFLAGS := -g -Wall
CC := clang
BIN ?= d2
SOURCES := 

all: $(BIN)

%: %.c
	$(CC) $(CFLAGS) $< $(SOURCES) -o $@

clean:
	rm -rf $(BIN) *.dSYM
