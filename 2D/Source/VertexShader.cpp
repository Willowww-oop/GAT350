#include "VertexShader.h"

VertexShader::uniforms_t VertexShader::uniforms =
{
	glm::mat4{ 1 },// model
	glm::mat4{ 1 }, // view
	glm::mat4{ 1 }, // projection
	color3_t{ 1 }
};

void VertexShader::Process(const vertex_t& ivertex, vertex_output_t& overtex)
{
	glm::mat4 mvp = uniforms.projection * uniforms.view * uniforms.model;
	overtex.position = mvp * glm::vec4{ ivertex.position, 1 };
	glm::mat4 mv = uniforms.view * uniforms.model;
	overtex.normal = glm::normalize(glm::mat3{ mv } * ivertex.normal);

	glm::vec3 lightPosition = uniforms.light.position;
	lightPosition = uniforms.view * glm::vec4{ lightPosition, 1 };
	glm::vec3 vposition = mv * glm::vec4{ ivertex.position, 1 };
	glm::vec3 lightDir = glm::normalize(lightPosition - vposition);

	float intensity = std::max(0.0f, glm::dot(lightDir, overtex.normal));
	color3_t lightColor{ 0.8f };
	color3_t diffuse = lightColor * intensity;

	overtex.color = uniforms.ambient + diffuse;	
}
	