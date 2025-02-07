#include "Paddle.h"
#include "Ball.h"

Paddle::Paddle(int p_xPos, int p_yPos, int p_Width, int p_Height, int p_Speed, float p_Delay)
{
   rect = { p_xPos, p_yPos, p_Width, p_Height };
   speed = p_Speed;
   reactionDelay = p_Delay;
   lastBallY = 0;
   lastUpdateTime = SDL_GetTicks();
}

void Paddle::moveUp()
{
   if (rect.y > 0)
      rect.y -= speed;
}

void Paddle::moveDown()
{
   if (rect.y + rect.h < 720)
      rect.y += speed;
}

void Paddle::render(SDL_Renderer* renderer)
{
   SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White paddle
   SDL_RenderFillRect(renderer, &rect);
}

// This function for the AI opponent paddle to follow the ball
// Tried implementing a few things like delay and randomness to make the
// AI behave more "human-like"
// It's not perfect, but it's better than locking onto the ball and hitting every
// incoming ball which can lead to stalemates
void Paddle::followBall(const Ball& ball)
{
   Uint32 currentTime = SDL_GetTicks();
   float paddleCenter = rect.y + (rect.h / 2);
   float ballCenter = ball.rect.y + (ball.rect.h / 2);

   // Randomly adjust reaction delay slightly for inconsistency
   int randomReactionAdjustment = (rand() % 15) - 7; // +/- 7ms variation
   int actualReactionDelay = reactionDelay + randomReactionAdjustment;

   // Only update target position after reaction delay
   if (currentTime - lastUpdateTime > actualReactionDelay)
   {
      lastBallY = ballCenter;
      lastUpdateTime = currentTime;
   }

   float predictedY = lastBallY;
   if (ball.velX > 0)  
   {
      float predictionNoise = (rand() % 15) - 7; 
      predictedY += (ball.velY * 0.85f) + predictionNoise;
   }

   // Add a small chance for AI to move slightly wrong and misplay
   if (rand() % 5 == 0)
   {
      predictedY += (rand() % 50) - 25;  // moves slightly off-target
   }

   // "lazy zone" where the paddle moves slower
   float distance = std::abs(paddleCenter - predictedY);
   int currentSpeed = speed;

   if (distance < 50)
   {
      currentSpeed = speed / 1.5f; // Slower movement close to target
   }

   // Move paddle based on adjusted predicted position
   if (predictedY > paddleCenter + 10)
   {
      rect.y += currentSpeed;
   }
   else if (predictedY < paddleCenter - 10)
   {
      rect.y -= currentSpeed;
   }

   // Ensure paddle stays within screen bounds
   if (rect.y < 0) rect.y = 0;
   if (rect.y + rect.h > 720) rect.y = 720 - rect.h;
}
