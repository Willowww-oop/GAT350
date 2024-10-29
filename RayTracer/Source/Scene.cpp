#include "Scene.h"
#include "Framebuffer.h"
#include "Camera.h"
#include "Color.h"
#include "Tracer.h"
#include <iostream>


void Scene::Render(Framebuffer& framebuffer, const Camera& camera)
{
	for (int y = 0; y < framebuffer.m_height; y++) {
		for (int x = 0; x < framebuffer.m_width; x++) {
			glm::vec2 pixel{ x,y };
			glm::vec2 point = pixel / glm::vec2{ framebuffer.m_width, framebuffer.m_height };
			point.y = 1 - point.y;

			ray_t ray = camera.GetRay(point);

			color3_t color = Tracer::Trace(*this, ray, 0.001f, 100.0f);

			//color4_t color = { 1,0,0,1 };

			framebuffer.DrawPoint(x, y, ColorConvert(color));
		}
		std::cout << "y: " << y << std::endl;
	}
}