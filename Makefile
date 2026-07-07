# ─── Compiler & Standard ────────────────────────────────────────────────────
CXX      := g++
STD      := -std=c++17       # C++17 is a strict superset of the book's C++11
WARN     := -Wall -Wextra -Wpedantic

# ─── Build type ─────────────────────────────────────────────────────────────
# Default: release (-O3 matters enormously for path tracing performance).
# Override at the command line: make BUILD=debug
BUILD    ?= release

ifeq ($(BUILD),debug)
    OPT  := -O0 -g -fsanitize=address,undefined
    LINK := -fsanitize=address,undefined
else
    OPT  := -O3 -DNDEBUG
    LINK :=
endif

CXXFLAGS := $(STD) $(WARN) $(OPT)

# ─── Paths ──────────────────────────────────────────────────────────────────
SRC_DIR  := src
BUILD_DIR := build/$(BUILD)
TARGET   := raytracer
OUTPUT   := img.ppm

# ─── Sources & objects ──────────────────────────────────────────────────────
SRCS := $(wildcard $(SRC_DIR)/*.cc)
OBJS := $(patsubst $(SRC_DIR)/%.cc,$(BUILD_DIR)/%.o,$(SRCS))
# Also track headers so object files rebuild when any header changes.
DEPS := $(OBJS:.o=.d)

# ─── Targets ────────────────────────────────────────────────────────────────
.PHONY: all run clean

all: $(TARGET)

# Link
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LINK) $^ -o $@

# Compile (with automatic dependency generation via -MMD -MP)
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cc | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

# Create build directory on demand
$(BUILD_DIR):
	mkdir -p $@

# Render: compile then redirect stdout to a PPM file
run: all
	./$(TARGET) > $(OUTPUT)

# Remove build artefacts and rendered image
clean:
	rm -rf build/ $(TARGET) $(OUTPUT)

# Pull in auto-generated header dependencies (silently — they won't exist yet
# on a clean build, which is fine).
-include $(DEPS)
