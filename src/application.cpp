#include "application.hpp"


namespace txo {

/*
	CONSTRUCTORS AND DESTRUCTORS
*/
Application::Application() {
	// TODO(sokette): error checking since throw already there ?
	_init_SDL();
	_init_window();
	_init_opengl_context();
	_init_imgui_context();
}

Application::~Application() {
	_end_imgui_context();
	_end_opengl_context();
	_end_window();
	_end_SDL();
}

/*
	PRIVATE METHODS
*/
void Application::_init_SDL() {
	if (SDL_Init(SDL_INIT_EVERYTHING)) {
		const char* errorMsg = "Problem while initializing SDL";
		ERR(errorMsg << ": " << SDL_GetError());
		throw std::runtime_error(errorMsg);
	}
}

void Application::_init_window() {
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	window = SDL_CreateWindow(
		WINDOW_TITLE,
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		WINDOW_FLAGS
	);

	if (!window) {
		const char* errorMsg = "Problem while initializing window";
		ERR(errorMsg << ": " << SDL_GetError());
		throw std::runtime_error(errorMsg);
	}
}

void Application::_init_opengl_context() {
	glContext = SDL_GL_CreateContext(window);
	SDL_GL_MakeCurrent(window, glContext);
	SDL_GL_SetSwapInterval(1); // vsync, on va eviter de cramer mon pc

	if (glewInit() != GLEW_OK) {
		const char* errorMsg = "Failed to initialize OpenGL loader";
		ERR(errorMsg);
		throw std::runtime_error(errorMsg);
	}
}

void Application::_init_imgui_context() {
	IMGUI_CHECKVERSION();
	imguiContext = ImGui::CreateContext();
	if (!imguiContext) {
		const char* errorMsg = "Failed to initialize ImGui context";
		ERR(errorMsg);
		throw std::runtime_error(errorMsg);
	}

	ImGui::StyleColorsDark();
	// no error checking, next 2 functions always return 'true' anyway.
	ImGui_ImplSDL2_InitForOpenGL(window, glContext);
	ImGui_ImplOpenGL3_Init("#version 450");
}

void Application::_end_SDL() noexcept {
	SDL_Quit();
}

void Application::_end_window() noexcept {
	SDL_DestroyWindow(window);
}

void Application::_end_opengl_context() noexcept {
	SDL_GL_DeleteContext(glContext);
}

void Application::_end_imgui_context() noexcept {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
}

/*
	PUBLIC METHODS
*/
void Application::start() {
	SDL_Event event;
	u32	nowTime;
	u32	lastTime;
	u32 frameTime;
	double deltaTime;
	bool redraw = true;
	bool quit = false;

	nowTime = SDL_GetTicks();
	lastTime = 0;
	deltaTime = 0;

	init();

	// main loop
	while (!quit)
	{
		// timer
		lastTime = nowTime;
		nowTime = SDL_GetTicks();
		frameTime = nowTime - lastTime;
		deltaTime = ((double)(nowTime - lastTime)) / 1000.0;
		// events
		while (SDL_PollEvent(&event))
		{
			SDL_Scancode sc;
			SDL_WindowEventID weid;

			switch (event.type)
			{
				case SDL_QUIT:
					quit = true;
					break;
				case SDL_KEYDOWN:
					sc = event.key.keysym.scancode;
					if      (sc == SDL_SCANCODE_Q) {}
					else if (sc == SDL_SCANCODE_W) {}
					else if (sc == SDL_SCANCODE_E) {}
					else if (sc == SDL_SCANCODE_R) {}

					else if (sc == SDL_SCANCODE_A) {}
					else if (sc == SDL_SCANCODE_S) {}
					else if (sc == SDL_SCANCODE_D) {}
					else if (sc == SDL_SCANCODE_F) {}

					else if (sc == SDL_SCANCODE_Z) {}
					else if (sc == SDL_SCANCODE_X) {}
					else if (sc == SDL_SCANCODE_C) {}
					else if (sc == SDL_SCANCODE_V) {}

					break;
				case SDL_KEYUP:
					sc = event.key.keysym.scancode;
					if      (sc == SDL_SCANCODE_ESCAPE) quit = true;
					else if (sc == SDL_SCANCODE_SPACE) {}
					break;
				case SDL_WINDOWEVENT:
					weid = (SDL_WindowEventID)event.window.event;
					if (weid == SDL_WINDOWEVENT_SIZE_CHANGED) redraw = true;
					break;
				default:
					break;
			}
		}

		// update
		update();

		// render
			// prepare render
		glClearColor(bgColor.r, bgColor.g, bgColor.b, bgColor.a);
		glClear(GL_COLOR_BUFFER_BIT);
			// render our frame
		render();
			// render imgui
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame(window);
		ImGui::NewFrame();
		render_imgui();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
			// present frame
		SDL_GL_SwapWindow(window);
	}
}

} // namespace txo
