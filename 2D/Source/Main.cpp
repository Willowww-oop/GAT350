#include "Renderer.h"
#include "Framebuffer.h"
#include "MathUtils.h"
#include "Image.h"
#include "PostProcess.h"
#include "Model.h"
#include "Transform.h"
#include "ETime.h"
#include "Input.h"
#include "Camera.h" 
#include "Actor.h"
#include "Random.h"

#include <glm/gtc/matrix_transform.hpp>
#include <SDL.h>
#include <memory>

int main(int argc, char* argv[])
{
    Renderer renderer;
    renderer.Initialize();
    renderer.CreateWindow("2D", 800, 600);

    Input input;
    input.Initialize();
    input.Update();

    Time time;

    //Image image;
    //image.Load("image.png");

    //Image imageAlpha;
    //imageAlpha.Load("colors.png");
    //PostProcess::Alpha(imageAlpha.m_buffer, 128);
    SetBlendMode(BlendMode::Normal);

    Framebuffer framebuffer(renderer, 800, 600);

    Camera camera(800, 600);
    camera.SetView(glm::vec3{ 0, 0, -20 }, glm::vec3{ 0 });
    camera.SetProjection(60.0f, 800.0f / 600, 0.1f, 200.0f);

    Transform cameraTransform{ { 0, 0, -20  } };


    //vertices_t vertices = { { -5, 5, 0}, { 5, 5, 0 }, { -5, -5, 0} };
    //Model model(vertices, { 0, 255, 0, 255 });



    std::shared_ptr<Model> model = std::make_shared<Model>();
    model->Load("cube.obj");
    model->SetColor({ 255, 255, 0, 255 });

    std::vector<std::unique_ptr<Actor>> actors;

    for (int i = 0; i < 2; i++) 
    {
        Transform transform{ {randomf(-10.0f, 10.0f),randomf(-10.0f),0}, glm::vec3{0,randomf(-10.0f),45}, glm::vec3{3}};
		std::unique_ptr<Actor> actor = std::make_unique<Actor>(transform, model);
		actor->SetColor(color_t{ (uint8_t)random(256), (uint8_t)random(256), (uint8_t)random(256) });
		actors.push_back(std::move(actor));
    }

    //Actor actor(transform, model);



    bool quit = false;

    while (!quit)
    {
        time.Tick();
        input.Update();

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

        framebuffer.Clear(color_t { 0, 0, 0, 255 });

        int mx, my;
        SDL_GetMouseState(&mx, &my);


        //SetBlendMode(BlendMode::Normal);
        //framebuffer.DrawImage(200, 200, 300, 250, image);


        //SetBlendMode(BlendMode::Multiply);
        //framebuffer.DrawImage(100 , 100, imageAlpha);


        if (input.GetMouseButtonDown(2))
        {
            input.SetRelativeMode(true);
            glm::vec3 direction{ 0 };

            if (input.GetKeyDown(SDL_SCANCODE_D)) direction.x = -1;
            if (input.GetKeyDown(SDL_SCANCODE_A)) direction.x = 1;
            if (input.GetKeyDown(SDL_SCANCODE_E)) direction.y = -1;
            if (input.GetKeyDown(SDL_SCANCODE_Q)) direction.y = 1;
            if (input.GetKeyDown(SDL_SCANCODE_W)) direction.z = 1;
            if (input.GetKeyDown(SDL_SCANCODE_S)) direction.z = -1;

            cameraTransform.rotation.y += input.GetMouseRelative().x * 0.25f;
            cameraTransform.rotation.x += input.GetMouseRelative().y * 0.25f;

            glm::vec3 offset = cameraTransform.GetMatrix() * glm::vec4{ direction, 0 };

            cameraTransform.position += offset * 50.0f * time.GetDeltaTime();

        }

        else

        {
            input.SetRelativeMode(false);
        }

        camera.SetView(cameraTransform.position, cameraTransform.position + cameraTransform.GetForward());

        for(auto & actor : actors) 
        {
            actor->Draw(framebuffer, camera);
        }

        // model.Draw(framebuffer, transform.GetMatrix(), camera);

        // actor.Draw(framebuffer, camera);

        framebuffer.Update();

        renderer.CopyFramebuffer(framebuffer);

        SDL_RenderPresent(renderer.m_renderer);
    }

    return 0;
}