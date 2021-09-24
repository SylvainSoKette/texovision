CC := g++ -std=c++2a
LD := g++ -std=c++2a

INCLUDES := -Iinclude/ -Iinclude/imgui/ -I/usr/include/SDL2/
DEBUG_CFLAGS := -g
RELEASE_CFLAGS := -O3
CFLAGS := $(DEBUG_CFLAGS)
LFLAGS := -lSDL2 -lGL -lGLEW -lm

# update as needed
SUBDIRS := imgui backends

SRC_DIR := src
SRC_SUBDIRS := $(foreach sdir,$(SUBDIRS),$(SRC_DIR)/$(sdir))
BUILD_DIR := obj
BUILD_SUBDIRS := $(foreach sdir,$(SUBDIRS),$(BUILD_DIR)/$(sdir))

SRC := $(wildcard $(SRC_DIR)/*.cpp) $(foreach sdir,$(SRC_SUBDIRS),$(wildcard $(sdir)/*.cpp))
OBJ := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC))
DEP := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.d,$(SRC))

.PHONY: all
all: build_dirs texovision Makefile

.PHONY: run
run: all
	./texovision

texovision: $(OBJ)
	$(LD) $^ $(LFLAGS) -o $@

-include $(DEP)

.PHONY: build_dirs
build_dirs:
	mkdir -p $(BUILD_DIR)
	mkdir -p $(BUILD_SUBDIRS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -c $< -o $@

.PHONY: clean
clean:
	-rm $(OBJ)
	-rm $(DEP)
	-rm -r $(BUILD_SUBDIRS)

.PHONY: purge
purge: clean
	-rm imgui.ini
	-rm ./texovision
