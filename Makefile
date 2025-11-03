CC = clang

TARGET = map
SRC = map.c ulinkedlist.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

run:
	./$(TARGET)

clean:
	@echo "Cleaning up..."
	rm -f $(TARGET)

.PHONY: all run clean
