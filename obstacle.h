#ifndef obstacle_H
#define obstacle_H
using namespace std;

int score = 0;
bool gameOver = false;


bool checkCollision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {
    return (x1 < x2 + w2 - 11 && x1 + w1 > x2 + 11 && y1 < y2 + h2 - 11 && y1 + h1 > y2 + 11);
}

void OBSTACLE() {
    for (auto& obs : obstacles) {
        if (obs.active) {
            obs.y += 3;
            if (obs.y > SCREEN_HEIGHT) obs.active = false;
            if (checkCollision(playerX, playerY, PLAYER_SIZE, PLAYER_SIZE,
                obs.x, obs.y, OBSTACLE_SIZE, OBSTACLE_SIZE)) {
                Mix_VolumeMusic(0);
                Mix_PlayChannel(-1, crashSound, 0);
                SDL_Delay(500);
                Mix_VolumeMusic(MIX_MAX_VOLUME);
                gameOver = true;
            }
        }
    }

    for (auto it = obstacles.begin(); it != obstacles.end(); ++it) {
        if (!it->active) {
            it = obstacles.erase(it); 
    }

    playerX = playerLane * LANE_WIDTH + 50;
    SDL_Rect carRect = {playerX, playerY, PLAYER_SIZE, PLAYER_SIZE};
    SDL_RenderCopy(gRenderer, gCarTexture, NULL, &carRect);

    for (const auto& obs : obstacles) {
        if (obs.active) {
            SDL_Rect obsRect = {obs.x, obs.y, OBSTACLE_SIZE, OBSTACLE_SIZE};
            if (obs.type == 0)
                SDL_RenderCopy(gRenderer, gObstacleTexture_one, NULL, &obsRect);
            else if (obs.type == 1)
                SDL_RenderCopy(gRenderer, gObstacleTexture_two, NULL, &obsRect);
            else
                SDL_RenderCopy(gRenderer, gObstacleTexture_three, NULL, &obsRect);
        }
    }

    for (auto& obs : obstacles) {
            if (obs.active && !obs.passed && obs.y > playerY + PLAYER_SIZE) {
                score++;
                obs.passed = true;
        }
    }

    for (auto& obs : obstacles) {
            if (obs.active && obs.y > SCREEN_HEIGHT) {
                obs.active = false;
        }
    }

    SDL_Color textColor = {255, 255, 255};
    string scoreText = "SCORE: " + to_string(score);
    SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, scoreText.c_str(), textColor);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
    SDL_Rect textRect = {10, 10, textSurface->w, textSurface->h};
    SDL_FreeSurface(textSurface);
    SDL_RenderCopy(gRenderer, textTexture, NULL, &textRect);
    SDL_DestroyTexture(textTexture);

    SDL_RenderPresent(gRenderer);
    SDL_Delay(1);
}
#endif
