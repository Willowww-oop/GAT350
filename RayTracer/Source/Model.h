#pragma once
#include "Color.h"
#include "Material.h"
#include "SceneObject.h"
#include <string>
#include <glm/glm.hpp>
#include <vector>

using vertex_t = glm::vec3;
using vertices_t = std::vector<vertex_t>;

class Model : public SceneObject
{
public:
	Model(std::shared_ptr<Material> material) : SceneObject{ material } {}
	Model(const Transform& transform, std::shared_ptr<Material> material) :
		SceneObject{ transform, material }
	{}
	Model(const vertices_t& vertices, std::shared_ptr<Material> material) : SceneObject{ material }, m_vertices{ vertices } {}

	void Update() override;

	void Draw(class Framebuffer& framebuffer, const glm::mat4& model, const class Camera& camera);
	bool Load(const std::string& filename);
	void SetColor(const color_t& color) { m_color = color; }

	bool Hit(const ray_t& ray, raycastHit_t& raycastHit, float minDistance, float maxDistance) override;

private:
	vertices_t m_vertices;
	color_t m_color{ 0 };
	vertices_t m_local_vertices;

	glm::vec3 m_center{ 0 };
	float m_radius{ 0 };
};