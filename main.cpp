#include<iostream>
#include<vector>
#include<set>
#include<ctime>
#include<algorithm>
#include "variable.h"
#include "Asset.h"
#include "startgame.h"
#include "endgame.h"
#include "spawnobstacle.h"
#include "obstacle.h"
#include "backgroundtroi.h"

using namespace std;

bool init();
bool loadMedia();
void close();
SDL_Surface* loadSurface(std::string path);

SDL_Surface* gScreenSurface = NULL;

bool init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) return false;

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) return false;

    gWindow = SDL_CreateWindow("RACING ATTACK", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL) return false;

    else {
        gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
        if (gRenderer == NULL) return false;
        else {
            SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) & imgFlags)) return false;
        }
    }
    return true;
}

void close() {
    SDL_DestroyTexture(gCarTexture);
    gCarTexture = NULL;

    SDL_DestroyTexture(gBackgroundTexture);
    gBackgroundTexture = NULL;

    SDL_DestroyTexture(gObstacleTexture_one);
    gObstacleTexture_one = NULL;

    SDL_DestroyTexture(gObstacleTexture_two);
    gObstacleTexture_two = NULL;

    SDL_DestroyTexture(gObstacleTexture_three);
    gObstacleTexture_three = NULL;

    TTF_CloseFont(gFont);
    gFont = NULL;

    Mix_FreeMusic(gBackgroundMusic);
    gBackgroundMusic = NULL;

    Mix_FreeChunk(crashSound);
    crashSound = NULL;


    Mix_Quit();
    TTF_Quit();
    SDL_Quit();
    IMG_Quit();
    Mix_CloseAudio();
}

int main(int argc, char* args[]) {
    if (!init()) return 1;
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) return 0;
    if (TTF_Init() == -1) return 0;

    if (!loadMedia()) return 0;

    Mix_PlayMusic(gBackgroundMusic, -1);

    bool quit = false;

    while (!quit) {
        if (!showStartScreen()) break;

        bool inGame = true;
        while (inGame && !quit) {
            gameOver = false;
            score = 0;
            playerLane = 1;
            playerY = SCREEN_HEIGHT - PLAYER_SIZE - 10;
            obstacles.clear();
            updateMusicState();

            bgY1 = 0;
            bgY2 = -SCREEN_HEIGHT;

            SDL_Event e;
            Uint32 lastSpawnTime = SDL_GetTicks();
            const Uint32 spawnInterval = 1000;

            while (!quit && !gameOver) {
                while (SDL_PollEvent(&e)) {
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    } else if (e.type == SDL_KEYDOWN) {
                        switch (e.key.keysym.sym) {
                            case SDLK_LEFT:
                                if (playerLane > 0) playerLane--;
                                break;
                            case SDLK_RIGHT:
                                if (playerLane < NUM_LANES - 1) playerLane++;
                                break;
                            case SDLK_UP:
                                playerY -= PLAYER_SPEED;
                                if (playerY < 0) playerY = 0;
                                break;
                            case SDLK_DOWN:
                                playerY += PLAYER_SPEED;
                                if (playerY > SCREEN_HEIGHT - PLAYER_SIZE)
                                    playerY = SCREEN_HEIGHT - PLAYER_SIZE;
                                break;
                        }
                    }
                }

                Uint32 currentTime = SDL_GetTicks();
                if (currentTime - lastSpawnTime >= spawnInterval) {
                    int numToSpawn = 1;
                    if (score > 10) numToSpawn = 2;

                    spawnObstacle(numToSpawn);
                    lastSpawnTime = currentTime;
                }

                OBSTACLE();

                background_troi();

                SDL_Delay(0);
            }

            if (gameOver) {
                int result = showgameover(gFont, score);
                if (result == 1) continue;
                else if (result == 0) inGame = false;
                else quit = true;
            }
        }
    }

    close();
    return 0;
}
