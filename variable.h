#ifndef variable_H
#define variable_H

#include <SDL_image.h>
#include <string>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

const int PLAYER_SIZE = 100;
const int OBSTACLE_SIZE = 100;
const int PLAYER_SPEED = 20;
const int NUM_LANES = 3;
const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 680;
const int LANE_WIDTH = 200;

bool isMusic = true;

int playerLane = 1;

SDL_Texture* gCarTexture = NULL;
SDL_Texture* gBackgroundTexture = NULL;
SDL_Texture* gObstacleTexture_one = NULL;
SDL_Texture* gObstacleTexture_two = NULL;
SDL_Texture* gObstacleTexture_three = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Window* gWindow = NULL;
TTF_Font* gFont = NULL;
Mix_Music* gBackgroundMusic = NULL;
Mix_Chunk* crashSound = NULL;

#endif // variable_H
