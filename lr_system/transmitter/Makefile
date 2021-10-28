ARTIFACT := transmitter

BASE_PROJ_DIR := ./../..

SRC_DIR := src
INC_DIR := include
BIN_DIR := bin

DEPS_DIR := deps
DEPS_SRC_DIR := $(BASE_PROJ_DIR)/$(DEPS_DIR)/$(SRC_DIR)
DEPS_INC_DIR := $(BASE_PROJ_DIR)/$(DEPS_DIR)/$(INC_DIR)

DEPS_SRC_FILES := $(wildcard $(DEPS_SRC_DIR)/*.cpp)
OWN_SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
SRC_FILES := $(DEPS_SRC_FILES) $(OWN_SRC_FILES)

INC_FLAGS := -I$(INC_DIR) -I$(DEPS_INC_DIR)
CXX_VER_FLAG := -std=c++17

CXXFLAGS := $(CXX_VER_FLAG) $(INC_FLAGS)
CXXFLAGS += -pthread

.PHONY: all clean

all: $(ARTIFACT)

$(ARTIFACT): $(SRC_FILES)
	g++ $(CXXFLAGS) $^ -o $@

clean:
	$(RM) $(ARTIFACT)