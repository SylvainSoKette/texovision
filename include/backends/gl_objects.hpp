#include <typeinfo>

#include <GL/glew.h>


namespace txo {

struct ArrayObject {
	GLuint id;

	ArrayObject() {
		glGenVertexArrays(1, &id);
	}

	void bind() {
		glBindVertexArray(id);
	}

	void unbind() {
		glBindVertexArray(0);
	}
};


enum VertexAttrib : const GLuint {
	POSITION,
	COLOR,
	UV,
};


template <typename T>
struct BufferObject {
	GLuint id;
	GLenum type;
	GLenum usage { GL_STATIC_DRAW };

	BufferObject(GLenum _type) : type(_type) {
		glGenBuffers(1, &id);
	}

	void setAttrib(VertexAttrib vertexAttrib, GLint attrib_size, GLint per_vertex_size, GLint stride) {
		GLenum t;
		if (typeid(T) == typeid(GLfloat)) t = GL_FLOAT;
		else if (typeid(T) == typeid(GLint)) t = GL_INT;
		else if (typeid(T) == typeid(GLuint)) t = GL_UNSIGNED_INT;

		glEnableVertexAttribArray(vertexAttrib);
		glVertexAttribPointer(
			vertexAttrib,
			attrib_size,
			t,
			GL_FALSE,
			sizeof(GLfloat) * per_vertex_size,
			(void*)(stride * sizeof(T))
		);
	}

	void setData(GLint size, T *data) {
		glBufferData(
			type,
			sizeof(GLfloat) * size,
			data,
			usage
		);
	}

	void bind() {
		glBindBuffer(type, id);
	}

	void unbind() {
		glBindBuffer(type, 0);
	}
};

} // namespace txo;
