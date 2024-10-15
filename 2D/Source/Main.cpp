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

    Image imageAlpha;
    imageAlpha.Load("colors.png");
    PostProcess::Alpha(imageAlpha.m_buffer, 128);

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


        //framebuffer.DrawImage(120, 200, image);

        SetBlendMode(BlendMode::Alpha);

        framebuffer.DrawImage(0, 0, 200, 150, image);

        SetBlendMode(BlendMode::Normal);

        framebuffer.DrawImage(200 , 200, imageAlpha);

        framebuffer.Update();

        renderer.CopyFramebuffer(framebuffer);

        SDL_RenderPresent(renderer.m_renderer);
    }

    return 0;
}