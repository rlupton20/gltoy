LSDL=`pkg-config --libs sdl2 glew`
INCLUDES=include/
main:
			mkdir -p build
			g++ --std=c++17 -I$(INCLUDES) src/* -o build/main $(LSDL)

clean:
			rm -rf build
