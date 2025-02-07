#include "RenderWindow.h"

RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h)
	:window(NULL), renderer(NULL)
{
	window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);

	if (window == NULL)
	{
		std::cout << "Window failed to init. Error: " << SDL_GetError() << std::endl;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (renderer == NULL)
	{
		std::cout << "Renderer failed to create. Error: " << SDL_GetError() << std::endl;
	}
}

SDL_Texture* RenderWindow::loadTexture(int r, int g, int b)
{
	SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 128, 128);
	SDL_SetRenderTarget(renderer, texture);
	SDL_SetRenderDrawColor(renderer, r, g, b, 255);
	SDL_RenderClear(renderer);
	SDL_SetRenderTarget(renderer, NULL);
	return texture;
}


void RenderWindow::cleanUp()
{
	SDL_DestroyWindow(window);
}

void RenderWindow::clear()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
}

void RenderWindow::render(SDL_Texture* p_tex)
{
	SDL_RenderCopy(renderer, p_tex, NULL, NULL);
}

void RenderWindow::display()
{
	SDL_RenderPresent(renderer);
}