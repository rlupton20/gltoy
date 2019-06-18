#version 120

attribute vec3 position;
attribute vec2 text_coord;

varying vec2 text_coord_pipeline;

void main()
{
    gl_Position = vec4(position, 1.0);
    text_coord_pipeline = text_coord;
}