# Makefile
CC = g++
CXXFLAGS = -Wall -std=c++17 -O2
LDFLAGS =

SRC_DIR = ./src
OBJ_DIR = ./obj

TARGET = main
SRCS = $(notdir $(wildcard $(SRC_DIR)/*.cc))
OBJECTS = $(patsubst %.o,$(OBJ_DIR)/%.o,$(SRCS:.cc=.o))
DEPS = $(OBJECTS:.o=.d)

all: prepare main

prepare: 
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc
	$(CC) $(CXXFLAGS) -c $< -o $@ -MD $(LDFLAGS)

$(TARGET) : $(OBJECTS)
	$(CC) $(CXXFLAGS) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

.PHONY: prepare all clean
clean:
	rm -f $(OBJECTS) $(DEPS) $(TARGET)
	rm -rf $(OBJ_DIR)

-include $(DEPS)