# compiler
CC = g++
EXE = dots
# compiler args
COMPARGS = -Wall -Wextra
LINKARGS =
# directories
SRC = src
OBJ = obj
BIN = bin
# discover sources, require their objects, we'll work out deps NOW
SOURCES := $(shell find $(SRC) -name '*.cc')
OBJECTS := $(subst $(SRC),$(OBJ),$(SOURCES:%.cc=%.o))
DEPENDS := $(OBJECTS:%.o=%.d)
FOLDERS := $(subst $(SRC),$(OBJ),$(shell find $(SRC) -type d))

.PHONY: all dirs clean rebuild

all: dirs $(BIN) $(EXE)

# make the binary folder
$(BIN):
	mkdir -p $(BIN)

# duplicate src folder structure to obj
dirs:
	@mkdir -p $(FOLDERS)

# link all object files
$(EXE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(BIN)/$(EXE) $(LINKARGS)

# make .d files
$(OBJ)/%.d: $(SRC)/%.cc
	$(CC) -MM $< -MT $@ > $@

# compile source to object
$(OBJ)/%.o: $(SRC)/%.cc
	$(CC) $(COMPARGS) -c $< -o $@

# clean the output directories (NOT SOURCE)
clean:
	rm -f $(BIN)/* $(OBJ)/*

# recompile everything
rebuild: clean all

-include $(DEPENDS)
