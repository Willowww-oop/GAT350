#include "Framebuffer.h"
#include "Renderer.h"
#include "MathUtils.h"
#include "Image.h"
#include <iostream>

Framebuffer::Framebuffer(const Renderer& renderer, int width, int height)
{
	m_width = width;
	m_height = height;
	m_pitch = width * sizeof(color_t);

	m_texture = SDL_CreateTexture(renderer.m_renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, width, height);
	if (m_texture == nullptr)
	{
		std::cerr << "Error initializing SDL: " << SDL_GetError() << std::endl;
	}
	m_buffer.resize(m_width * m_height);
}

Framebuffer::~Framebuffer()
{
	SDL_DestroyTexture(m_texture);
}

void Framebuffer::Update()
{
	SDL_UpdateTexture(m_texture, NULL, m_buffer.data(), m_pitch);
}

void Framebuffer::Clear(const color_t& color)
{
	std::fill(m_buffer.begin(), m_buffer.end(), color);
}

void Framebuffer::DrawPoint(int x, int y, const color_t& color)
{
	if (x < 0 || x > m_width || y < 0 || y > m_height) return;

	m_buffer[x + y * m_width] = color;
}


void Framebuffer::DrawLinearCurve(int x1, int y1, int x2, int y2, const color_t& color)
{

	float dt = 1 / 10.0f;
	float t1 = 0;
	for (int i = 0; i < 10; i++)
	{
		int sx1 = Lerp(x1, x2, t1);
		int sy1 = Lerp(y1, y2, t1);

		float t2 = t1 + dt;

		int sx2 = Lerp(x1, x2, t2);
		int sy2 = Lerp(y1, y2, t2);
		t1 += dt;


		DrawLine(sx1, sy1, sx2, sy2, color);
	}
}

void Framebuffer::DrawQuadraticCurve(int x1, int y1, int x2, int y2, int x3, int y3, const color_t& color)
{
	float dt = 1 / 50.0f;
	float t1 = 0;
	for (int i = 0; i < 50; i++)
	{
		int sx1, sy1;
		QuadraticPoint(x1, y1, x2, y2, x3, y3, t1, sx1, sy1);

		float t2 = t1 + dt;
		int sx2, sy2;
		QuadraticPoint(x1, y1, x2, y2, x3, y3, t1, sx2, sy2);

		t1 += dt;


		DrawLine(sx1, sy1, sx2, sy2, color);
	}
}

void Framebuffer::DrawCubicCurve(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, const color_t& color)
{
	float dt = 1 / 50.0f;
	float t1 = 0;
	for (int i = 0; i < 50; i++)
	{
		int sx1, sy1;
		CubicPoint(x1, y1, x2, y2, x3, y3, x4, y4, t1, sx1, sy1);

		float t2 = t1 + dt;
		int sx2, sy2;
		CubicPoint(x1, y1, x2, y2, x3, y3, x4, y4, t1, sx2, sy2);

		t1 += dt;


		DrawLine(sx1, sy1, sx2, sy2, color);
	}
}

void Framebuffer::DrawLine(int x1, int y1, int x2, int y2, const color_t& color)
{
	int dx = x2 - x1; 
	int dy = y2 - y1; 

	bool steep = (std::abs(dx) > std::abs(dy));

	if (steep)
	{
		std::swap(x1, y1);
		std::swap(x2, y2);
	}

	if (x1 > x2)
	{
		std::swap(x1, y1);
		std::swap(x2, y2);
	}

	// recalculating deltas
	dx = x2 - x1; 
	dy = y2 - y1; 

	// set error term and y step direction
	int error = dx / 2;
	int ystep = (y1 < y2) ? 1 : -1;

	// draw line points
	for (int x = x1, y = y1; x <= x2; x++)
	{
		(steep) ? DrawPoint(y, x, color) : DrawPoint(x, y, color);

		// update error term
		error -= dy;

		if (error < 0)
		{
			y += ystep;
			error += dx;
		}
	}
}

