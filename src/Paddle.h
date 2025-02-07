#pragma once
#include <SDL2/SDL.h>
#include <algorithm>

#include "Ball.h"


class Paddle
{
public:
   SDL_Rect rect;
   int speed;
   float reactionDelay;
   float lastBallY;
   Uint32 lastUpdateTime;

   Paddle(int p_xPos, int p_yPos, int p_Width, int p_Height, int p_Speed, float p_Delay = 0);

   void followBall(const Ball& ball);
   void moveUp();
   void moveDown();
   void render(SDL_Renderer* renderer);
};

