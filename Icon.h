#ifndef ICON_H
#define ICON_H

#include <SDL2/SDL.h>
#include <string>
#include <vector>

class Icon {
private:
    int x;
    int y;
    int hei;
    std::string image;
    SDL_Rect Rec;
    SDL_Rect recBd;
    SDL_Color color;
    SDL_Color colorBd;
    SDL_Texture* iconTexture;

public:
    Icon(int x, int y, int hei, std::string image);
    ~Icon();

    void draw(SDL_Renderer* renderer);

    std::vector<int> getPos();
    int getHei();
    SDL_Rect getRec();
    SDL_Rect getRecBd();
    SDL_Color getColor();
    SDL_Color getColorBd();
    std::string getImage();
    bool operator==(const Icon& other) const {
    return x == other.x && y == other.y && hei == other.hei && image == other.image;
    }
};

#endif 
