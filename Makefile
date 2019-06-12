main:
			mkdir -p build
			g++ --std=c++17 src/main.cpp -o build/main

clean:
			rm -rf build
