# ==============================================================================
# RISC-V (RV32I) Cache Simulator - Makefile
# ==============================================================================
# Targets:
#   all (default) : Builds optimized release executable in bin/
#   debug         : Builds executable with debug symbols and no optimization
#   run           : Builds (if needed) and executes the simulator
#   clean         : Removes compiled object files and binaries
#   help          : Displays available targets
# ==============================================================================

# Compiler & Linker Settings
CXX          ?= g++
CXXFLAGS     ?= -std=c++17 -Wall -Wextra -Wpedantic -O2
CPPFLAGS     ?= -Iinclude -MMD -MP
DEBUG_FLAGS  := -g3 -O0 -DDEBUG

# Directories
SRC_DIR      := src
INC_DIR      := include
BUILD_DIR    := build
BIN_DIR      := bin

# Executable Name
TARGET_NAME  := cache_sim
TARGET       := $(BIN_DIR)/$(TARGET_NAME)

# Discover Source and Object Files
SRCS         := $(wildcard $(SRC_DIR)/*.cpp)
ifneq ($(wildcard main.cpp),)
    SRCS     += main.cpp
endif

OBJS         := $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(SRCS))
DEPS         := $(OBJS:.o=.d)

# ------------------------------------------------------------------------------
# Build Rules
# ------------------------------------------------------------------------------

.PHONY: all
all: $(TARGET)

# Link the executable
$(TARGET): $(OBJS)
	@mkdir -p $(@D)
	@echo "[LD]  $@"
	$(CXX) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $@

# Compile source files into object files
$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	@echo "[CXX] $<"
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

# Debug Target
.PHONY: debug
debug: CXXFLAGS := -std=c++17 -Wall -Wextra -Wpedantic $(DEBUG_FLAGS)
debug: all

# Run Simulator
.PHONY: run
run: $(TARGET)
	@echo "[RUN] Launching $(TARGET)..."
	./$(TARGET)

# Clean Target
.PHONY: clean
clean:
	@echo "[CLEAN] Removing build artifacts..."
	rm -rf $(BUILD_DIR) $(BIN_DIR) *.o
	@echo "[CLEAN] Complete."

# Help Target
.PHONY: help
help:
	@echo "RISC-V Cache Simulator Build System"
	@echo "-----------------------------------"
	@echo "Usage: make [target]"
	@echo ""
	@echo "Available targets:"
	@echo "  make          - Build release binary ($(TARGET))"
	@echo "  make debug    - Build with debugging symbols and debug flags"
	@echo "  make run      - Compile and run the simulator"
	@echo "  make clean    - Remove build/ and bin/ directories"
	@echo "  make help     - Display this help message"

# Include generated header dependency files
-include $(DEPS)
