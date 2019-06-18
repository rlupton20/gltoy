LSDL=`pkg-config --libs sdl2 glew`
INCLUDES=include/
main:
			mkdir -p build
			g++ --std=c++17 -I$(INCLUDES) src/* -o build/main $(LSDL)

format:
			find -iname *.hpp -o -iname *.cpp | xargs clang-format -style=file -i

clean:
			rm -rf build
