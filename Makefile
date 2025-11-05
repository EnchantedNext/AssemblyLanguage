CC = clang

TARGET = set
SRC = set.c map.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

run:
	./$(TARGET)

clean:
	@echo "Cleaning up..."
	rm -f $(TARGET)

.PHONY: all run clean
