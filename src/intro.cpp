#include "intro.h"

IntroPS::IntroPS()
{
    background_r = 0;
    background_g = 0;
    background_b = 0;

    beginTime = SDL_GetTicks();
    endTime = 0;
    deltaTime = 0;

    endIntro = false;

    sIntro = NULL;
    effect = INIT_DELAY;
}

IntroPS::~IntroPS()
{
    bigDiamond.free();
    smallDiamond.free();
    psLogo.free();
    txtSony.free();
    txtCE.free();
    txtPlayStation.free();
    txtLicense.free();

    Mix_FreeChunk( sIntro );
    sIntro = NULL;
}

bool IntroPS::loadMedia(SDL_Renderer*& renderer)
{
    //Load sound effects
    sIntro = Mix_LoadWAV("res/sound/intro.wav");
    if(sIntro == NULL)
    {
        return false;
        //printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
    }

    if(!bigDiamond.loadFromFile("res/graphics/rlogo1.png", renderer))
	{
		printf( "Failed to load big diamond texture!\n" );
		return false;
	}

	if(!smallDiamond.loadFromFile("res/graphics/rlogo2.png", renderer))
	{
		printf( "Failed to load small diamond texture!\n" );
		return false;
	}

	if(!psLogo.loadFromFile("res/graphics/pslogo.png", renderer))
	{
	    printf( "Failed to load texture Playstation logo!\n" );
	    return false;
	}

	if(!txtSony.loadFromFile("res/graphics/sony.png", renderer))
	{
	    printf( "Failed to load texture Sony text!\n" );
	    return false;
	}

	if(!txtCE.loadFromFile("res/graphics/ce.png", renderer))
	{
	    printf( "Failed to load texture Computer Entertainment text!\n" );
	    return false;
	}

	if(!txtPlayStation.loadFromFile("res/graphics/playstation.png", renderer))
	{
	    printf( "Failed to load texture PlayStation text!\n" );
	    return false;
	}

	if(!txtLicense.loadFromFile("res/graphics/license.png", renderer))
	{
	    printf( "Failed to load texture License text!\n" );
	    return false;
	}

	psLogo.setBlendMode(SDL_BLENDMODE_BLEND);
	psLogo.setAlpha(0);

	txtSony.setBlendMode(SDL_BLENDMODE_BLEND);
	txtSony.setAlpha(0);

	txtCE.setBlendMode(SDL_BLENDMODE_BLEND);
	txtCE.setAlpha(0);

	txtPlayStation.setBlendMode(SDL_BLENDMODE_BLEND);
	txtPlayStation.setAlpha(0);

	//smallDiamond.setWidth(smallDiamond.getWidth() * 2);
	//smallDiamond.setHeight(smallDiamond.getHeight() * 2);

    return true;
}

void IntroPS::playSound()
{
    // If I ask for it in this state of effect, I prevent the sound from being reproduced more than once...
    if(effect == INIT_DELAY)
    {
        Mix_PlayChannel( -1, sIntro, 0 );
    }
}

void IntroPS::checkTimerEffects()
{
    // Timers who control the change of effects according to time.
    static Uint32 beforeIntroDelay = SDL_GetTicks() + TIME_INTRO_DELAY;
    static Uint32 endIntroTime = SDL_GetTicks() + TIME_END_INTRO + TIME_INTRO_DELAY;
    static Uint32 backScreenAgain = SDL_GetTicks() + TIME_EFFECT_BLACK + TIME_INTRO_DELAY;


    if(SDL_GetTicks() >= beforeIntroDelay && effect == INIT_DELAY)
    {
        playSound(); // call me once.
        effect = EFFECT_BACKGROUND_WHITE; // change to the blank screen effect and do not call the "PlaySound" function again.
    }

    if(SDL_GetTicks() >= backScreenAgain && effect == EFFECT_SONY_LOGO)
    {
        effect = EFFECT_BACKGROUND_BLACK; // moment for the black screen.
    }

    // After finishing the sound of the intro and a few seconds of silence, we close our program.
    if(SDL_GetTicks() >= endIntroTime)
    {
        endIntro = true;
    }
}

