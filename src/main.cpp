#include <SDL.h>
#include <stdio.h>

#include "engine.h"

int main(int argc, char* args[])
{
    Engine engine;

    if(engine.init())
    {
        while(engine.isRunning())
        {
            engine.update();
        }
    }

    engine.close();
	return 0;
}
