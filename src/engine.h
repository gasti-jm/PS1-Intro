#ifndef ENGINE_H_INCLUDED
#define ENGINE_H_INCLUDED

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdio.h>

#include "intro.h"

class Engine{
    private:
        bool prgRun;

        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_Event e;

        IntroPS intro;

    public:
        Engine();
        ~Engine();

        bool init();
        void close();
        void update();

        bool isRunning();
};

#endif
