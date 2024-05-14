#include "Score.h"
#include <iostream>

Score::Score(SDL_Color color, int level, int score, int timeClick, int x, int y, std::string noti) {
    this->color = color;
    this->level = level;
    this->score = score;
    this->timeClick = timeClick;
    this->noti = noti;
    this->rect = { 0, 0, x, y };
    this->rectScore = { 0, x, x, y - x };
    this->font = TTF_OpenFont("image/game.ttf", 80);

}

Score::~Score() {
    TTF_CloseFont(font);
}

void Score::render(SDL_Renderer* renderer) {
    SDL_Surface* surface = TTF_RenderText_Solid(font, noti.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
    SDL_DestroyTexture(texture);
}

SDL_Rect Score::getRect() const {
    return rect;
}

SDL_Rect Score::getRectScore() {
    return rectScore;
}

std::string Score::getNoti() {
    return noti;
}
