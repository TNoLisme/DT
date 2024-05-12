#ifndef FUNC_H
#define FUNC_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "Score.h"
#include "Icon.h"
#include "LoadImage.h"

using namespace std;


extern bool running;
extern bool play;
extern bool gameOver;
extern bool start;
extern int wigWin;
extern int heiWin;
extern int level;
extern int score;
extern int borderSpace;
extern int iconSpace;
extern int fps;
extern int timeClick;
extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern SDL_Texture* texture;
extern Mix_Music *gMusic;
extern TTF_Font* font;
extern SDL_Color colorBg;
extern std::vector<Icon> arrayIcon;
extern std::vector<Icon> arrayIconChoosed;
extern std::string special;
extern std::string backside;
extern std::string GOver;
extern std::string backgroundImg;
extern std::string startImg;

extern std::vector<std::string> image;

extern std::vector<int> arrNum;
extern Score scoreRender;

Image backgroundImage;
Image startImage;


bool init(SDL_Window*& window, SDL_Renderer*& renderer);
void displayGameOver(SDL_Renderer* renderer);
void initStateIcon(std::vector<int>& stateIcon, const std::vector<Icon>& arrayIcon);
void drawIcon(int x, int y, int hei, SDL_Renderer* renderer);
void makeArrNum(int num);
void makeArrayIcon(SDL_Renderer* renderer, std::vector<Icon>& arrayIcon, int level);
void choosed(SDL_Renderer* renderer, const std::string& image, int x, int y, int hei);
void makeScore(int level, SDL_Renderer* renderer);
void cleanup(SDL_Window* window, SDL_Renderer* renderer);
std::vector<std::vector<int>> makePos(int level);
void playSound(const std::string& soundFile, int repeatCount);
void showStartScreen();





#endif // FUNC_H
