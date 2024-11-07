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
void InitScene01(Scene& scene, Camera& camera);

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
	camera.SetView({ 0, 4, -25}, { 0, 0, 0 });

	Scene scene;

	InitScene(scene);
	//InitScene01(scene, camera);

	scene.Update();
	scene.Render(framebuffer, camera, 200, 10);

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
	//scene.SetSky(HSVtoRGB(25, 1, 0.2f), HSVtoRGB(150, 1, 0.5f));		

	std::shared_ptr<Material> gray = std::make_shared<Lambertian>(color3_t{ 0.5f });
	std::shared_ptr<Material> red = std::make_shared<Lambertian>(color3_t{ 1, 0, 0 });
	std::shared_ptr<Material> green = std::make_shared<Lambertian>(color3_t{ 0, 1, 0 });
	std::shared_ptr<Material> yellow = std::make_shared<Lambertian>(color3_t{ 1, 1, 0 });
	std::shared_ptr<Material> cyan = std::make_shared<Lambertian>(color3_t{ 0, 1, 1 });
	std::shared_ptr<Material> purple = std::make_shared<Lambertian>(color3_t{ 1, 0, 1 });
	std::shared_ptr<Material> white = std::make_shared<Lambertian>(color3_t{ 1, 1, 1 });
	std::shared_ptr<Material> whiteLight = std::make_shared<Emissive>(color3_t{ 1, 1, 1 }, 12);
	std::vector<std::shared_ptr<Material>> materials;
	materials.push_back(red);
	materials.push_back(green);
	materials.push_back(yellow);
	materials.push_back(cyan);
	materials.push_back(purple);
	materials.push_back(white);
	materials.push_back(whiteLight);

	auto plane = std::make_unique<Plane>(Transform{ glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 0, 0 } }, white);
	auto plane2 = std::make_unique<Plane>(Transform{ glm::vec3{ 15, 0, 0 }, glm::vec3{ 0, 0, 90 } }, green);
	auto plane3 = std::make_unique<Plane>(Transform{ glm::vec3{ -15, 0, 0 }, glm::vec3{ 0, 0, -90 } }, red);
	auto plane4 = std::make_unique<Plane>(Transform{ glm::vec3{ 0, 0, 20 }, glm::vec3{ -90, 0, 0 } }, white);
	auto planeroof = std::make_unique<Plane>(Transform{ glm::vec3{ 0, 15, 0 }, glm::vec3{ 0, 0, 0 } }, white);

	scene.AddObject(std::move(plane));
	scene.AddObject(std::move(plane2));
	scene.AddObject(std::move(plane3));
	scene.AddObject(std::move(plane4));
	scene.AddObject(std::move(planeroof));

	auto model = std::make_unique<Model>(Transform{ glm::vec3{ 0, 2, 0 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 3.3f } }, gray);
	auto bunny = std::make_unique<Model>(Transform{ glm::vec3{ 10, 2, -2 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 2 } }, cyan);
	auto model2 = std::make_unique<Model>(Transform{ glm::vec3{ 0, 15, 3 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 5.5f, 0.5f, 5.5f } }, whiteLight);

	model->Load("cube.obj");
	bunny->Load("bunny.obj");
	model2->Load("cube.obj");

	scene.AddObject(std::move(model));
	scene.AddObject(std::move(bunny));
	scene.AddObject(std::move(model2));
}

void InitScene01(Scene& scene, Camera& camera)
{
	camera.SetFOV(20.0f);
	camera.SetView({ 13, 2, 3 }, { 0, 0, 0 });

	auto ground_material = std::make_shared<Lambertian>(color3_t(0.5f));
	scene.AddObject(std::make_unique<Plane>(Transform{ glm::vec3{ 0 } }, ground_material));

	for (int a = -11; a < 11; a++) 
	{
		for (int b = -11; b < 11; b++) 
		{
			auto choose_mat = randomf();
			glm::vec3 center(a + 0.9 * randomf(), 0.2, b + 0.9 * randomf());

			if ((center - glm::vec3(4, 0.2, 0)).length() > 0.9) 
			{
				std::shared_ptr<Material> sphere_material;

				if (choose_mat < 0.8) 
				{
					// diffuse
					auto albedo = HSVtoRGB(randomf(0, 360), 1.0f, 1.0f);
					sphere_material = std::make_shared<Lambertian>(albedo);
					scene.AddObject(std::make_unique<Sphere>(Transform{ center }, 0.2f, sphere_material));
				}
				else if (choose_mat < 0.95) 
				{
					// metal
					auto albedo = HSVtoRGB(randomf(0, 360), 1.0f, 1.0f);
					auto fuzz = randomf(0.0f, 0.5f);
					sphere_material = std::make_shared<Metal>(albedo, fuzz);
					scene.AddObject(std::make_unique<Sphere>(Transform{ center }, 0.2f, sphere_material));
				}
				else 
				{
					// glass
					sphere_material = std::make_shared<Dielectric>(color3_t{ 1 }, 1.5f);
					scene.AddObject(std::make_unique<Sphere>(Transform{ center }, 0.2f, sphere_material));
				}
			}
		}
	}

	auto material1 = std::make_shared<Dielectric>(color3_t{ 1 }, 1.5f);
	scene.AddObject(std::make_unique<Sphere>(Transform{ glm::vec3{ 0, 1, 0 } }, 1.0f, material1));

	auto material2 = std::make_shared<Lambertian>(color3_t(0.4f, 0.2f, 0.1f));
	scene.AddObject(std::make_unique<Sphere>(Transform{ glm::vec3{ -4, 1, 0 } }, 1.0f, material2));
		
	auto material3 = std::make_shared<Metal>(color3_t(0.7f, 0.6f, 0.5f), 0.0f);
	scene.AddObject(std::make_unique<Sphere>(Transform{ glm::vec3{ 4, 1, 0 } }, 1.0f, material3));
}
