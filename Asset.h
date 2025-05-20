#ifndef ASSET_H
#define ASSET_H

#include <SDL_image.h>
#include <string>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
using namespace std;


SDL_Texture* loadTexture(string path) {
    SDL_Texture* newTexture = NULL;

    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL ) return NULL;
    else {

        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if( newTexture == NULL ) return NULL;

        SDL_FreeSurface( loadedSurface );
    }

    return newTexture;
}

TTF_Font* loadFont(const char* path, int size) {
    TTF_Font* gFont = TTF_OpenFont( path, size );
    if (gFont == nullptr) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
                        SDL_LOG_PRIORITY_ERROR,
                        "Load font %s", TTF_GetError());
    }
    return gFont;
}

Mix_Music *loadMusic(const char* path)
    {
        Mix_Music *gMusic = Mix_LoadMUS(path);
        if (gMusic == nullptr) {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
                           SDL_LOG_PRIORITY_ERROR,
                "Could not load music! SDL_mixer Error: %s", Mix_GetError());
        }
        return gMusic;
    }


Mix_Chunk* loadSound(const char* path) {
        Mix_Chunk* gChunk = Mix_LoadWAV(path);
        if (gChunk == nullptr) {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
                           SDL_LOG_PRIORITY_ERROR,
               "Could not load sound! SDL_mixer Error: %s", Mix_GetError());
        }
        return gChunk;
    }



bool loadMedia() {
    gBackgroundTexture = loadTexture("background1.bmp");
    if (gBackgroundTexture == NULL) return false;

    gCarTexture = loadTexture("car1.png");
    if (gCarTexture == NULL) return false;

    gObstacleTexture_one = loadTexture("car2.png");
    if (gObstacleTexture_one == NULL) return false;

    gObstacleTexture_three = loadTexture("car3.png");
    if (gObstacleTexture_three == NULL) return false;

    gObstacleTexture_two = loadTexture("car4.png");
    if (gObstacleTexture_two == NULL) return false;

    gFont = loadFont("Inter_28pt-BoldItalic.ttf", 24);
    if (gFont == NULL) return false;

    gBackgroundMusic = loadMusic("music.mp3");
    if (gBackgroundMusic == NULL) return false;

    crashSound = loadSound("music1.wav");
    if(crashSound == NULL) return false;

    return true;
}
#endif

