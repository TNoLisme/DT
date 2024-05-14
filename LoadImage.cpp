#include "LoadImage.h"
#include <iostream>

Image::Image() : mTexture(nullptr), mWidth(0), mHeight(0) {}
Image::~Image() {
    free();
}

Image::Image(SDL_Texture* tex, int x, int y, int w, int h) : mTexture(tex) {
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
}

int Image::getWidth() const {
    return mWidth;
}

int Image::getHeight() const {
    return mHeight;
}

SDL_Rect Image::getRect() const {
    return rect;
}

bool Image::loadTexture(const std::string& path, SDL_Renderer* renderer) {
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr) {
        std::cerr << "Unable to load image " << path << "! SDL_image Error: " << IMG_GetError() << std::endl;
        return false;
    }

    mTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    if (mTexture == nullptr) {
        std::cerr << "Unable to create texture from " << path << "! SDL Error: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(loadedSurface);
        return false;
    }

    mWidth = loadedSurface->w;
    mHeight = loadedSurface->h;
    SDL_FreeSurface(loadedSurface);

    return true;
}

void Image::render(int x, int y, SDL_Renderer* renderer) {
    SDL_Rect renderQuad = {x, y, mWidth, mHeight};
    SDL_RenderCopy(renderer, mTexture, nullptr, &renderQuad);
}

void Image::renderIndex(int x, int y, int w, int h, SDL_Renderer* renderer) {
    SDL_Rect renderQuad = {x, y, w, h};
    SDL_RenderCopy(renderer, mTexture, nullptr, &renderQuad);
}

void Image::free() {
    if (mTexture != nullptr) {
        SDL_DestroyTexture(mTexture);
        mTexture = nullptr;
        mWidth = 0;
        mHeight = 0;
    }
}
