#version 120

varying vec2 text_coord_pipeline;

uniform sampler2D diffuse;

void main()
{
    gl_FragColor = texture2D(diffuse, text_coord_pipeline);
}