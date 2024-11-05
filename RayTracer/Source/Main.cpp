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
#include "Triangle.h"
#include "Scene.h"
#include "Plane.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include <iostream>

void InitScene(Scene& scene);

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
	camera.SetView({ 0, 2, -5 }, { 0, 0, 0 });

	Scene scene;

	InitScene(scene);

	scene.Update();
	scene.Render(framebuffer, camera, 10, 3);

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

		renderer = framebuffer;
		SDL_RenderPresent(renderer.m_renderer);
	}

	return 0;
}

void InitScene(Scene& scene) 
{
	scene.SetSky(HSVtoRGB(25, 1, 0.2f), HSVtoRGB(150, 1, 0.5f));		

	std::shared_ptr<Material> gray = std::make_shared<Lambertian>(color3_t{ 0.5f });
	std::shared_ptr<Material> red = std::make_shared<Lambertian>(color3_t{ 1, 0, 0 });
	std::shared_ptr<Material> green = std::make_shared<Lambertian>(color3_t{ 0, 1, 0 });
	std::shared_ptr<Material> pink = std::make_shared<Emissive>(color3_t{ 1, 0, 1 });
	std::shared_ptr <Material> blue = std::make_shared<Metal>(color3_t{ 0, 0, 1 }, 0.1f);
	std::vector<std::shared_ptr<Material>> materials;
	materials.push_back(red);
	materials.push_back(green);
	materials.push_back(pink);
	materials.push_back(blue);

	auto plane = std::make_unique<Plane>(Transform{ glm::vec3{ 0, -2, 0 }, glm::vec3{ 0, 0, 0 } }, gray);
	scene.AddObject(std::move(plane));

	//auto object = std::make_unique<Sphere>(Transform{ glm::vec3{ random(glm::vec3{ -10 }, glm::vec3{ 10 })} }, randomf(0.2f, 3.0f), materials[random(0, (int)materials.size())]);
	//scene.AddObject(std::move(object));

	//auto triangle = std::make_unique<Triangle>(glm::vec3{ -10,0,0 }, glm::vec3{ -5,10,0 }, glm::vec3{ 0,0,0 }, green);
	//scene.AddObject(std::move(triangle));

	vertices_t vertice = { glm::vec3{ 0 }, glm::vec3{ 0 }, glm::vec3{ 0 } };

	auto model = std::make_unique<Model>(vertice, blue);
	model->Load("cube.obj");
	scene.AddObject(std::move(model));

	//for (int i = 0; i < 20; i++)
	//{
	
	//auto model = std::make_unique<Model>(Transform glm::vec{ 7 } }, std::make_shared<Lambertian>(HSVtoRGB(randomf(0, 360), 1.0f, 1.0f));

}