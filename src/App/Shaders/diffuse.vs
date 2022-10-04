#version 330 core

layout(location=0) in vec2 pos;
layout(location=1) in vec3 col;

uniform mat4 matrix;

out vec3 vert_col;

void main() {
	vert_col = col;
	gl_Position = matrix * vec4(pos.xy, 0.0, 1.0);
}
