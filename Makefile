LSDL=`pkg-config --libs sdl2 glew`
INCLUDES=-Iinclude/ -I$(STB_HEADER_PATH)
CPPFLAGS=-Wall -std=c++17 $(INCLUDES)
BUILDDIR=build/
CPP=g++

SRCS=$(wildcard src/*.cpp)
OBJS=$(SRCS:src/%.cpp=build/%.o)

.PHONY = all clean format

all: main

main: $(OBJS)
			mkdir -p $(BUILDDIR)
			$(CPP) $(CPPFLAGS) $^ -o build/main $(LSDL)

build/%.o: src/%.cpp
			@mkdir -p $(BUILDDIR)
			$(CPP) $(CPPFLAGS) -c $^ -o $@

format:
			find -iname *.hpp -o -iname *.cpp | xargs clang-format -style=file -i

clean:
			rm $(OBJS)
			rm -rf $(BUILDDIR)
