# compiler
CC = g++
EXE = sdf
# compiler args
COMPARGS = -Wall -Wextra
LINKARGS = -lncurses -ltinfo
# directories
SRC = src
OBJ = obj
DEP = dep
BIN = bin
# discover sources, require their objects and deps
SOURCES := $(shell find src/ -name '*.cc')
OBJECTS := $(subst src/,obj/,$(SOURCES:%.cc=%.o))
DEPENDS := $(subst src/,dep/,$(SOURCES:%.cc=%.d))

.PHONY: all clean rebuild

all: $(EXE)

# link all object files
$(EXE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(BIN)/$(EXE) $(LINKARGS)

# make .d files
$(DEP)/%.d: $(SRC)/%.cc
	$(CC) -MM $< -MT $(OBJ)/$(@F:%.d=%.o) > $@

# compile source to object
$(OBJ)/%.o: $(SRC)/%.cc
	$(CC) $(COMPARGS) -c $< -o $@

# clean the output directories (NOT SOURCE)
clean:
	rm -f $(BIN)/* $(OBJ)/* $(DEP)/*

# recompile everything
rebuild: clean all

-include $(DEPENDS)