void Framebuffer::DrawLineSlope (int x1, int y1, int x2, int y2, const color_t& color)
{
	int dx = x2 - x1; // run
	int dy = y2 - y1; // rise

	if (dx == 0)
	{
		if (y1 > y2) std::swap(y1, y2);
		for (int y = y1; y < y2; y++)
		{
			m_buffer[x1 + y * m_width] = color;
		}
	}
	else
	{
		float m = dy / (float)dx;

		float b = y1 - (m * x1);

		// draw line points

		if (std::abs(dx) > std::abs(dy))
		{
			for (int x = x1; x <= x2; x++)
			{
				int y = (int)round((m * x) + b);
				m_buffer[x + y * m_width] = color;
			}
		}
		else
		{
			for (int y = y1; y <= y2; y++)
			{
				int x = (int)round((y - b) / m);
				m_buffer[x + y * m_width] = color;
			}
		}
	}
}


void Framebuffer::DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, const color_t& color)
{
	DrawLineSlope(x1, y1, x2, y2, color);
	DrawLineSlope(x2, y2, x3, y3, color);
	DrawLineSlope(x3, y3, x1, y1, color);

}

void Framebuffer::DrawRect(int x, int y, int w, int h, const color_t& color)
{
	if (x + w < 0 || x >= m_width || y + h < 0 || y >= m_height) return;

	int x1 = std::max(x, 0);
	int x2 = std::min(x + w, m_width);
	int y1 = std::max(y, 0);
	int y2 = std::min(y + h, m_height);

	for (int sy = y1; sy < y2; sy++)
	{
		int index = x1 + sy * m_width;
		std::fill(m_buffer.begin() + index, m_buffer.begin() + (index + x2 - x1), color);
		/*for (int sx = x1; sx < x2; sx++)
		{
			m_buffer[sx + sy * m_width] = color;
			// m_buffer[index++] = color;
		}
		*/
	}
}

void Framebuffer::DrawCirclePoints(int xc, int yc, int x, int y, const color_t& color)
{
	DrawPoint(xc + x, yc + y, color);
	DrawPoint(xc - x, yc + y, color);
	DrawPoint(xc + x, yc - y, color);
	DrawPoint(xc - x, yc - y, color);
	DrawPoint(xc + y, yc + x, color);
	DrawPoint(xc - y, yc + x, color);
	DrawPoint(xc + y, yc - x, color);
	DrawPoint(xc - y, yc - x, color);

}

void Framebuffer::DrawFullCircle(int xc, int yc, int radius, const color_t& color)
{
	int x = 0, y = radius;
	int d = 3 - 2 * radius;
	DrawCirclePoints(xc, yc, x, y, color);
	while (y >= x) {

		if (d > 0) {
			y--;
			d = d + 4 * (x - y) + 10;
		}
		else
			d = d + 4 * x + 6;

		x++;

		DrawCirclePoints(xc, yc, x, y, color);
	}
}




void Framebuffer::DrawImage(int x, int y, const Image& image)
{
	// check if off-screen
	if (x + image.m_width < 0 || x >= image.m_width || y + image.m_height < 0 || y >= image.m_height) return;

	// iterate through image y
	for (int iy = 0; iy < image.m_height; iy++)
	{
		// set screen y 
		int sy = y + iy;
		// check if off-screen, don't draw if off-screen
		if (sy < 0 || sy >= image.m_height) continue;

		// iterate through image x
		for (int ix = 0; ix < image.m_width; ix++)
		{

			// set screen x
			int sx = x + ix;
			// check if off-screen, don't draw if off-screen
			if (sx < 0 || sx >= image.m_width) continue;

			// get image pixel color
			color_t color = image.m_buffer[ix + iy * m_width];

			// check alpha, if 0 don't draw
			if (color.a == 0) continue;
			// set buffer to color
			m_buffer[sx + sy * m_width] = color;
		}
	}
}