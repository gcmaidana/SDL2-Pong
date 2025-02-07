#include "Ball.h"

Ball::Ball(int p_xPos, int p_yPos, int p_Width, int p_Height, int p_SpeedX, int p_SpeedY)
{
   rect = { p_xPos, p_yPos, p_Width, p_Height };
   velX = p_SpeedX;
   velY = p_SpeedY;
}

void Ball::update()
{
   rect.x += velX;
   rect.y += velY;

   // Bounce off top and bottom walls
   if (rect.y <= 0 || rect.y + rect.h >= 720)
      velY = -velY;
}

void Ball::render(SDL_Renderer* renderer)
{
   // SDL2 does not have a built-in function to draw a circle, but
   // we can use the midpoint circle algorithm to plot the points of a circle

   int centerX = rect.x + rect.w / 2;
   int centerY = rect.y + rect.h / 2;
   int radius = rect.w / 2; 

   for (int w = 0; w < radius * 2; w++)
   {
      for (int h = 0; h < radius * 2; h++)
      {
         int dx = radius - w; // Horizontal distance from center
         int dy = radius - h; // Vertical distance from center
         if ((dx * dx + dy * dy) <= (radius * radius))
         {
            SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // Yellow ball
            SDL_RenderDrawPoint(renderer, centerX + dx, centerY + dy);
         }
      }
   }
}

void Ball::reset(int p_xPos, int p_yPos)
{
   rect.x = p_xPos;
   rect.y = p_yPos;
   velX = -velX; 
}

