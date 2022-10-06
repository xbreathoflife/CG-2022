#version 330 core

in vec2 vert_pos;
out vec4 out_col;

uniform int iterations;
uniform float radius;

float mandelbrot(vec2 uv) {
    vec2 c = 0.5 * uv - vec2(0.7, 0.0);
    vec2 z = vec2(0.0);
    float iter = 0.0;
    for (int i = 0; i < iterations; i++) {
        z = vec2(z.x * z.x - z.y * z.y, 2.0 * z.x * z.y) + c;
        if (dot(z, z) > radius * radius) return float(iter) * 1.5 / iterations;
        iter++;
    }
    return 0.0;
}

void main() {
    float m = mandelbrot(vert_pos);
	out_col = vec4(0.0, 0.0, min(1.0, m), 1.0);
}