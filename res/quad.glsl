;; vertex
#version 450 core

layout (location=0) in vec2 vertPos;
layout (location=2) in vec2 vertUV;

out vec2 uvCoord;

void main() {
	uvCoord = vertUV;
	gl_Position = vec4(vertPos.x, vertPos.y, 1.0f, 1.0f); // such passthrough, so beautiful, wow
}

;; fragment
#version 450 core

in vec2 uvCoord;

layout (binding=0) uniform sampler2D tex;

out vec4 fragColor;

void main() {
	float colorValue = texture(tex, uvCoord).r;
	fragColor = vec4(
		colorValue,
		colorValue,
		colorValue,
		1.0f
	);
}
