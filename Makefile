# Directory structure
SRC_DIR := src
SRC_SUBDIRS := files io io/modes  # Subdirectories inside src
LIB_DIR := libs
OBJ_DIR := objects
BIN_DIR := bin
TARGET := $(BIN_DIR)/vino

# Source file discovery
SRC_FILES := $(wildcard $(SRC_DIR)/*.c) $(foreach dir,$(SRC_SUBDIRS),$(wildcard $(SRC_DIR)/$(dir)/*.c))
LIB_FILES := $(wildcard $(LIB_DIR)/*/*.c) $(wildcard $(LIB_DIR)/*/*/*.c)
ALL_C_FILES := $(SRC_FILES) $(LIB_FILES)

# Object file paths with preserved directory structure
ALL_OBJ_FILES := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/src/%.o,$(SRC_FILES)) \
								 $(patsubst $(LIB_DIR)/%.c,$(OBJ_DIR)/libs/%.o,$(LIB_FILES))

# Compilation flags
BASE_FLAGS := 
WARN_FLAGS := -Wall -Wextra
ERROR_FLAGS := $(WARN_FLAGS) -Werror
DEBUG_FLAGS := -g
RELEASE_FLAGS := -O3 -DNDEBUG -funroll-loops -ffast-math -finline-functions -finline-small-functions -findirect-inlining -fprefetch-loop-arrays -ftree-vectorize -fstrict-aliasing -fstrict-overflow # Standard optimizations without architecture-specific ones

# Default target
all: compile

# Basic compilation (no extra flags)
compile: $(TARGET)

# Compilation with warnings
warnings: CFLAGS += $(WARN_FLAGS)
warnings: $(TARGET)

# Compilation with warnings as errors
ewarnings: CFLAGS += $(ERROR_FLAGS)
ewarnings: $(TARGET)

# Debug compilation
debug: CFLAGS += $(DEBUG_FLAGS)
debug: $(TARGET)

# Release compilation
release: CFLAGS += $(RELEASE_FLAGS)
release: $(TARGET)

# Install compiled binary to system directory
install: release
	@echo "-------------------------------Installing to /usr/bin-------------------------------"
	install -Dm755 $(TARGET) /usr/bin/vino

# Final binary linking
$(TARGET): $(ALL_OBJ_FILES) | $(BIN_DIR)
	@echo "-------------------------------Linking final binary-------------------------------"
	$(CC) $(CFLAGS) $^ -o $@

# Rule for source object files
$(OBJ_DIR)/src/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule for library object files
$(OBJ_DIR)/libs/%.o: $(LIB_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

# Create required directories
$(OBJ_DIR) $(BIN_DIR):
	mkdir -p $@

# Clean build artifacts
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all compile warnings ewarnings debug release clean install
