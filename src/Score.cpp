#include "Score.h"
#include <iostream>

Score::Score(SDL_Renderer* renderer)
   : renderer(renderer), playerScore(0), aiScore(0)
{
   scoreTexture = nullptr;
   if (TTF_Init() == -1)
   {
      std::cout << "TTF_Init FAILED. ERROR: " << TTF_GetError() << std::endl;
   }
   
   // Due to this project using CMAKE, we are running from "pong/out/build/x64-Debug/"
   // So we have to move three directories up in the hierarchy to go into res folder properly
   font = TTF_OpenFont("../../../res/fonts/arcade.ttf", 32);

   if (!font)
   {
      std::cout << "Failed to load font. ERROR: " << TTF_GetError() << std::endl;
      std::cout << "Current directory: " << SDL_GetBasePath() << std::endl;
      std::cout << "Trying to load font from: " << SDL_GetBasePath() << "res/fonts/arcade.ttf" << std::endl;

   }

   color = { 255, 0, 255, 255 }; // Neon pink color (R,G,B,A)

   updateTexture();
}

Score::~Score()
{
   SDL_DestroyTexture(scoreTexture);
   TTF_CloseFont(font);
   TTF_Quit();
}

void Score::increasePlayerScore()
{
   playerScore++;
   updateTexture();
}

void Score::increaseAIScore()
{
   aiScore++;
   updateTexture();
}

void Score::updateTexture()
{
   // Create score text
   std::string scoreText = std::to_string(playerScore) + "  |  " + std::to_string(aiScore);

   // Render text to surface
   SDL_Surface* textSurface = TTF_RenderText_Solid(font, scoreText.c_str(), color);
   if (!textSurface)
   {
      std::cout << "Failed to create text surface. ERROR: " << TTF_GetError() << std::endl;
      return;
   }

   // Convert to texture
   if (scoreTexture)
      SDL_DestroyTexture(scoreTexture);
   scoreTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
   SDL_FreeSurface(textSurface);

   // Set text position at the top-center
   scoreRect = { 1280 / 2 - 50, 20, 100, 50 }; // Adjust width later dynamically
}

void Score::render()
{
   SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreRect);
}
