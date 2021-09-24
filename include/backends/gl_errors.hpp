#pragma once

#include <string>
#include <iostream>

#include <GL/glew.h>


#define GLCall(x) txo::GLError::clear(); x; txo::GLError::check(#x, __FILE__, __LINE__)

namespace txo {

namespace GLError
{
	void clear() { while(glGetError() != GL_NO_ERROR); }

	void check(const char* function, const char* file, const int line)
	{
		while(GLenum error = glGetError())
		{
			std::string errorMsg;
			switch(error)
			{
				case GL_INVALID_ENUM:
					errorMsg = "GL_INVALID_ENUM An unacceptable value is specified for an enumerated argument. The offending command is ignored and has no other side effect than to set the error flag.";
					break;
				case GL_INVALID_VALUE:
					errorMsg = "GL_INVALID_VALUE A numeric argument is out of range. The offending command is ignored and has no other side effect than to set the error flag.";
					break;
				case GL_INVALID_OPERATION:
					errorMsg = "GL_INVALID_OPERATION The specified operation is not allowed in the current state. The offending command is ignored and has no other side effect than to set the error flag.";
					break;
				case GL_INVALID_FRAMEBUFFER_OPERATION:
					errorMsg = "GL_INVALID_FRAMEBUFFER_OPERATION The framebuffer object is not complete. The offending command is ignored and has no other side effect than to set the error flag.";
					break;
				case GL_OUT_OF_MEMORY:
					errorMsg = "GL_OUT_OF_MEMORY There is not enough memory left to execute the command. The state of the GL is undefined, except for the state of the error flags, after this error is recorded.";
					break;
				case GL_STACK_UNDERFLOW:
					errorMsg = "GL_STACK_UNDERFLOW An attempt has been made to perform an operation that would cause an internal stack to underflow.";
					break;
				case GL_STACK_OVERFLOW:
					errorMsg = "GL_STACK_OVERFLOW An attempt has been made to perform an operation that would cause an internal stack to overflow.";
					break;
				default:
					errorMsg = "Unsupported Error";
					break;
			}

			std::cout << "[GL Error] " << error
				<< " " << errorMsg
				<< " - in function " << function
				<< " from file " << file
				<< ":" << line <<"\n";
		}
	}

	void debugMessageCallback(
		GLenum source, GLenum type, GLuint id,
		GLenum severity, GLsizei length,
		const GLchar *message, const void *userParam
	) {
		std::string _source;
		std::string _type;
		std::string _severity;

		switch (source)
		{
			case GL_DEBUG_SOURCE_API:             _source = "API"; break;
			case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   _source = "WINDOW SYSTEM"; break;
			case GL_DEBUG_SOURCE_SHADER_COMPILER: _source = "SHADER COMPILER"; break;
			case GL_DEBUG_SOURCE_THIRD_PARTY:     _source = "THIRD PARTY"; break;
			case GL_DEBUG_SOURCE_APPLICATION:     _source = "APPLICATION"; break;
			case GL_DEBUG_SOURCE_OTHER:           _source = "UNKNOWN"; break;
			default:                              _source = "UNKNOWN"; break;
		}

		switch (type) {
			case GL_DEBUG_TYPE_ERROR:               _type = "Error"; break;
			case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: _type = "Deprecated behavior"; break;
			case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  _type = "Undefined behavior"; break;
			case GL_DEBUG_TYPE_PORTABILITY:         _type = "Portability"; break;
			case GL_DEBUG_TYPE_PERFORMANCE:         _type = "Performance"; break;
			case GL_DEBUG_TYPE_OTHER:               _type = "Other"; break;
			case GL_DEBUG_TYPE_MARKER:              _type = "Marker"; break;
			default:                                _type = "UNKNOWN"; break;
		}

		switch (severity) {
			case GL_DEBUG_SEVERITY_HIGH:         _severity = "HIGH"; break;
			case GL_DEBUG_SEVERITY_MEDIUM:       _severity = "MEDIUM"; break;
			case GL_DEBUG_SEVERITY_LOW:          _severity = "LOW"; break;
			case GL_DEBUG_SEVERITY_NOTIFICATION: _severity = "NOTIFICATION"; break;
			default:                             _severity = "UNKNOWN"; break;
		}

		std::cerr << "[GL " << _type << "]: "
			<< "(severity: " << _severity << ")"
			<< "\n\tSource: "<< _source
			<< "\n\tType: " << _type
			<< "\n\tMessage: " << message << std::endl;
	}
};

} // namepsace txo
