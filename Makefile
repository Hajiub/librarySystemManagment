CC = gcc
CFLAGS = -Wall -Wextra
SRC_DIR = ./src
BUILD_DIR = ./bin
EXEC = $(BUILD_DIR)/main


SRC = $(wildcard $(SRC_DIR)/*.c)

OBJ = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC))

# Ensure the build directory exists
$(shell mkdir -p $(BUILD_DIR))

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

run:
	$(EXEC)
