#include "imgui.h"

#include "application.hpp"
#include "quad.hpp"
#include "types.hpp"


static txo::Quad quad {
	glm::vec2(-1.f, -1.f), glm::vec2(-1.f, 1.f),
	glm::vec2(1.f, 1.f), glm::vec2(1.f, -1.f)
};

static const uint size {512};
static const size_t bit_per_pixel {1};
static const u8 texture_content[bit_per_pixel* size * size] {0};


struct Texovision : txo::Application {
	void init() override {
		quad.init(); // makes me think Application and Quad should not be the same project since I need to glue them together here
		// ou alors un genre de add(quad) qui fait le init du quad et le chargement des ressources ? ça commence à faire moteur
		// de jeu complet là...
	}

	void update() override {
	}

	void render() override {
		quad.render();
	}

	void render_imgui() override {
		static int facet_number = 10;
		static float sensitivity = 0.3f;

		ImGui::Begin("Voronoi texture");
		ImGui::SetWindowSize(ImVec2{320, 600});
		ImGui::SliderInt("facets", &facet_number, 1, 200);
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("Set the number of points used to generate the voronoi pattern with.");
		ImGui::SliderFloat("sensitivity", &sensitivity, 0.01f, 1.0f);
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("Set the speed at which a point will lose it's influence over neighboring pixels.");
		ImGui::End();
	}
};


int main()
{
	auto texovision { new Texovision }; // don't risk Texovision being bigger than the stack since it will contain every resource the app needs.
	texovision->start(); // vroom vroom
	delete texovision; // or don't and let the OS do it, so it's much faster ? :)
	return EXIT_SUCCESS;
}
