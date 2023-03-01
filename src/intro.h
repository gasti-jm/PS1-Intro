#ifndef INTRO_H_INCLUDED
#define INTRO_H_INCLUDED

#define SCREEN_WIDTH 1360
#define SCREEN_HEIGHT 768

#include <SDL.h>
#include <SDL_mixer.h>
#include "texture.h"

enum effects
{
    INIT_DELAY,
    EFFECT_BACKGROUND_WHITE,
    EFFECT_SONY_LOGO,
    EFFECT_BACKGROUND_BLACK,
    EFFECT_DRAW_PLAYSTATION_LOGO
};

class IntroPS
{
    private:
        bool endIntro;

        // background color on screen.
        Uint8 background_r;
        Uint8 background_g;
        Uint8 background_b;

        Texture bigDiamond;
        Texture smallDiamond;
        Texture psLogo;

        //Rendered texture
        Texture txtSony;
        Texture txtCE;
        Texture txtPlayStation;
        Texture txtLicense;

        //intro sound
        Mix_Chunk* sIntro;

        int effect;

        // Timers!
        float beginTime;
		float endTime;
		float deltaTime;

		const int TIME_INTRO_DELAY = 2000;
        const int TIME_EFFECT_BLACK = 6200; // starting black effect.
        const int TIME_END_INTRO = 20000; // In 20 seconds the intro will be over.

    public:
        IntroPS();
        ~IntroPS();

        void update(SDL_Renderer*&);

        void checkTimerEffects();

        bool loadMedia(SDL_Renderer*&);
        bool loadFonts(SDL_Renderer*&);
        void playSound();

        void effectWhite();
        void effectBlack();
        void effectSmallDiamonds(SDL_Renderer*&, int, int);
        void effectTexts();

        void drawLogoSony(SDL_Renderer*&);
        void drawPsLogo(SDL_Renderer*&);
        void drawPSText(SDL_Renderer*&);
        void drawLicense(SDL_Renderer*&);

        // for renderer.
        Uint8 getBackground_R();
        Uint8 getBackground_G();
        Uint8 getBackground_B();

        // to end the program..
        bool getEnd();
};

#endif
