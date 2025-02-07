#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class Score
{
private:
   SDL_Renderer* renderer;
   TTF_Font* font;
   SDL_Color color;
   int playerScore;
   int aiScore;
   SDL_Texture* scoreTexture;
   SDL_Rect scoreRect;

public:
   Score(SDL_Renderer* renderer);
   ~Score();

   void increasePlayerScore();
   void increaseAIScore();
   void updateTexture();
   void render();
};


