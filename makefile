CPP = g++
HEADERS = $(wildcard include/IronMind/*.h)
SRCS = $(wildcard src/IronMind/*.cpp)
OBJS = $(patsubst src/IronMind/%.cpp,obj/IronMind/%.o,$(SRCS))
DEPS = $(OBJS:.o=.d)
FLAGS = -Iinclude -std=c++14

.PHONY: tst run clean

# Run tests
run: tst
	@printf '\n--- Runing Tests ---\n\n'
	@bin/tst

# Tests
tst: tst/main.cpp $(DEPS) $(OBJS)
	$(CPP) $(FLAGS) -o bin/tst $(OBJS) tst/main.cpp

# Object files
obj/%.o: src/%.cpp mk_dirs.sh
	./mk_dirs.sh
	$(CPP) $(FLAGS) -c -o $@ $<

# Depedencies from cpp files
obj/%.d: src/%.cpp mk_dirs.sh
	./mk_dirs.sh
	$(CPP) $(FLAGS) -MM -MT $(patsubst obj/%.d,obj/%.o,$@) $< > $@

# Removes obj and bin folders
clean:
	rm -rf bin obj
	clear

# Include depedencies (auto update headers)
-include $(DEPS)
