#pragma once
#include <SDL2/SDL.h>

class Ball
{
public:
   SDL_Rect rect;
   int velX, velY;

   Ball(int p_xPos, int p_yPos, int p_Width, int p_Height, int p_SpeedX, int p_SpeedY);

   void update();
   void render(SDL_Renderer* renderer);
   void reset(int p_xPos, int p_yPos);
};
