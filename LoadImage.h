#ifndef IMAGE_H
#define IMAGE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

class Image {
private:
    SDL_Texture* mTexture = nullptr;
    int mWidth;
    int mHeight;
    SDL_Rect rect;

public:
    Image();
    ~Image();
    Image(SDL_Texture* tex, int x, int y, int w, int h);

    int getWidth() const;
    int getHeight() const;
    SDL_Rect getRect() const;
    bool loadTexture(const std::string& path, SDL_Renderer* renderer);
    void render(int x, int y, SDL_Renderer* renderer);
    void renderIndex(int x, int y, int w, int h, SDL_Renderer* renderer);
    void free();
};

#endif // IMAGE_H
