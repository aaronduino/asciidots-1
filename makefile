# compiler
CC = g++
EXE = dots
# compiler args
COMPARGS = -Wall -Wextra
LINKARGS = -lncurses -ltinfo
# directories
SRC = src
OBJ = obj
DEP = dep
BIN = bin
# discover sources, require their objects, we'll work out deps NOW
SOURCES := $(shell find src/ -name '*.cc')
OBJECTS := $(subst src/,obj/,$(SOURCES:%.cc=%.o))
DEPENDS := $(subst src/,dep/,$(SOURCES:%.cc=%.d))

.PHONY: all clean rebuild

all: $(OBJ) $(DEP) $(BIN) $(EXE)

# make working directories
$(OBJ) $(DEP) $(BIN):
	mkdir $@

# link all object files
$(EXE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(BIN)/$(EXE) $(LINKARGS)

# make .d files
$(DEP)/%.d: $(SRC)/%.cc
	$(CC) -MM $< -MT $@ > $@

# compile source to object
$(OBJ)/%.o: $(SRC)/%.cc
	$(CC) $(COMPARGS) -c $< -o $@

# clean the output directories (NOT SOURCE)
clean:
	rm -f $(BIN)/* $(OBJ)/* $(DEP)/*

# recompile everything
rebuild: clean all

-include $(DEPENDS)
