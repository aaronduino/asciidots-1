# compiler
CC = g++
EXE = dots
# discover sources, require their objects, we'll work out deps later
SOURCES := $(shell find src/ -name '*.cc')
OBJECTS := $(subst src/,obj/,$(SOURCES:%.cc=%.o))
DEPENDS := $(patsubst src/,obj/,$(SOURCES:%.cc=%.d))

.PHONY: asciidots clean rebuild

# link all objects when we have newest deps
asciidots: $(OBJECTS)
		$(CC) $(OBJECTS) -o bin/$(EXE) -lncurses

#create dependency files
obj/%.d: src/%.cc
		$(CC) -MM -MT '$(patsubst src/%.cc,obj/%.o,$<)' $< -MF $@

# object required, compile twinned source
obj/%.o: src/%.cc src/%.d
		$(CC) -c $< -o $@

# remove old object files
clean:
		rm -rf obj/* bin/*

#clean and build
rebuild: clean asciidots
