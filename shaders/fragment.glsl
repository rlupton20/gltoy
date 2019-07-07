#version 120

varying vec2 text_coord_pipeline;
varying vec3 normal_pipeline;

uniform sampler2D diffuse;

void main()
{
    gl_FragColor = texture2D(diffuse, text_coord_pipeline) * dot(vec3(0.0, 0, -1.0), normal_pipeline);
}