#include "SDL.h"
#include "Renderer.h"
#include "Framebuffer.h"
#include "PostProcess.h"
#include "Image.h"
#include "Model.h"
#include "Transform.h"
#include "ETime.h"
#include "Input.h"
#include "Camera.h"
#include "Actor.h"
#include "Random.h"
#include "Tracer.h"
#include "Scene.h"
#include "Plane.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include <iostream>

int main(int argc, char* argv[])
{
	srand((unsigned int)time(NULL));

	Time time;
	std::string str = "title";
	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow(str, 800, 600);

	SetBlendMode(BlendMode::Normal);

	Framebuffer framebuffer(renderer, 800, 600);

	Camera camera{ 70.0f, renderer.GetWidth() / (float)(renderer.GetHeight()) };
	camera.SetView({ 0, 0, -20 }, { 0, 0, 0 });

	Scene scene;

	auto material2 = std::make_shared<Lambertian>(color3_t{ 0.0f, 0.0f, 1.0f });
	auto plane = std::make_unique<Plane>(glm::vec3{ 0, -5, 0 }, glm::vec3{ 0, 1, 0 }, material2);
	scene.AddObject(std::move(plane));

	auto material = std::make_shared<Lambertian>(color3_t{ 0.0f, 1.0f, 0.0f });
	auto object = std::make_unique<Sphere>(glm::vec3{ 0.0f }, 3.0f, material);
	scene.AddObject(std::move(object));


	framebuffer.Clear(ColorConvert(color4_t{ 0, 0.25f, 0, 255 }));
	scene.Render(framebuffer, camera);


	bool quit = false;
	while (!quit)
	{
		time.Tick();
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				quit = true;
			}
			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
			{
				quit = true;
			}
		}

		//tracer.Render(framebuffer, camera);

		framebuffer.Update();

		renderer = framebuffer;
		SDL_RenderPresent(renderer.m_renderer);
	}

	return 0;
}