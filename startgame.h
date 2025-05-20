#ifndef startgame_H
#define startgame_H
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

int bgY1 = 0;
int bgY2 = -SCREEN_HEIGHT;
const int BG_SCROLL_SPEED = 3;

int playerX = 64;
int playerY = 128;

void nentroi() {
    bgY1 += BG_SCROLL_SPEED;
    bgY2 += BG_SCROLL_SPEED;

    if (bgY1 >= SCREEN_HEIGHT) bgY1 = bgY2 - SCREEN_HEIGHT;
    if (bgY2 >= SCREEN_HEIGHT) bgY2 = bgY1 - SCREEN_HEIGHT;

    SDL_RenderClear(gRenderer);
    SDL_Rect bgRect1 = {0, bgY1, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_Rect bgRect2 = {0, bgY2, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_RenderCopy(gRenderer, gBackgroundTexture, NULL, &bgRect1);
    SDL_RenderCopy(gRenderer, gBackgroundTexture, NULL, &bgRect2);
}

void updateMusicState() {
    if (isMusic) {
        Mix_ResumeMusic();
    } else {
        Mix_PauseMusic();
    }
}

bool showStartScreen() {
    SDL_Texture* namegameTexture = loadTexture("racing_attack.png");
    if(!namegameTexture) return false;


    SDL_Texture* playButtonTexture = loadTexture("play_button.png");
    if (!playButtonTexture) return false;

    SDL_Texture* exitButtonTexture = loadTexture("exit_button.png");
    if (!exitButtonTexture) {
        SDL_DestroyTexture(playButtonTexture);
        return false;
    }

    playerX = playerLane * LANE_WIDTH + (LANE_WIDTH - PLAYER_SIZE) / 2;
    playerY = SCREEN_HEIGHT - PLAYER_SIZE - 10;
    SDL_Rect carRect = {playerX, playerY, PLAYER_SIZE, PLAYER_SIZE};

    SDL_Texture* volum_onTexture = loadTexture("volum_button.png");
    if(!volum_onTexture) return false;

    SDL_Texture* volum_offTexture = loadTexture("off_volum_button.png");
    if(!volum_offTexture) return false;

    SDL_Rect namegameRect = {75, 5, 450, 400};
    SDL_Rect playButtonRect = { 177, 250, 250, 250 };
    SDL_Rect exitButtonRect = { 180, 350, 250, 250 };
    SDL_Rect volum_onRect = {550, 0, 50, 50};
    SDL_Rect volum_offRect = {550, 0, 50, 50};

    SDL_Event e;
    while (true) {
        nentroi();

        SDL_RenderCopy(gRenderer, playButtonTexture, NULL, &playButtonRect);
        SDL_RenderCopy(gRenderer, exitButtonTexture, NULL, &exitButtonRect);
        SDL_RenderCopy(gRenderer, namegameTexture, NULL, &namegameRect);
        SDL_RenderCopy(gRenderer, gCarTexture, NULL, &carRect);
        if(isMusic) {
            SDL_RenderCopy(gRenderer, volum_onTexture, NULL, &volum_onRect);
        } else {
            SDL_RenderCopy(gRenderer, volum_offTexture, NULL, &volum_offRect);
        }
        SDL_RenderPresent(gRenderer);

        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                SDL_DestroyTexture(playButtonTexture);
                SDL_DestroyTexture(exitButtonTexture);
                SDL_DestroyTexture(namegameTexture);
                SDL_DestroyTexture(volum_onTexture);
                SDL_DestroyTexture(volum_offTexture);
                exit(0);
            }

            if (e.type == SDL_MOUSEBUTTONDOWN) {
                int x = e.button.x;
                int y = e.button.y;

                if (x >= 210 && x <= 395 &&
                    y >= 315 && y <= 400) {
                    SDL_DestroyTexture(playButtonTexture);
                    SDL_DestroyTexture(exitButtonTexture);
                    SDL_DestroyTexture(namegameTexture);
                    SDL_DestroyTexture(volum_onTexture);
                    SDL_DestroyTexture(volum_offTexture);
                    return true; // bắt đầu game
                }

                if (x >= 225 && x <= 375 &&
                    y >= 420 && y <= 495) {
                    SDL_DestroyTexture(playButtonTexture);
                    SDL_DestroyTexture(exitButtonTexture);
                    SDL_DestroyTexture(volum_onTexture);
                    SDL_DestroyTexture(volum_offTexture);
                    exit(0);
                }

                if(x >= 565 && x <= 590 && y >= 10 && y <= 25) {
                    if(isMusic) {
                        isMusic = false;
                        Mix_PauseMusic();
                    } else {
                        isMusic = true;
                        Mix_ResumeMusic();
                    }
                }
            }
        }

        SDL_Delay(10);
    }
}

#endif // startgame_H
