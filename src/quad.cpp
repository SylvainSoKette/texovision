#include "quad.hpp"


static const char* VERTEX_SHADER_SOURCE = "#version 450 core\n"
	"\n"
	"layout (location=0) in vec2 vertPos;\n"
	"layout (location=0) in vec2 texCoord;\n"
	"\n"
	"void main() {\n"
	"	gl_Position = vec4(vertPos.x, vertPos.y, 1.0f, 1.0f);\n" // such passthrough, so beautiful, wow
	"}\n";
static const char* FRAGMENT_SHADER_SOURCE = "#version 450 core\n"
	"\n"
	"out vec4 fragColor;\n"
	"\n"
	"void main() {\n"
	"	fragColor = vec4("
	"		gl_FragCoord.x / 960,"
	"		gl_FragCoord.y / 540,"
	"		1.0f,"
	"		1.0f"
	"	);"
	"}\n";

namespace txo {

	Quad::Quad(glm::vec2 top_left, glm::vec2 top_right, glm::vec2 bottom_right, glm::vec2 bottom_left) noexcept :
		topLeft{top_left},
		topRight{top_right},
		bottomRight{bottom_right},
		bottomLeft{bottom_left},
		vertices {
			bottomLeft.x, bottomLeft.y,
			topLeft.x, topLeft.y,
			topRight.x, topRight.y,
			topRight.x, topRight.y,
			bottomRight.x, bottomRight.y,
			bottomLeft.x, bottomLeft.y,
		} {}

	void Quad::init() {
		std::string shaderSources { txo::read_file("res/quad.glsl") };
		shaderProgram = new ShaderProgram();
		shaderProgram->addShaders(shaderSources);
		shaderProgram->link();

		// // VAO
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		// // VBO
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(txo::VertexAttrib::POSITION);
		glVertexAttribPointer(txo::VertexAttrib::POSITION, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
		// ou bien, puisqu'on a du tightly-packed data dans le buffer 'vertices':
		// glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	}

	void Quad::render() {
		// activate shader program and vao then ask for render
		shaderProgram->bind();
		// glUseProgram(shaderProgram);
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 2 * 3);

		shaderProgram->unbind();
	}

} // namespace txo
