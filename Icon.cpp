#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
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
};

Icon::Icon(int x, int y, int hei, std::string image) : x(x), y(y), hei(hei), image(image) {
    Rec = { x, y, hei, hei };
    recBd = { x - 2, y - 2, hei + 4, hei + 4 };
    color = { 189, 195, 199 };
    colorBd = { 229, 80, 57 };
    iconTexture = nullptr;
}

Icon::~Icon() {
    if (iconTexture != nullptr) {
        SDL_DestroyTexture(iconTexture);
    }
}

void Icon::draw(SDL_Renderer* renderer) {
    if (iconTexture == nullptr) {
        SDL_Surface* iconSurface = IMG_Load(image.c_str());
        iconTexture = SDL_CreateTextureFromSurface(renderer, iconSurface);
        SDL_FreeSurface(iconSurface);
    }

    SDL_Rect iconRect = { x, y, hei, hei };
    SDL_RenderCopy(renderer, iconTexture, nullptr, &iconRect);
}

std::vector<int> Icon::getPos() {
    return { x, y };
}

int Icon::getHei() {
    return hei;
}

SDL_Rect Icon::getRec() {
    return Rec;
}

SDL_Rect Icon::getRecBd() {
    return recBd;
}

SDL_Color Icon::getColor() {
    return color;
}

SDL_Color Icon::getColorBd() {
    return colorBd;
}

std::string Icon::getImage() {
    return image;
}
