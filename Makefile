P=main
OBJECTS=http.o main.o
CFLAGS=-Wall -Wextra -pedantic


$P: $(OBJECTS)
	$(CC) -o $P $(OBJECTS) -lcurl


.PHONY: clean
clean:
	rm $(OBJECTS) $P
