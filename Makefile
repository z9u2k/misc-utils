CFLAGS=-std=c99 -pedantic -Wall -Werror

.PHONY: all
all: stdio-redir

.PHONY: clean
clean:
	rm -f stdio-redir

stdio-redir: stdio-redir.c
	$(CC) $(CFLAGS) -o $@ $<

