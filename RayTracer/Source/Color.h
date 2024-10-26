#pragma once
#include <algorithm>
#include <SDL.h>

using color_t = SDL_Color;

extern color_t(*blend_func)(const color_t& src, const color_t& dest);

enum class BlendMode
{
	Normal,
	Alpha,
	Additive,
	Multiply
};

color_t NormalBlend(const color_t& src, const color_t& dest);
color_t AlphaBlend(const color_t& src, const color_t& dest);
color_t AdditiveBlend(const color_t& src, const color_t& dest);
color_t MultiplyBlend(const color_t& src, const color_t& dest);

void SetBlendMode(BlendMode blendMode);
color_t ColorBlend(const color_t& src, const color_t& dest);
