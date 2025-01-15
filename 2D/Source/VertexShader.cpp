#include "VertexShader.h"
#include "Framebuffer.h"
#include "Shader.h"

void VertexShader::Process(const vertex_t& ivertex, vertex_output_t& overtex)
{
	glm::mat4 mvp = Shader::uniforms.projection * Shader::uniforms.view * Shader::uniforms.model;
	overtex.position = mvp * glm::vec4{ ivertex.position, 1 };
	glm::mat4 mv = Shader::uniforms.view * Shader::uniforms.model;
	overtex.normal = glm::normalize(glm::mat3{ mv } * ivertex.normal);
	overtex.vposition = mv * glm::vec4{ ivertex.position, 1 };

	glm::vec3 lightPosition = Shader::uniforms.light.position;

	lightPosition = Shader::uniforms.view * glm::vec4{ lightPosition, 1 };
	
	glm::vec3 vposition = mv * glm::vec4{ ivertex.position, 1 };
	glm::vec3 lightDir = glm::normalize(Shader::uniforms.light.direction);
	//glm::vec3 lightDir = glm::normalize(lightPosition - vposition);

	float intensity = std::max(0.0f, glm::dot(lightDir, overtex.normal));
	color3_t lightColor{ 0.8f };
	color3_t diffuse = lightColor * intensity;

	overtex.color = Shader::uniforms.ambient + diffuse;	
}
	