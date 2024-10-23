#pragma once
#include "Color.h"
#include <glm/glm.hpp>
#include <vector>

using vertex_t = glm::vec3;
using vertices_t = std::vector<vertex_t>;

class Model
{
public:
	Model() = default;
	Model(const vertices_t& vertices, const color_t& color) : m_vertices{ vertices }, m_color{ color } {}
	 
	void Draw(class Framebuffer& framebuffer, const glm::mat4& model, const class Camera& camera);
	
private:
	vertices_t m_vertices;
	color_t m_color;
};