#pragma once
#include <SDL2/SDL.h>
#include <iostream>

class RenderWindow
{
public:
	RenderWindow(const char* p_title, int p_w, int p_h);
	SDL_Texture* RenderWindow::loadTexture(int r, int g, int b);

	void cleanUp();
	void clear();
	void render(SDL_Texture* p_tex);
	void display();
	SDL_Renderer* getRenderer() { return renderer; }
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
};