#include "quad.hpp"


namespace txo {

	Quad::Quad(glm::vec2 top_left, glm::vec2 top_right, glm::vec2 bottom_right, glm::vec2 bottom_left) noexcept :
		topLeft{top_left},
		topRight{top_right},
		bottomRight{bottom_right},
		bottomLeft{bottom_left},
		vertices {
		//	x              y              u      v
			bottomLeft.x,  bottomLeft.y,  0.0f, 0.0f,
			topLeft.x,     topLeft.y,     0.0f, 1.0f,
			topRight.x,    topRight.y,    1.0f, 1.0f,
			topRight.x,    topRight.y,    1.0f, 1.0f,
			bottomRight.x, bottomRight.y, 1.0f, 0.0f,
			bottomLeft.x,  bottomLeft.y,  0.0f, 0.0f
		} {}

	void Quad::init() {
	/*
		Init OpenGL data for this object.
		At this point, OpenGL context must have been initialized.
	*/
		std::string shaderSources { txo::read_file("res/quad.glsl") };
		shaderProgram = std::make_unique<txo::ShaderProgram>();
		shaderProgram->addShaders(shaderSources);
		shaderProgram->link();

		// VAO
		arrayObject = std::make_unique<txo::ArrayObject>();
		arrayObject->bind();

		// VBO// need to instantiate it when opengl context is ready to be used
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(txo::VertexAttrib::POSITION);
		glVertexAttribPointer(
			txo::VertexAttrib::POSITION,
			2, GL_FLOAT, GL_FALSE,
			4 * sizeof(float),
			(void*)(0)
		);
		glEnableVertexAttribArray(txo::VertexAttrib::UV);
		glVertexAttribPointer(
			txo::VertexAttrib::UV,
			2, GL_FLOAT, GL_FALSE,
			4 * sizeof(float),
			(void*)(2 * sizeof(float))
		);

		// texture binding
		textureObject = std::make_unique<txo::TextureObject>();
	}

	void Quad::render() {
		shaderProgram->bind();

		if (texture) {
			// https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glActiveTexture.xhtml
			glActiveTexture(GL_TEXTURE0);
			textureObject->bind();
		}

		arrayObject->bind();
		glDrawArrays(GL_TRIANGLES, 0, 2 * 3);

		if (texture) textureObject->unbind();

		arrayObject->unbind();
		shaderProgram->unbind();
	}

	void Quad::update_texture() {
		textureObject->bind();
		textureObject->setData(
			texture->size,
			texture->pixels.data()
		);
		textureObject->unbind();
	}

} // namespace txo
