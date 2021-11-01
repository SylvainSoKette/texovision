#include <iostream>
#include <random>

#include "imgui.h"

#include "application.hpp"
#include "quad.hpp"
#include "types.hpp"
#include "texture.hpp"


constexpr size_t default_texture_width { 128 };


struct Texovision : txo::Application {
	txo::Quad quad {
		glm::vec2(-1.f, -1.f), glm::vec2(-1.f, 1.f),
		glm::vec2(1.f, 1.f),   glm::vec2(1.f, -1.f)
	};
	txo::Texture texture {
		.bbp { 1 },
		.size { default_texture_width },
		.pixels { std::vector<float>(default_texture_width*default_texture_width) }
	};

	void _regen_values() {
		std::random_device dev;
		std::mt19937 rng { dev() };
		std::uniform_int_distribution<uint32_t> unif_i_dist(0,1);

		for (auto &pixel : texture.pixels) {
			pixel = unif_i_dist(rng);
		}

		quad.update_texture();
	}

	void init() override {
		quad.texture = &texture;
		quad.init();
		_regen_values();
	}

	void update() override {
	}

	void render() override {
		quad.render();
	}

	void render_imgui() override {
		ImGui::SetNextWindowSize(ImVec2{320, 200});

		ImGui::Begin("Random texture");
		if (ImGui::Button("Randomize !")) _regen_values();

		ImGui::End();
	}
};


int main()
{
	auto texovision { new Texovision }; // just in case we handle a big resource we don't want on the stack
	texovision->start();
	delete texovision;
	return EXIT_SUCCESS;
}
