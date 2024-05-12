#ifndef SCORE_H
#define SCORE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class Score {
private:
    SDL_Color color;
    int level;
    int score;
    int timeClick;
    std::string noti;
    SDL_Rect rect;
    SDL_Rect rectScore;
    TTF_Font* font;

public:
    Score(SDL_Color color, int level, int score, int timeClick, int x, int y, std::string noti);
    ~Score();

    void update(int level, int score, int timeClick);
    void render(SDL_Renderer* renderer);

    SDL_Rect getRect() const;
    SDL_Rect getRectScore();
    std::string getNoti();
};

#endif // SCORE_H
