#ifndef endgame_H
#define endgame_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>



void destroy(SDL_Texture* gameoverTexture, SDL_Texture* scoreTexture, SDL_Texture* replayTexture,
             SDL_Texture* backTexture)
{
    SDL_DestroyTexture(gameoverTexture);
    SDL_DestroyTexture(scoreTexture);
    SDL_DestroyTexture(replayTexture);
    SDL_DestroyTexture(backTexture);
}


int showgameover(TTF_Font* font, int score) {
    SDL_Color textColor = {255, 0, 0};
    SDL_Color replayColor = {0, 255, 0};
    SDL_Color backColor = {255, 255, 0};

    string gameOverText = "GAME OVER!";
    string finalScoreText = "YOUR SCORE: " + std::to_string(score);
    string replayText = "PLAY AGAIN";
    string backText = "BACK";

    SDL_Surface* gameoverSurface = TTF_RenderText_Solid(font, gameOverText.c_str(), textColor);
    SDL_Surface* scoreSurface = TTF_RenderText_Solid(font, finalScoreText.c_str(), textColor);
    SDL_Surface* replaySurface = TTF_RenderText_Solid(font, replayText.c_str(), replayColor);
    SDL_Surface* backSurface = TTF_RenderText_Solid(font, backText.c_str(), backColor);

    if (!gameoverSurface || !scoreSurface || !replaySurface || !backSurface) return -1;

    SDL_Texture* gameoverTexture = SDL_CreateTextureFromSurface(gRenderer, gameoverSurface);
    SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(gRenderer, scoreSurface);
    SDL_Texture* replayTexture = SDL_CreateTextureFromSurface(gRenderer, replaySurface);
    SDL_Texture* backTexture = SDL_CreateTextureFromSurface(gRenderer, backSurface);

    playerLane = 1;
    playerX = playerLane * LANE_WIDTH + (LANE_WIDTH - PLAYER_SIZE) / 2;
    playerY = SCREEN_HEIGHT - PLAYER_SIZE - 10;
    SDL_Rect carRect = {playerX, playerY, PLAYER_SIZE, PLAYER_SIZE};


    SDL_Rect gameoverRect = {
        (SCREEN_WIDTH - gameoverSurface->w) / 2,
        SCREEN_HEIGHT / 2 - 100,
        gameoverSurface->w,
        gameoverSurface->h
    };
    SDL_Rect scoreRect = {
        (SCREEN_WIDTH - scoreSurface->w) / 2,
        SCREEN_HEIGHT / 2 - 50,
        scoreSurface->w,
        scoreSurface->h
    };
    SDL_Rect replayRect = {
        (SCREEN_WIDTH - replaySurface->w) / 2,
        SCREEN_HEIGHT / 2 + 20,
        replaySurface->w,
        replaySurface->h
    };
    SDL_Rect backRect = {
        (SCREEN_WIDTH - backSurface->w) / 2,
        SCREEN_HEIGHT / 2 + 70,
        backSurface->w,
        backSurface->h
    };
    SDL_Rect backgroundRect = {0, 0, 600, 680};

    SDL_FreeSurface(gameoverSurface);
    SDL_FreeSurface(scoreSurface);
    SDL_FreeSurface(replaySurface);
    SDL_FreeSurface(backSurface);

    while (true) {
        nentroi();

        SDL_RenderCopy(gRenderer, gameoverTexture, NULL, &gameoverRect);
        SDL_RenderCopy(gRenderer, scoreTexture, NULL, &scoreRect);
        SDL_RenderCopy(gRenderer, replayTexture, NULL, &replayRect);
        SDL_RenderCopy(gRenderer, backTexture, NULL, &backRect);
        SDL_RenderCopy(gRenderer, gCarTexture, NULL, &carRect);
        SDL_RenderPresent(gRenderer);

        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                destroy(gameoverTexture, scoreTexture, replayTexture, backTexture);
                return -1;
            }

            if (e.type == SDL_MOUSEBUTTONDOWN) {
                int x = e.button.x;
                int y = e.button.y;

                if (x >= replayRect.x && x <= replayRect.x + replayRect.w &&
                    y >= replayRect.y && y <= replayRect.y + replayRect.h) {
                    destroy(gameoverTexture, scoreTexture, replayTexture, backTexture);
                    return 1;
                }

                if (x >= backRect.x && x <= backRect.x + backRect.w &&
                    y >= backRect.y && y <= backRect.y + backRect.h) {
                    destroy(gameoverTexture, scoreTexture, replayTexture, backTexture);
                    return 0;
                }
            }
        }

        SDL_Delay(10);
    }
}

#endif // endgame_H
