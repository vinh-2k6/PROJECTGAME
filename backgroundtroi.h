#ifndef backgroundtroi_H
#define backgroundtroi_H

void background_troi() {

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

#endif // backgroundtroi_H
