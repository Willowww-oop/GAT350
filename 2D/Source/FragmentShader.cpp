#include "FragmentShader.h"

color4_t FragmentShader::Process(const fragment_input_t& fragment)
{
	//float average = (fragment.color.r + fragment.color.g + fragment.color.b) / 3.0f ;

	//return { average, average, average, 1 };


	/*
	glm::vec3 lightPosition = Shader::uniforms.light.position;

	lightPosition = Shader::uniforms.view * glm::vec4{ lightPosition, 1 };

	glm::vec3 vposition = mv * glm::vec4{ ivertex.position, 1 };
	glm::vec3 lightDir = glm::normalize(Shader::uniforms.light.direction);
	//glm::vec3 lightDir = glm::normalize(lightPosition - vposition);

	float intensity = std::max(0.0f, glm::dot(lightDir, overtex.normal));
	color3_t lightColor{ 0.8f };
	color3_t diffuse = lightColor * intensity;

	overtex.color = Shader::uniforms.ambient + diffuse;
	*/

	return fragment.color;
}


