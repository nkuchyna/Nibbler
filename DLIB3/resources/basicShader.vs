#version 120

attribute vec4 vertex;
varying vec2 texCoord0;

uniform mat4 transform;

void main()
{
    texCoord0 = vertex.zw;
    gl_Position = transform * vec4(vertex.xy, 0.0, 1.0);
}