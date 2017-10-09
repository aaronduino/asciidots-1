# compiler
CC = g++
EXE = dots
# discover sources, require their objects
SOURCES := $(shell find src/ -name '*.cc')
OBJECTS := $(subst src/,obj/,$(SOURCES:%.cc=%.o))

.PHONY: asciidots clean rebuild
# link all objects when we have newest deps
asciidots: $(OBJECTS)
		$(CC) $(OBJECTS) -o bin/$(EXE) -lncurses
# object required, compile twinned source
obj/%.o: src/%.cc
		$(CC) -c $< -o $@
# remove old object files
clean:
		rm -rf obj/* bin/*
#clean and build
rebuild: clean asciidots
