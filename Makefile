CC = clang

TARGET_APP = app
SRC_APP = app.c

TARGET_CLIENT = client
SRC_CLIENT = client.c

all: $(TARGET_APP) $(TARGET_CLIENT)

$(TARGET_APP): $(SRC_APP)
	$(CC) -o $(TARGET_APP) $(SRC_APP)

$(TARGET_CLIENT): $(SRC_CLIENT)
	$(CC) -o $(TARGET_CLIENT) $(SRC_CLIENT)

clean:
	@echo "Cleaning up..."
	rm -f $(TARGET_APP) $(TARGET_CLIENT)

.PHONY: all clean
