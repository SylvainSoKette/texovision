#include <GL/glew.h>

namespace txo {

struct TextureObject {
	GLuint id;
	GLenum type;

	TextureObject() : type{GL_TEXTURE_2D} {
		glGenTextures(1, &id);
	}

	void setData(std::size_t size, float *data) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		// https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glTexImage2D.xhtml
		glTexImage2D(
			type,     // GLenum target
			0,        // GLint level
			GL_RED,   // GLint internalformat
			size,     // GLsizei width
			size,     // GLsizei height
			0,        // GLint border
			GL_RED,   // GLenum format
			GL_FLOAT, // GLenum type
			data      // const void * data
		);
	}

	void bind() {
		glBindTexture(type, id);
	}

	void unbind() {
		glBindTexture(type, 0);
	}
};

} // namespace txo;
