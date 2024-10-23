#pragma once
#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/transform.hpp>

struct Transform
{
	glm::vec3 position{ 0 };
	glm::vec3 rotation{ 0 };
	glm::vec3 scale{ 1 };

	Transform() = default;
	Transform(const glm::vec3& position,
		const glm::vec3& rotation = glm::vec3{ 0 },
		const glm::vec3& scale = glm::vec3{ 1 }) :
		position{ position },
		rotation{ rotation },
		scale{ scale }
	{}

	glm::mat4 GetMatrix()
	{
		glm::mat4 mxs = glm::scale(scale);
		glm::mat4 mxt = glm::translate(position);
		glm::mat4 mxr = glm::eulerAngleYXZ(glm::radians(rotation.y), glm::radians(rotation.x), glm::radians(rotation.z));

		glm::mat4 mx = mxt * mxs * mxr;

		return mx;
	}

	glm::vec3 GetForward()
	{
		glm::mat4 mxr = glm::eulerAngleYXZ(glm::radians(rotation.y), glm::radians(rotation.x), glm::radians(rotation.z));

		return mxr * glm::vec4{ 0, 0, 1, 1 };
	}
	
	glm::vec3 GetUp()
	{
		glm::mat4 mxr = glm::eulerAngleYXZ(glm::radians(rotation.y), glm::radians(rotation.x), glm::radians(rotation.z));

		return mxr * glm::vec4{ 0, 1, 0, 1 };
	}

	glm::vec3 GetRight()
	{
		glm::mat4 mxr = glm::eulerAngleYXZ(glm::radians(rotation.y), glm::radians(rotation.x), glm::radians(rotation.z));

		return mxr * glm::vec4{ 1, 0, 0, 1 };
	}

};