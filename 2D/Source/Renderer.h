#pragma once
#include "Framebuffer.h"
#include <SDL.h>
#include <string>


class Renderer
{
public:
	bool Initialize();
	bool CreateWindow(string name, int width, int height);
	void CopyFramebuffer(const Framebuffer& framebuffer);

	void operator = (const class Framebuffer& framebuffer);
	SDL_Renderer* m_renderer{ nullptr };

private:
	int m_width{ 0 };
	int m_height{ 0 };
	
	SDL_Window* m_window{ nullptr };
};