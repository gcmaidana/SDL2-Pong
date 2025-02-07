/*
*  @author: Gean Maidana
*  This is a simple game of Pong meant to be played by 1 player against an enemy AI
*  This game is built using SDL2 and C++
*/


// SDL_main.h is included automatically from SDL.h and redefines main().
// Defining SDL_MAIN_HANDLED before including SDL.h prevents SDL from modifying main().
// Alternatively, if SDL has already redefined main(), use "#undef main" after including SDL.h.
#define SDL_MAIN_HANDLED 

#include <SDL2/SDL.h>
#include <iostream>

#include "RenderWindow.h"
#include "Ball.h"
#include "Paddle.h"
#include "Score.h"

int main(int argc, char* args[])
{
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
		std::cout << "SDL_Init has FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;
   
   const int FPS = 60;
   const int frameDelay = 250 / FPS;
   Uint32 frameStart;

   int frameTime;
	RenderWindow window("Pong", 1280, 720);

   Paddle player(50, 300, 20, 100, 2);
   Paddle opponent(1210, 300, 20, 100, 2, 100.0f);
	Ball ball(640, 360, 15, 15, 2, 2);
   Score score(window.getRenderer());

	bool gameRunning = true;
	SDL_Event event;

	while (gameRunning)
	{
      frameStart = SDL_GetTicks();

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				gameRunning = false;
         if (event.type == SDL_KEYDOWN)
         { 
            if (event.key.keysym.sym == SDLK_ESCAPE)
               gameRunning = false; // Game exits if ESC key is pressed
         }
		}

      // Player can move up and down using either W and S or the up and down arrows on the keyboard
      const Uint8* keystate = SDL_GetKeyboardState(NULL);
      if (keystate[SDL_SCANCODE_W])
         player.moveUp();
      if (keystate[SDL_SCANCODE_S])
         player.moveDown();
      if (keystate[SDL_SCANCODE_UP])
         player.moveUp();
      if (keystate[SDL_SCANCODE_DOWN])
         player.moveDown();

      // Update the ball movement and update enemy AI paddle to follow the ball
      ball.update();
      opponent.followBall(ball);

      // Collision with paddles
      if (SDL_HasIntersection(&ball.rect, &player.rect) || SDL_HasIntersection(&ball.rect, &opponent.rect))
         ball.velX = -ball.velX;

      // Reset ball if it goes out of bounds
      if (ball.rect.x < 0 || ball.rect.x > 1280)
      {
         if (ball.rect.x < 0)
            score.increaseAIScore();
         else if (ball.rect.x > 1280)
            score.increasePlayerScore();
         ball.reset(640, 360);
      }
         
      // Rendering
      window.clear();
      player.render(window.getRenderer());
      opponent.render(window.getRenderer());
      ball.render(window.getRenderer());
      score.render();
      window.display();

      // This frame time stuff is to prevent the game from rendering too fast  
      // as it can cause problems with things moving too fast
      frameTime = SDL_GetTicks() - frameStart;
      if (frameDelay > frameTime)
      {
         SDL_Delay(frameDelay - frameTime);
      }
	}

	window.cleanUp();
	SDL_Quit();

	return 0;
}