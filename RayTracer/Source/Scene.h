#pragma once
#include <vector>
#include <memory>
#include "Sphere.h"

class Scene
{
public:
	Scene() = default;
	void Render(class Framebuffer& framebuffer, const class Camera& camera, int numSamples = 10, int depth = 5);
	void AddObject(std::unique_ptr<class SceneObject> object) { m_objects.push_back(std::move(object)); }
	friend class Tracer;
private:
	std::vector< std::unique_ptr<class SceneObject>> m_objects;
};