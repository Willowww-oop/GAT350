#include "Model.h"
#include "Framebuffer.h"
#include "Camera.h"



void Model::Draw(Framebuffer& framebuffer, const glm::mat4& model, const Camera& camera)
{
	for (int i = 0; i < m_vertices.size(); i += 3)
	{
		// Convert point from model space to world space

		vertex_t p1 = model * glm::vec4{ m_vertices[i], 1 };
		vertex_t p2 = model * glm::vec4{ m_vertices[i + 1], 1 };
		vertex_t p3 = model * glm::vec4{ m_vertices[i + 2], 1 };

		// Convert point from model space to view space

		p1 = camera.ModelToView(p1);
		p2 = camera.ModelToView(p2);
		p3 = camera.ModelToView(p3);

		// Convert point from view space to projection space

		p1 = camera.ViewToProjection(p1);
		p2 = camera.ViewToProjection(p2);
		p3 = camera.ViewToProjection(p3);

		
		glm::ivec2 s1 = camera.ToScreen(p1);
		glm::ivec2 s2 = camera.ToScreen(p2);
		glm::ivec2 s3 = camera.ToScreen(p3);

		if (s1.x == -1 || s1.y == -1 || s2.x == -1 || s2.y == -1 || s3.x == -1 || s3.y == -1)
		{
			continue;
		}


		framebuffer.DrawTriangle((int)p1.x, (int)p1.y, (int)p2.x, (int)p2.y, (int)p3.x, (int)p3.y, m_color);
	}
}
