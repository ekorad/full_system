.DEFAULT_GOAL := target

LIB_NAME := utils

SRC_DIR := src
INC_DIR := include
BIN_DIR := bin

INSTALL_INC_DIR := /usr/local/include/$(LIB_NAME)
INSTALL_LIB_DIR := /usr/local/lib

SOURCES := $(addprefix $(SRC_DIR)/,*.cpp)
OBJ_NAME := $(addsuffix $(addprefix $(LIB_NAME),.so),lib)

TARGET_OBJ := $(BIN_DIR)/$(OBJ_NAME)
TARGET_INCS := $(INC_DIR)/*.h

DBG := 0

INC_FLAGS := $(addsuffix $(INC_DIR),-I)
CXX_VER_FLAG := -std=c++17
DBG_FLAG := -ggdb3

CXXFLAGS := $(CXX_VER_FLAG) $(INC_FLAGS)
CXXFLAGS += -shared -fPIC

ifeq ($(DBG),1)
CXXFLAGS := -ggdb3 $(CXXFLAGS)
endif

.PHONY: all target clean install uninstall reinstall

all: target install

target: $(TARGET_OBJ)

$(TARGET_OBJ): $(BIN_DIR)/%.so: $(SOURCES)
	mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm -rf $(BIN_DIR)

install: target
	sudo install -d $(INSTALL_LIB_DIR)
	sudo install -d $(INSTALL_INC_DIR)
	sudo install -m644 $(TARGET_OBJ) $(INSTALL_LIB_DIR)
	sudo install -m644 $(TARGET_INCS) $(INSTALL_INC_DIR)
	sudo ldconfig

uninstall:
	sudo $(RM) $(INSTALL_LIB_DIR)/$(OBJ_NAME)
	sudo $(RM) -r $(INSTALL_INC_DIR)
	sudo ldconfig

reinstall: uninstall install