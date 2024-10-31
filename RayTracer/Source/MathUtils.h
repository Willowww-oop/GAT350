#pragma once
#include <glm/glm.hpp>

template<typename T> 
inline T Lerp(const T& a, const T& b, float t)
{
	return static_cast<T>(a + ((b - a) * t));
};


inline glm::vec3 Cross(const glm::vec3& v1, const glm::vec3& v2)
{
	glm::vec3 result;

	result.x = v1.y * v2.z - v2.y * v1.z;
	result.y = v1.z * v2.x - v2.z * v1.x;
	result.z = v1.x * v2.y - v2.x * v1.y;

	return result;
};

inline float Dot(const glm::vec3& v1, const glm::vec3& v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
};

inline float Angle(const glm::vec3& v1, const glm::vec3& v2)
{
	return glm::acos(glm::dot(glm::normalize(v1), glm::normalize(v2)));
};

inline glm::vec3 Reflect(const glm::vec3& i, const glm::vec3& n)
{
	return i - ((Dot(i, n) * n) * 2.0f);
};

//inline glm::vec3 Refract(const glm::vec3& i, const glm::vec3& n, float ri, glm::vec3& refracted)
//{
//	glm::vec3 ni = glm::normalize(i);
//	float cosine = glm::dot(ni, n);
//
//	float discriminant = i - (ri * ri) * (1 - cosine * cosine);
//
//	if (discriminant >= 0)
//	{
//		refracted = ri * (ni - (n * cosine)) - (n * glm::sqrt(discriminant));
//		return true;
//	}
//
//	return false;
//};


inline bool approximately(float value1, float value2)
{
	// check if the difference between the values is less than epsilon

	return ((value2 - value1) < FLT_EPSILON);
};

template<typename T>
inline T Clamp(const T& value, const T& min, const T& max)
{
	return (value < min) ? min : (value > max) ? max : value;
};



inline void QuadraticPoint(int x1, int y1, int x2, int y2, int x3, int y3, float t, int& x, int& y)
{
	float one_minus_t = 1 - t;

	float a = one_minus_t * one_minus_t;
	float b = 2 * one_minus_t * t;
	float c = t * t;

	x = (int)(a * x1 + b * x2 + c * x3);
	y = (int)(a * y1 + b * y2 + c * x3);
};

inline void CubicPoint(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, float t, int& x, int& y)
{
	float one_minus_t = 1 - t;

	float a = one_minus_t * one_minus_t * one_minus_t;
	float b = 3 * (one_minus_t * one_minus_t) * t;
	float c = 3 * one_minus_t * (t * t);
	float d = t * t * t;

	x = (int)((a * x1) + (b * x2) + (c * x3) + (d * x4));
	y = (int)((a * y1) + (b * y2) + (c * y3) + (d * y4));
};



