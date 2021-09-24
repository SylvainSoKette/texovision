#include "backends/gl_shaders.hpp"


namespace txo {

	void ShaderUtils::check_compilation_status(uint shader, GLenum type) {
		GLint compilationStatus;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compilationStatus);
		if (compilationStatus == GL_FALSE)
		{
			GLint infoLogLength;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

			GLchar infoLogContent[infoLogLength + 1]; // c'est possible ça ? O_o
			glGetShaderInfoLog(shader, infoLogLength, nullptr, infoLogContent);

			std::string shaderTypeStr;
			switch(type)
			{
					case GL_VERTEX_SHADER: shaderTypeStr = "vertex"; break;
					case GL_GEOMETRY_SHADER: shaderTypeStr = "geometry"; break;
					case GL_FRAGMENT_SHADER: shaderTypeStr = "fragment"; break;
					default: shaderTypeStr = "???"; break;
			}

			ERR("[GL Error]: Failed to compile " << shaderTypeStr << " shader: " << infoLogContent);
		}
	}

	ShaderProgram::ShaderProgram() {
		id = glCreateProgram();
	}

	ShaderProgram::~ShaderProgram() {
		glDeleteProgram(id);
	}

	std::vector<ShaderSource> ShaderProgram::parseShaders(std::string source) {
		std::vector<ShaderSource> shaderSources;
		std::istringstream sourceStream(source);

		for (std::string line; std::getline(sourceStream, line); )
		{
			if (txo::starts_with(line, ";;")) {
				if (txo::starts_with(line, ";; vertex")) {
					shaderSources.push_back( {GL_VERTEX_SHADER, ""} );
					continue;
				} else if (txo::starts_with(line, ";; geometry")) {
					shaderSources.push_back( {GL_GEOMETRY_SHADER, ""} );
					continue;
				} else if (txo::starts_with(line, ";; fragment")) {
					shaderSources.push_back( {GL_FRAGMENT_SHADER, ""} );
					continue;
				}
			}
			shaderSources.back().source.append(line + "\n");
		}

		return shaderSources;
	}

	void ShaderProgram::addShaders(std::string sources) {
		for (ShaderSource shaderSource : parseShaders(sources)) {
			addShader(shaderSource.type, shaderSource.source);
		}
	}

	void ShaderProgram::addShader(GLenum type, std::string source) {
		GLuint shader = glCreateShader(type);
		const char *shaderSource = source.c_str();
		glShaderSource(shader, 1, &shaderSource, nullptr);

		glCompileShader(shader);
		txo::ShaderUtils::check_compilation_status(shader, type);

		shaders.push_back(shader);
	}

	void ShaderProgram::link() {
		for (auto shader : shaders) glAttachShader(id, shader);

		// TODO(sylvain): error checking for linking
		glLinkProgram(id);
		glValidateProgram(id);

		for (auto shader : shaders)
		{
			glDetachShader(id, shader);
			glDeleteShader(shader);
		}
	}

	void ShaderProgram::bind() {
		glUseProgram(id);
	}

	void ShaderProgram::unbind() {
		glUseProgram(0);
	}

	void ShaderProgram::setUniform(const char* name, float value) {
		GLint location = glGetUniformLocation(id, name);
		if (location != -1) glUniform1f(location, value);
	}

	void ShaderProgram::setUniform(const char* name, float x, float y) {
		GLint location = glGetUniformLocation(id, name);
		if (location != -1) glUniform2f(location, x, y);
	}

	void ShaderProgram::setUniform(const char* name, float x, float y, float z) {
		GLint location = glGetUniformLocation(id, name);
		if (location != -1) glUniform3f(location, x, y, z);
	}

	void ShaderProgram::setUniform(const char* name, const glm::vec3 v) {
		GLint location = glGetUniformLocation(id, name);
		if (location != -1) glUniform3fv(location, 1, glm::value_ptr(v));
	}

	void ShaderProgram::setUniform(const char* name, float r, float g, float b, float a) {
		GLint location = glGetUniformLocation(id, name);
		if (location != -1) glUniform4f(location, r, g, b, a);
	}

	void ShaderProgram::setUniform(const char* name, const glm::mat4 mat) {
		GLint location = glGetUniformLocation(id, name);
		if (location != -1) glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
	}

} // namespace txo