void IntroPS::update(SDL_Renderer*& renderer)
{
    endTime = SDL_GetTicks();
    deltaTime = (endTime - beginTime) / 1000.f;
    beginTime = endTime;

    checkTimerEffects();

    switch(effect)
    {
        case EFFECT_BACKGROUND_WHITE: effectWhite(); break;
        case EFFECT_SONY_LOGO:
            drawLogoSony(renderer);
            break;
        case EFFECT_BACKGROUND_BLACK: effectBlack(); break;
        case EFFECT_DRAW_PLAYSTATION_LOGO: drawPsLogo(renderer); break;
    }
}

void IntroPS::drawLogoSony(SDL_Renderer*& renderer)
{
    // for big diamond sony logo...
    int posBigX = (SCREEN_WIDTH / 2) - (bigDiamond.getWidth() / 2);
    int posBigY = (SCREEN_HEIGHT / 2) - (bigDiamond.getHeight() / 2);
    bigDiamond.render(posBigX, posBigY, renderer);

    // sony text
    int posSonyTextX = (SCREEN_WIDTH / 2) - (txtSony.getWidth() / 2);
    int posSonyTextY = posBigY - txtSony.getHeight() - 20;
    txtSony.render(posSonyTextX, posSonyTextY, renderer);

    // computer entertainment text
    int posCETextX = (SCREEN_WIDTH / 2) - (txtCE.getWidth() / 2) + 20;
    int posCETextY = (posBigY + bigDiamond.getHeight()) + 20;
    txtCE.render(posCETextX, posCETextY, renderer);

    effectSmallDiamonds(renderer, posBigX, posBigY);
}

/**
 * Resize the size of the rhombos and centralize them in the big rhombus
 * @params: Engine rendering, position X and Y of the big rhombus (logo sony).
 * @note: All values is hardcoded about resolution and position.
 */
void IntroPS::effectSmallDiamonds(SDL_Renderer*& renderer, int posBigX, int posBigY)
{
    // size and pos in end effect. (NOTE: THIS IS HARDCODED!)
    static const int smallWidth = (smallDiamond.getWidth() / 2) - (smallDiamond.getWidth() * 0.15f);
    static const int smallHeight = (smallDiamond.getHeight() / 2) - (smallDiamond.getHeight() * 0.15f);

    static const int posSmallX_END = posBigX + (bigDiamond.getWidth() / 2);
    static const int posSmallY_END = posBigY + bigDiamond.getHeight() / 2;

    static const int posSmallX_END_LEFT = posBigX + (bigDiamond.getWidth() / 2) - smallWidth;
    static const int posSmallY_END_LEFT = posBigY + (bigDiamond.getHeight() / 2) - smallHeight;

    // initial value
    static float posX_left = posBigX;
    static float posY_left = posBigY + (bigDiamond.getHeight() / 2) - smallDiamond.getHeight() / 2;

    static float posX_right = posBigX + bigDiamond.getWidth() - smallDiamond.getWidth();
    static float posY_right = posBigY + (bigDiamond.getHeight() / 2) - smallDiamond.getHeight() / 2;

    //////////////////////////////////////////////////////

    // arrow left

    if(posX_left < posSmallX_END_LEFT)
    {
        posX_left += 130 * deltaTime;
    }
    else
    {
        posX_left = posSmallX_END_LEFT;
    }

    if(posY_left < posSmallY_END_LEFT)
    {
        posY_left += 60 * deltaTime;
    }
    else
    {
        posY_left = posSmallY_END_LEFT;
    }


    ///////////////////////////////////////////////////////


    // arrow right

    if(posX_right > posSmallX_END)
    {
        posX_right -= 60 * deltaTime;
    }
    else
    {
        posX_right = posSmallX_END;
    }

    if(posY_right < posSmallY_END)
    {
        posY_right += 200 * deltaTime;
    }
    else
    {
        posY_right = posSmallY_END;
    }


    ///////////////////////////////////////////////////////

    static float effectWidth = smallDiamond.getWidth();
    static float effectHeight = smallDiamond.getHeight();

    if(effectWidth > smallWidth) effectWidth -= 130 * deltaTime;
    if(effectHeight > smallHeight) effectHeight -= 260 * deltaTime;

    smallDiamond.setWidth((int)effectWidth);
    smallDiamond.setHeight((int)effectHeight);

    if(smallDiamond.getWidth() < smallWidth && smallDiamond.getHeight() < smallHeight)
    {
        smallDiamond.setHeight(smallHeight);
        smallDiamond.setWidth(smallWidth);
        effectTexts();
    }


    smallDiamond.render(posX_right,
                        posY_right, renderer);

    smallDiamond.render(posX_left,
                        posY_left,
                        renderer, NULL, SDL_FLIP_HORIZONTAL);

}

