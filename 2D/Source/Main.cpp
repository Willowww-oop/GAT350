#include "Renderer.h"
#include "Framebuffer.h"
#include "MathUtils.h"
#include "Image.h"
#include "PostProcess.h"

#include <SDL.h>
#include <iostream>

int main(int argc, char* argv[])
{
    Renderer renderer;
    renderer.Initialize();
    renderer.CreateWindow("2D", 800, 600);
    Image image;
    image.Load("image.png");

    Framebuffer framebuffer(renderer, 800, 600);

    bool quit = false;

    while (!quit)
    {
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

       // framebuffer.DrawRect(100, 200, 300, 100, { 120, 0, 255, 33 });
        
        framebuffer.DrawLine(200, 300, 250, 350, { 123, 188, 55, 21 });
        framebuffer.DrawLineSlope(50, 600, 200, 150, { 44, 21, 55, 65 });
        framebuffer.DrawTriangle(200, 20, 240, 120, 160, 120, { 35, 103, 31, 34 });

        framebuffer.DrawCirclePoints(50, 50, 100, 300, { 221, 50, 12, 33 });
        framebuffer.DrawFullCircle(50, 50, 55, { 150, 175, 33, 35 });

        framebuffer.DrawLinearCurve(100, 100, 200, 200, { 255, 255, 0, 255 });
        framebuffer.DrawQuadraticCurve(
            100, 200,
            mx, my,
            300, 200, { 255, 255, 0, 255 });
        framebuffer.DrawCubicCurve(
            100, 200,
            100, 100,
            200, 100,
            200, 200, { 255, 0, 0, 255 });

        int ticks = SDL_GetTicks();
        float time = ticks * 0.1f;
        float t = std::abs(std::sin(time));

        //framebuffer.DrawRect(20, 20, 40, 40, { 255, 0, 255, 200 });


        framebuffer.DrawImage(10, 10, image);

        PostProcess::Brightness(framebuffer.m_buffer, 60);

        framebuffer.Update();

        renderer.CopyFramebuffer(framebuffer);

        SDL_RenderPresent(renderer.m_renderer);
    }

    return 0;
}