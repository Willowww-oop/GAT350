#pragma once
#include "glm/glm.hpp"
#include "Color.h"

struct light_t
{
	glm::vec3 position;
	glm::vec3 direction;
	color3_t color;
};