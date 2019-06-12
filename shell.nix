let
   pkgs = import <nixpkgs> {};
in pkgs.stdenv.mkDerivation rec {
  name = "opengl-toy";
  buildInputs = [ pkgs.pkg-config pkgs.SDL2 pkgs.glew pkgs.glm ];
}
