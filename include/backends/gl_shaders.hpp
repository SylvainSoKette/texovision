#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <string>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "utils.hpp"

namespace txo {

	namespace ShaderUtils {
		void check_compilation_status(uint shader, GLenum type);
	}

	struct ShaderSource {
		GLenum type;
		std::string source;
	};

	struct ShaderProgram {
		GLuint id;
		std::vector<GLuint> shaders;

		ShaderProgram();
		~ShaderProgram();

		std::vector<ShaderSource> parseShaders(std::string);
		void addShaders(std::string);
		void addShader(GLenum, std::string);
		void link();
		void bind();
		void unbind();
		void setUniform(const char*, float);
		void setUniform(const char*, float, float);
		void setUniform(const char*, float, float, float);
		void setUniform(const char*, const glm::vec3);
		void setUniform(const char*, float, float, float, float);
		void setUniform(const char*, const glm::mat4);
	};

} // namespace txo
