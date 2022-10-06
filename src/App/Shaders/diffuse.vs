#version 330 core

layout(location=0) in vec2 pos;

out vec2 vert_pos;

uniform float zoom;
uniform vec2 shift;

void main() {
    float newX = pos.x + shift.x;
    float newY = pos.y + shift.y;
    vert_pos = vec2(newX / zoom, newY / zoom);
	gl_Position = vec4(pos.xy, 0.0, 1.0);
}
