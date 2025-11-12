CC = clang++

SRC = inheritance.cpp composition.cpp
DEST = inheritance composition

all: $(DEST)

inheritance: inheritance.cpp
	$(CC) $< -o $@

composition: composition.cpp
	$(CC) $< -o $@

clean:
	rm -f $(DEST)

.PHONY: all clean
