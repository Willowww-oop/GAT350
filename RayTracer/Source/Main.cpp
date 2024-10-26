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
    renderer.CreateWindow("RayTracer", 800, 600);

    Input input;
    input.Initialize();
    input.Update();

    Time time;

    Image image;
    image.Load("nightsky.png");

    SetBlendMode(BlendMode::Normal);

    Framebuffer framebuffer(renderer, 800, 600);

    Camera camera(800, 600);
    camera.SetView(glm::vec3{ 0, 0, -20 }, glm::vec3{ 0 });
    camera.SetProjection(60.0f, 800.0f / 600, 0.1f, 200.0f);

    Transform cameraTransform{ { 0, 0, -20  } };


    //vertices_t vertices = { { -5, 5, 0}, { 5, 5, 0 }, { -5, -5, 0} };
    //Model model(vertices, { 0, 255, 0, 255 });



    std::shared_ptr<Model> model = std::make_shared<Model>();
    std::shared_ptr<Model> modelTwo = std::make_shared<Model>();
    std::shared_ptr<Model> modelThree = std::make_shared<Model>();

    model->Load("cube.obj");
    modelTwo->Load("sword.obj");
    modelThree->Load("tree.obj");

    model->SetColor( { 255, 255, 0, 255 } );
    modelTwo->SetColor( { 225, 103, 0, 12 } );
    modelThree->SetColor( {100, 25, 255, 60} );

    std::vector<std::unique_ptr<Actor>> actors;

    for (int i = 0; i < 2; i++) 
    {
        Transform transform { { 0, 5, 0 }, glm::vec3{0, 90, -180 }, glm::vec3{ 5 } };
        Transform transformTwo { { 10, 5, 0 }, glm::vec3{0, 5, -180 }, glm::vec3{ 3 } };
        Transform transformThree { { 100, 5, 0 }, glm::vec3{0, 5, -180 }, glm::vec3{ 5 } };

        std::unique_ptr<Actor> actor = std::make_unique<Actor>(transform, model);
        std::unique_ptr<Actor> actorTwo = std::make_unique<Actor>(transformTwo, modelTwo);
        std::unique_ptr<Actor> actorThree = std::make_unique<Actor>(transformThree, modelThree);

        actors.push_back(std::move(actor));
        actors.push_back(std::move(actorTwo));
        actors.push_back(std::move(actorThree));
    }




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

            cameraTransform.rotation.y += input.GetMouseRelative().x * 0.1f;
            cameraTransform.rotation.x += input.GetMouseRelative().y * 0.1f;

            glm::vec3 offset = cameraTransform.GetMatrix() * glm::vec4{ direction, 0 };

            cameraTransform.position += offset * 70.0f * time.GetDeltaTime();

        }

        else

        {
            input.SetRelativeMode(false);
        }

        camera.SetView(cameraTransform.position, cameraTransform.position + cameraTransform.GetForward());

        framebuffer.DrawImage(0, 0, 800, 600, image);

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
};