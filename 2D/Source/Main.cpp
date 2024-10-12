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


        framebuffer.DrawImage(120, 200, image);
        framebuffer.DrawImage(300, 10, 400, 100, image);

        //PostProcess::Invert(framebuffer.m_buffer);
        //PostProcess::Monochrome(framebuffer.m_buffer);
        //PostProcess::ColorBalance(framebuffer.m_buffer, 150, -50, -50);
        //PostProcess::Brightness(framebuffer.m_buffer, 50);
        //PostProcess::Noise(framebuffer.m_buffer, 80);
        //PostProcess::Threshold(framebuffer.m_buffer, 150);
        PostProcess::Posterize(framebuffer.m_buffer, 6);

        //PostProcess::BoxBlur(framebuffer.m_buffer, framebuffer.m_width, framebuffer.m_height);

        framebuffer.Update();

        renderer.CopyFramebuffer(framebuffer);

        SDL_RenderPresent(renderer.m_renderer);
    }

    return 0;
}