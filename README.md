# Messing around with OpenGL

Simple toy C++ program for messing around with OpenGL.

## Building

### nix

Run `nix-shell` then `make`.

### Other systems

You will need to build with `SDL2`, `glew`, `glm` and `stb_image.h` from `stb`. The `Makefile` expects the `stb_image.h` file to be located in a directory specified in an environment variable `STB_HEADER_PATH`.
