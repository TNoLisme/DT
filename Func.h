#ifndef FUNC_H
#define FUNC_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream> 
#include <fstream>
#include <random>
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
extern bool choosenum;
extern bool isPlayingMusicGame;
extern bool isPlayingGameOver;
extern bool win;
extern bool isWin;

extern int wigWin;
extern int heiWin;
extern int level;
extern int levelwin;
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
extern std::vector<int> arrNum;
extern Score scoreRender;
extern std::string special;
extern std::string backside;
extern std::string GOver;
extern std::string backgroundImg;
extern std::string startImg;
extern std::string choose09;

extern std::string winMusic;
extern std::string lossMusic;
extern std::string playMusic;
extern std::string startMusic;
extern std::string chooseTrue;
extern std::string chooseFalse; 

extern Image backgroundImage;
extern Image choosedNum;
extern Image winImage;

extern std::vector<std::string> image;
extern std::vector<std::string> image0;
extern std::vector<std::string> image1;
extern std::vector<std::string> image2;
extern std::vector<std::string> image3;
extern std::vector<std::string> image4;
extern std::vector<std::string> image5;
extern std::vector<std::string> image6;
extern std::vector<std::string> image7;
extern std::vector<std::string> image8;
extern std::vector<std::string> image9;

extern bool img0;
extern bool img1;
extern bool img2;
extern bool img3;
extern bool img4;
extern bool img5;
extern bool img6;
extern bool img7;
extern bool img8;
extern bool img9;


bool init(SDL_Window*& window, SDL_Renderer*& renderer);
void read(const string path, vector<string> &image0,vector<string> &image1, vector<string> &image2, vector<string> &image3, vector<string> &image4, 
    vector<string> &image5, vector<string> &image6,vector<string> &image7, vector<string> &image8, vector<string> &image9 , bool &img0 , bool &img1 , 
    bool &img2 , bool &img3 , bool &img4 , bool &img5 , bool &img6 , bool &img7 , bool &img8 , bool &img9 );
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
void handleStartButtonClick(SDL_Event event, bool &start, bool &choosenum) ;
void renderStart();
void renderImagechoose();
void handleKeyPress(SDL_Keycode key, std::vector<std::string>& chosenImage, bool& chooseNum, bool& play, SDL_Renderer* renderer, std::vector<Icon>& arrayIcon, int level, std::string &special);
void handleNormalIconClick(std::vector<Icon>& arrayIcon, std::vector<Icon>& arrayIconChoosed, int& timeClick, SDL_Renderer* renderer);
void handleGameRunningEvent(SDL_Event& event, std::vector<Icon>& arrayIcon, std::vector<Icon>& arrayIconChoosed, int& timeClick, int& level, int& score, SDL_Renderer* renderer, bool& gameOver, bool& win);
void handleRestartLoss(int& level, int& score, int& timeClick, std::vector<Icon>& arrayIcon, std::vector<Icon>& arrayIconChoosed, SDL_Renderer* renderer, bool& gameOver);
void handleRestartWin(SDL_Keycode key, bool& running, int& level, int& score, int& timeClick,bool& choosenum, bool& play, bool& win, bool& isWin, bool& isPlayingGameOver);
void drawIcon(SDL_Renderer* renderer);
void renderScore(int score, SDL_Renderer* renderer);
void renderWin();
void selectSpecial(std::vector<std::string>& image, std::string& special);

#endif
