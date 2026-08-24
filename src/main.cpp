#include <SDL.h>
#include <cstdio>

namespace
{

constexpr int kGbcWidth = 160;
constexpr int kGbcHeight = 144;
constexpr int kWindowScale = 3;

} // namespace

int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window =
        SDL_CreateWindow("gbcemu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                         kGbcWidth * kWindowScale, kGbcHeight * kWindowScale, SDL_WINDOW_SHOWN);

    if (window == nullptr)
    {
        std::fprintf(stderr, "SDL_CreateWindow failed: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    bool running = true;
    SDL_Event event;
    while (running)
    {
        while (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
