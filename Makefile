CC = gcc
CFLAGS = -Iinclude -I/opt/homebrew/opt/openssl@3/include
LDFLAGS = -L/opt/homebrew/opt/openssl@3/lib -lssl -lcrypto

SRC_DIR = src
CRYPTO_DIR = crypto
OBJ_DIR = obj

# List of source files
SRCS = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(CRYPTO_DIR)/*.c)

# List of object files
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Executable name
TARGET = myprogram

# Build the executable
$(TARGET): $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS)

# Build object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(CRYPTO_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Create the obj directory if it doesn't exist
$(shell mkdir -p $(OBJ_DIR))

# Phony target to clean the project
clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET)

