# PlayStation 1 Intro

<div align = "center">
<img src="https://img.shields.io/badge/Build%20for-Windows_x64-43ca1f.svg?style=flat-square"/></img>
<img src="https://img.shields.io/badge/Tested%20on%20Linux-Not_yet-e92727.svg?style=flat-square"></img>

<img src="https://img.shields.io/badge/Made%20in-Code::Blocks-e92727.svg?style=flat-square"></img>
<img src="https://img.shields.io/badge/License-GNU%20General%20Public%20License%20v3.0-e98227.svg?style=flat-square"></img>

<p>
  Recreation PlayStation 1 intro in C++ under SDL2
</p>

![ps1](https://user-images.githubusercontent.com/82490615/222027622-50bbb651-9597-4868-97cf-ebb4099ae259.gif)
</div>
<br/>

# How to compile
<p>
  <a href="https://www.codeblocks.org/" target="_blank">Code::Blocks</a> is needed (although with <a href="https://visualstudio.microsoft.com/es/" target="_blank">Visual Studio 2022</a>, <a href="https://www.bloodshed.net/" target="_blank">DevC++</a> or any other IDE you can use it, if you know how to build the project). <br/><br/>
  You must also install and include the SDL2 library along with SDL_Image and SDL_Mixer. <br/>
  Steps for windows: <a href="http://lazyfoo.net/tutorials/SDL/01_hello_SDL/windows/index.php" target="_blank">Lazy Foo tutorials: Setting up SDL on Windows</a>
</p>

# How to change resolution:

<p>Go to the file intro.h and modify this code:</p>

<code>#define SCREEN_WIDTH 1360
#define SCREEN_HEIGHT 768
</code>

<b>Note:</b> Resolutions higher than 800x600 are recommended!

# How to enable/disable VSYNC
<p>Go to the engine.cpp file and in the "init" function you will see this code:</p>
<code>renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);</code>
<br/> <br/>
<p>
And change for: <br/>
<code>SDL_RENDERER_PRESENTVSYNC: Enable VSYNC</code> <br/>
<code>SDL_RENDERER_ACCELERATED: Disable VSYNC</code>
</p>

# How to enable/disable Fullscreen
<p>Go to the engine.cpp file and in the "init" function you will see this code:</p>
<code>window = SDL_CreateWindow("PLAYSTATION INTRO",
                              SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN);</code>
<br/> <br/>

<p>
Where it says "SDL_WINDOW_FULLSCREEN", change to: <br/>
<code>SDL_WINDOW_FULLSCREEN: Enable fullscreen</code> <br/>
<code>SDL_WINDOW_SHOWN: Window mode</code> <br/>
<code>SDL_WINDOW_BORDERLESS: Borderless window</code>
</p>

# Thanks to
Lazy Foo' Productions and their tutorials: http://lazyfoo.net/tutorials/SDL/index.php#Hello%20SDL
