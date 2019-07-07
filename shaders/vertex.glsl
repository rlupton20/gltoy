#version 120

attribute vec3 position;
attribute vec2 text_coord;
attribute vec3 normal;

varying vec2 text_coord_pipeline;
varying vec3 normal_pipeline;

uniform mat4 transform;

void main()
{
    gl_Position = transform * vec4(position, 1.0);
    text_coord_pipeline = text_coord;
    normal_pipeline = (transform * vec4(normal, 0.0)).xyz;
}