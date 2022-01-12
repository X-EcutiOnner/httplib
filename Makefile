BIN=bin
P=main
SOURCES=src/*.c
CFLAGS=-Wall -Wextra -Wpedantic -Iinclude

all: clean $P

%: $(SOURCES) %.c
	mkdir -p $(BIN)
	$(CC) $(CFLAGS) -o $(BIN)/$@ $? -lcurl

.PHONY: clean
clean:
	-rm $(BIN)/$P
