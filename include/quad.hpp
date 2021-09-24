#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "backends/gl_objects.hpp"
#include "backends/gl_shaders.hpp"
#include "utils.hpp"

namespace txo {

	struct Quad {
		Quad(glm::vec2 top_left, glm::vec2 top_right, glm::vec2 bottom_right, glm::vec2 bottom_left) noexcept;

		void init();
		void render();
	private:
		glm::vec2 topLeft;
		glm::vec2 topRight;
		glm::vec2 bottomRight;
		glm::vec2 bottomLeft;
		float vertices[2 * 3 * 2]; // 2 triangles, 3 vertices per triangle, 2 points per vertex

		txo::ShaderProgram *shaderProgram; // need to instantiate it when opengl context is ready to be used
		uint vao;
		uint vbo;
	};

} // namespace txo
