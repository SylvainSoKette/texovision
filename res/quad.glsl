;; vertex
#version 450 core

layout (location=0) in vec2 vertPos;

void main() {
	gl_Position = vec4(vertPos.x, vertPos.y, 1.0f, 1.0f); // such passthrough, so beautiful, wow
}

;; fragment
#version 450 core

out vec4 fragColor;

void main() {
	fragColor = vec4(
		gl_FragCoord.x / 960,
		gl_FragCoord.y / 960,
		1.0f,
		1.0f
	);
}
