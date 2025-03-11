#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

using namespace std;

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 700;
const string Window_Title = "Mindustry";

void LogSDLError(ostream& os, const string &msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << endl;
    if (fatal)
    {
        SDL_Quit();
        exit(1);
    }
}

void initSDL(SDL_Window* &window, SDL_Renderer* &Renderer)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        LogSDLError (cout, "SDL_init", true);
    window = SDL_CreateWindow(Window_Title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr)
        LogSDLError(cout, "CreateWindow", true);
    Renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (Renderer == nullptr) LogSDLError(cout, "CreateWindow", true);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(Renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void quitSDL(SDL_Window* window, SDL_Renderer* Renderer)
{
    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true)
    {
        if (SDL_WaitEvent(&e) !=0 && (e.type == SDL_KEYDOWN || e.type == SDL_QUIT))
            return ;
        SDL_Delay(100);
    }
}

int main(int argc, char* argv[])
{
    SDL_Window* Window;
    SDL_Renderer* Renderer;
    initSDL(Window, Renderer);

    waitUntilKeyPressed();
    quitSDL(Window, Renderer);
    return 0;
}
