P=main
SOURCES=src/*.c
CFLAGS=-Wall -Wextra -Wpedantic -Iinclude

all: clean $P

%: $(SOURCES) %.c
	$(CC) $(CFLAGS) -o $@ $? -lcurl

.PHONY: clean
clean:
	-rm $P
