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

	std::shared_ptr<Lambertian> gray = std::make_shared<Lambertian>(color3_t{ 0.5f });
	std::shared_ptr<Lambertian> red = std::make_shared<Lambertian>(color3_t{ 1, 0, 0 });
	std::shared_ptr<Lambertian> blue = std::make_shared<Lambertian>(color3_t{ 0, 0, 1 });
	std::vector<std::shared_ptr<Lambertian>> materials;
	materials.push_back(red);
	materials.push_back(blue);


	/*auto material2 = std::make_shared<Lambertian>(color3_t{ 0.0f, 0.0f, 1.0f });
	auto plane = std::make_unique<Plane>(glm::vec3{ 0, -5, 0 }, glm::vec3{ 0, 1, 0 }, material2);
	scene.AddObject(std::move(plane));*/
	
	auto plane = std::make_unique<Plane>(glm::vec3{ 0, -5, 0 }, glm::vec3{ 0, 1, 0 }, gray); scene.AddObject(std::move(plane));

	for (int i = 0; i < 20; i++)
	{
		auto object = std::make_unique<Sphere>(random(glm::vec3{ -10 }, glm::vec3{ 10 }), randomf(0.2f, 3.0f), materials[random(0, (int)materials.size())]);

		scene.AddObject(std::move(object));

	}

	//framebuffer.Clear(ColorConvert(color4_t{ 0, 0.25f, 0, 255 }));
	scene.Render(framebuffer, camera);

	framebuffer.Update();

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


		renderer = framebuffer;
		SDL_RenderPresent(renderer.m_renderer);
	}

	return 0;
}