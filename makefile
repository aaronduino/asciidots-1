# compiler
CC = g++
# discover sources, require their objects
SOURCES := $(shell find src/ -name '*.cc')
OBJECTS := $(subst src/,obj/,$(SOURCES:%.cc=%.o))

# link all objects when we have newest deps
asciidots: $(OBJECTS)
		$(CC) $(OBJECTS) -o bin/dots
# object required, compile twinned source
obj/%.o: src/%.cc
		$(CC) -c $< -o $@
