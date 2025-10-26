CC = clang
TARGET = server
SRC = server.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

run: $(TARGET)
	@echo "Running $(TARGET)..."
	./$(TARGET)

clean:
	@echo "Cleaning up..."
	rm -f $(TARGET)

.PHONY: all run clean
