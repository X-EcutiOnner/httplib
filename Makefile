BIN=bin
SOURCES=src/*.c
CFLAGS=-Wall -Wextra -Wpedantic -Iinclude

all: clean samples

samples: sample_basic_usage sample_cookies sample_auth_basic \
	sample_auth_bearer sample_auth_digest sample_redirects sample_timeout\
    sample_post sample_put sample_patch sample_json

sample_%: $(SOURCES) samples/%.c
	mkdir -p $(BIN)
	$(CC) $(CFLAGS) -o $(BIN)/$* $? -lcurl

.PHONY: clean
clean:
	-rm -r $(BIN)
