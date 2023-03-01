#ifndef TEXTURE_H_INCLUDED
#define TEXTURE_H_INCLUDED

#include <SDL.h>
#include <SDL_image.h>
#include <string>

class Texture
{
	public:
		Texture();
		~Texture();

		bool loadFromFile(std::string, SDL_Renderer*&);
		void free();

		void setColor(Uint8, Uint8, Uint8);
		void setBlendMode(SDL_BlendMode);
		void setAlpha(Uint8);
		void render(int x, int y, SDL_Renderer*& renderer, SDL_Rect* clip = NULL, SDL_RendererFlip = SDL_FLIP_NONE);

		int getWidth();
		int getHeight();

		void setWidth(int);
		void setHeight(int);

	private:
		SDL_Texture* mTexture;
		int mWidth;
		int mHeight;
};

#endif
