# compiler
CC = g++
EXE = dots
# compiler args
COMPARGS = -Wall -Wextra -std=gnu++11
LINKARGS = -lncurses
# directories
SRC = src
OBJ = obj
BIN = bin
# discover sources, require their objects, we'll work out deps NOW
SOURCES := $(shell find $(SRC) -name '*.cc')
OBJECTS := $(subst $(SRC),$(OBJ),$(SOURCES:%.cc=%.o))
DEPENDS := $(shell find $(OBJ) -name '*.d')
FOLDERS := $(subst $(SRC),$(OBJ),$(shell find $(SRC) -type d))

.PHONY: all dirs clean rebuild
.PRECIOUS: $(OBJ)/%.d # don't delete deps

all: dirs $(BIN) $(EXE)

# make the binary folder
$(BIN):
	mkdir -p $(BIN)

# link all object files
$(EXE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(BIN)/$(EXE) $(LINKARGS)

# compile source to object
$(OBJ)/%.o: $(SRC)/%.cc $(OBJ)/%.d
	$(CC) $(COMPARGS) -c $< -o $@

# generate dependency files
$(OBJ)/%.d: $(SRC)/%.cc
	$(CC) -MM $< -MT "$(subst .d,.o,$@) $@" > $@

# clean the output directories (NOT SOURCE)
clean:
	rm -rf $(BIN)/* $(OBJ)/*

# recompile everything
rebuild: clean all

# duplicate src folder structure to obj
dirs:
	mkdir -p $(FOLDERS)

-include $(DEPENDS)
