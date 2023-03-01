#include "engine.h"

/**
 * Constructor
 */
Engine::Engine()
{
    window = NULL;
    renderer = NULL;
    this->prgRun = true; // always
}

/**
 * Desctructor
 */
Engine::~Engine()
{

}

/**
 * Initializate engine and SDL Systems
 */
bool Engine::init()
{
    //Initialize SDL
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("SDL2 could not initialize! Error code: %s\n", SDL_GetError());
		return false;
	}

	//Set texture filtering to linear
    if(!SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1"))
    {
        printf("Warning: Linear texture filtering not enabled!");
    }

    //Create window
    window = SDL_CreateWindow("PLAYSTATION INTRO",
                              SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN);

    if(window == NULL)
    {
        printf("Window could not be created! Error code: %s\n", SDL_GetError());
        return false;
    }

    //Create renderer for window
    //SDL_RENDERER_PRESENTVSYNC
    //SDL_RENDERER_ACCELERATED
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
    if(renderer == NULL)
    {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    //Initialize renderer color
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

    //Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if(!(IMG_Init(imgFlags) & imgFlags))
    {
        printf("SDL2 IMAGE could not initialize! Error code: %s\n", IMG_GetError());
        return false;
    }

     //Initialize SDL Mixer
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        printf( "SDL Mixer could not initialize! Error code: %s\n", Mix_GetError());
        return false;
    }

    if(!intro.loadMedia(renderer))
    {
        return false;
    }

    SDL_ShowCursor(SDL_DISABLE);

    // init ok!
	return true;
}

/**
 * Update screen
 */
void Engine::update()
{
    if(SDL_PollEvent(&e))
    {
        if(e.type == SDL_QUIT)
        {
            prgRun = false;
        }
        else if(e.type == SDL_KEYDOWN)
        {
            if (e.key.keysym.sym == SDLK_ESCAPE) prgRun = false;
        }
    }

    //Clear screen
    SDL_SetRenderDrawColor(renderer, intro.getBackground_R(),
                                     intro.getBackground_G(),
                                     intro.getBackground_B(), 255);

    SDL_RenderClear(renderer);

    intro.update(renderer);

    // update screen
    SDL_RenderPresent(renderer);

    if(intro.getEnd()) prgRun = false;
}

/**
 * Closing engine and SDL Systems
 */
void Engine::close()
{
    //Destroy window and renderer
    SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = NULL;
	renderer = NULL;

	//Quit SDL subsystems
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

/**
 * For main loop.
 */
bool Engine::isRunning()
{
    return prgRun;
}

