#pragma once

#include <cstdlib> // RETURN_SUCCESS RETURN_FAILURE
#include <exception> // std::runtime_error

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl.h"
#include "imgui/imgui_impl_opengl3.h"

#include "quad.hpp"
#include "utils.hpp"
#include "types.hpp"

namespace txo {

	struct Application {
		Application();
		~Application() noexcept;
		Application(const Application&) = delete;
		Application(const Application&&) = delete;
		Application& operator=(const Application&) = delete;
		Application& operator=(const Application&&) = delete;
		// vroom vroom
		void start();
		// override me please :3
		virtual void init() {};
		virtual void update() {};
		virtual void render() {};
		virtual void render_imgui() {};
	private:
		// init all context
		void _init_SDL();
		void _init_window();
		void _init_opengl_context();
		void _init_imgui_context();
		// end all context, should be called in the reverse order
		void _end_SDL() noexcept;
		void _end_window() noexcept;
		void _end_opengl_context() noexcept;
		void _end_imgui_context() noexcept;
		// private consts
		const char* WINDOW_TITLE {"Tex-O-Vision"};
		const int WINDOW_WIDTH {960};
		const int WINDOW_HEIGHT {960};
		const SDL_WindowFlags WINDOW_FLAGS {(SDL_WindowFlags)(
			// SDL_WINDOW_BORDERLESS |
			SDL_WINDOW_OPENGL |
			SDL_WINDOW_ALLOW_HIGHDPI
		)};
		//private members
		glm::vec4 bgColor {
			40.0f / 255.0f, // r
			40.0f / 255.0f, // g
			40.0f / 255.0f, // b
			1.0f
		};
		SDL_Window *window;
		SDL_GLContext glContext;
		ImGuiContext *imguiContext;
	};

} // namespace txo
