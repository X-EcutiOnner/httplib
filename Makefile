BIN=bin
SOURCES=src/*.c
CFLAGS=-Wall -Wextra -Wpedantic -Iinclude

all: clean samples

samples: sample_basic_usage sample_cookies sample_auth_basic sample_auth_bearer

sample_%: $(SOURCES) samples/%.c
	mkdir -p $(BIN)
	$(CC) $(CFLAGS) -o $(BIN)/$* $? -lcurl

.PHONY: clean
clean:
	-rm -r $(BIN)
