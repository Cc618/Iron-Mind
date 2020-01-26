CPP = g++
HEADERS = $(wildcard include/IronMind/*.h)
SRCS = $(wildcard src/IronMind/*.cpp)
OBJS = $(patsubst src/IronMind/%.cpp,obj/IronMind/%.o,$(SRCS))
DEPS = $(OBJS:.o=.d)
FLAGS = -Iinclude -std=c++17

.PHONY: dirs tst run clean

# Run tests
run: tst
	@printf '\n--- Runing Tests ---\n\n'
	@bin/tst

# Tests
tst: tst/main.cpp dirs $(DEPS) $(OBJS)
	$(CPP) $(FLAGS) -o bin/tst $(OBJS) $<

# Object files
obj/%.o: src/%.cpp
	$(CPP) $(FLAGS) -c -o $@ $<

# Depedencies from cpp files
obj/%.d: src/%.cpp
	$(CPP) $(FLAGS) -MM -MT $(patsubst obj/%.d,obj/%.o,$@) $< > $@

# Creates bin and obj directories
dirs:
	mkdir -p bin obj obj/IronMind

# Removes obj and bin folders
clean:
	rm -rf bin/* obj/*
	clear

# Include depedencies (auto update headers)
-include $(DEPS)