/**
 * Transparency in blue letters on the white screen.
 * @params: none
 */
void IntroPS::effectTexts()
{
    static float alpha = 0;
    if (alpha < 255) alpha += 255 * deltaTime;
    if (alpha > 255) alpha = 255;

    txtSony.setAlpha((Uint8) alpha);
    txtCE.setAlpha((Uint8) alpha);
}

/**
 * Drawing of the PlayStation logo + transparency effect.
 * @params: Engine rendering
 */
void IntroPS::drawPsLogo(SDL_Renderer*& renderer)
{
    int posLogoX = (SCREEN_WIDTH / 2) - (psLogo.getWidth() / 2);
    int posLogoY = (SCREEN_HEIGHT / 2) - psLogo.getHeight();


    static float alpha = 0;
    if (alpha < 255) alpha += 300 * deltaTime;

    if (alpha >= 255)
    {
        alpha = 255;
        drawPSText(renderer);
    }

    psLogo.setAlpha((Uint8) alpha);
    psLogo.render(posLogoX, posLogoY, renderer);
}

void IntroPS::drawPSText(SDL_Renderer*& renderer)
{
    int posTextX = (SCREEN_WIDTH / 2) - (txtPlayStation.getWidth() / 2) + 12;
    int posTextY = (SCREEN_HEIGHT / 2) + (txtPlayStation.getHeight() * 0.25f);

    static float alpha = 0;
    if (alpha < 255) alpha += 400 * deltaTime;
    if (alpha >= 255)
    {
        alpha = 255;
    }

    txtPlayStation.setAlpha((Uint8) alpha);
    drawLicense(renderer);
    txtPlayStation.render(posTextX, posTextY, renderer);

}

void IntroPS::drawLicense(SDL_Renderer*& renderer)
{
    int posTextX = (SCREEN_WIDTH / 2) - (txtLicense.getWidth() / 2);
    int posTextY = (SCREEN_HEIGHT / 2) + txtLicense.getHeight();

    txtLicense.render(posTextX, posTextY, renderer);
}

void IntroPS::effectWhite()
{
    static float newValue = 0;
    if (newValue < 255) newValue += 200 * deltaTime;

    if (newValue > 255)
    {
        newValue = 255;
        effect = EFFECT_SONY_LOGO;
    }

    background_r = (Uint8) newValue;
    background_g = (Uint8) newValue;
    background_b = (Uint8) newValue;
}

void IntroPS::effectBlack()
{
    static float newValue = 255;
    if (newValue > 0) newValue -= 255 * deltaTime;

    if (newValue < 0)
    {
        newValue = 0;
        effect = EFFECT_DRAW_PLAYSTATION_LOGO;
    }

    background_r = (Uint8) newValue;
    background_g = (Uint8) newValue;
    background_b = (Uint8) newValue;
}

Uint8 IntroPS::getBackground_R()
{
    return background_r;
}

Uint8 IntroPS::getBackground_G()
{
    return background_g;
}

Uint8 IntroPS::getBackground_B()
{
    return background_b;
}

bool IntroPS::getEnd()
{
    return endIntro;
}
