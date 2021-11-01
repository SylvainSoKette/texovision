#pragma once

#include <cstddef>
#include <vector>

namespace txo {
	struct Texture {
		std::size_t bbp {1}; // byte per pixel
		std::size_t size {512}; // all textures are square
		std::vector<float> pixels;
	};
}
