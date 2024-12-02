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
#include "Shader.h"

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
    camera.SetProjection(80.0f, 800.0f / 600, 0.1f, 100.0f);

    Transform cameraTransform{ { 0, 0, -20  } };

    // Shader

    VertexShader::uniforms.view = camera.GetView();
    VertexShader::uniforms.projection = camera.GetProjection();
    VertexShader::uniforms.light.position = glm::vec3{ 10, 10, -10 };
    VertexShader::uniforms.light.direction = glm::vec3{ 0, -1, 0 }; // light pointing down
    VertexShader::uniforms.light.color = color3_t{ 1 }; // white light
    VertexShader::uniforms.ambient = color3_t{ 0.01f };

    Shader::framebuffer = &framebuffer;

    // Models

    std::shared_ptr<Model> model = std::make_shared<Model>();
    std::shared_ptr<Model> modelTwo = std::make_shared<Model>();
    std::shared_ptr<Model> modelThree = std::make_shared<Model>();

    // Actors

    model->Load("cube.obj");
    //modelTwo->Load("sword.obj");
    //modelThree->Load("tree.obj");

    model->SetColor({ 0, 0, 1, 1 });
    /*modelTwo->SetColor({ 225, 103, 0, 12 });
    modelThree->SetColor({ 100, 25, 255, 60 });*/

    std::vector<std::unique_ptr<Actor>> actors;

    Transform transform{ glm::vec3{ 0 }, glm::vec3{ 0 }, glm::vec3{ 5 } };
    std::unique_ptr<Actor> actor = std::make_unique<Actor>(transform, model);
    actors.push_back(std::move(actor));




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

        framebuffer.Clear(color_t{ 0, 0, 0, 255 });

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
        VertexShader::uniforms.view = camera.GetView();

        framebuffer.DrawImage(0, 0, 800, 600, image);

        for (auto& actor : actors)
        {
            actor->GetTransform().rotation.y += time.GetDeltaTime() * 90;
            actor->Draw();
        }



        // model.Draw(framebuffer, transform.GetMatrix(), camera);

        // actor.Draw(framebuffer, camera);

        framebuffer.Update();

        renderer.CopyFramebuffer(framebuffer);

        SDL_RenderPresent(renderer.m_renderer);
    }

    return 0;
};