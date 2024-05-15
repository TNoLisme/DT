
#include "Func.h"

bool running = true;
bool choosenum = false; //true để hiển thị ảnh chọn chủ đề từ 0-9
bool play = false;  //true để load từ ảnh chọn số vào trong game
bool gameOver = false;//true để hiển thị ảnh gameover và lựa chọn
bool start = true;//true hiển thị ảnh nền và ảnh nút start, false để chạy game vào trong
bool isPlayingMusicGame = false;
bool isPlayingGameOver = false;
bool win = false;
bool isWin = false;

int wigWin = 750;
int heiWin = 800;
int level = 1;
int levelwin = 5;
int score = 0;
int borderSpace = static_cast<int>(wigWin * 0.1);
int iconSpace = 12;
int fps = 60;
int timeClick = 2;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
Mix_Music *gMusic = NULL;
TTF_Font* font = NULL;
SDL_Texture* texture = NULL;

SDL_Color colorBg = {52, 73, 94};
std::vector<Icon> arrayIcon;
std::vector<Icon> arrayIconChoosed;
std::vector<int> arrNum;
std::string special;
std::string backside = "image/backside.jpg";
std::string GOver = "image/loss.jpg";
std::string backgroundImg = "image/start.jpg";
std::string winImg = "image/playwin.jpg";
std::string choose09 = "image/number.jpg"; 

Image backgroundImage;
Image choosedNum;
Image winImage;

std::vector<std::string> image;
std::vector<std::string> image0;
std::vector<std::string> image1;
std::vector<std::string> image2;
std::vector<std::string> image3;
std::vector<std::string> image4;
std::vector<std::string> image5;
std::vector<std::string> image6;
std::vector<std::string> image7;
std::vector<std::string> image8;
std::vector<std::string> image9;

bool img0 = false;
bool img1 = false;
bool img2 = false;
bool img3 = false;
bool img4 = false;
bool img5 = false;
bool img6 = false;
bool img7 = false;
bool img8 = false;
bool img9 = false;

 Score scoreRender(colorBg, level, score, timeClick, wigWin, heiWin, "Level: " + std::to_string(level) + "  " + "Score: " + std::to_string(score) + "  " + "Click: " + std::to_string(timeClick));

void displayGameOver(SDL_Renderer* renderer) {
    Image gameOverImage;
    if (!gameOverImage.loadTexture(GOver, renderer)) {
        return;
    }
    gameOverImage.render(0, 0, renderer);
}

void initStateIcon(vector<int>& stateIcon, const vector<Icon>& arrayIcon) {
    stateIcon.clear();
    stateIcon.resize(arrayIcon.size(), 0);
}

bool init(SDL_Window*& window, SDL_Renderer*& renderer) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << endl;
        return false;
    }
    window = SDL_CreateWindow("DT MEMORY", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, wigWin, heiWin, SDL_WINDOW_SHOWN);
    if (!window) {
        cout << "Window could not be created! SDL Error: " << SDL_GetError() << endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << endl;
        return false;
    }

    if (TTF_Init() == -1) {
        cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << endl;
        return false;
    }

    font = TTF_OpenFont("image/game.ttf", 36);
    if (!font) {
        //cout << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << endl;
        return false;
    }
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 1024 ) < 0 )
	{
	    cout<<"SDL_mixer could not initialize! SDL_mixer Error: "<<Mix_GetError()<<endl;
		return false;
	}
    gMusic = Mix_LoadMUS( "music/start.mp3" );
	if( gMusic == NULL )
	{
		cout << "Failed to load background texture image!" << Mix_GetError()<< endl;
		return false;
	}
	 else
    {
        // Phát nhạc nền
        Mix_PlayMusic( gMusic, -1 ); // -1 để lặp vô hạn
		Mix_VolumeMusic(MIX_MAX_VOLUME / 4);
		//max là 128
    }
    srand(time(nullptr));
    return true;
}

vector<vector<int>> makePos(int level) {
    vector<vector<int>> pos;
    for (int i = 0; i < level + 1; ++i) {
        for (int j = 0; j < level + 1; ++j) {
            pos.push_back({i, j});
        }
    }
    return pos;
}

int heiIcon(int level) {
    return static_cast<int>((wigWin - 2*borderSpace - (level - 1)*iconSpace) / (level + 1));
}

void drawIcon(int x, int y, int hei, SDL_Renderer* renderer) { 

    SDL_Color color = {96, 163, 188};
    SDL_Color colorBd = {229, 80, 57};
    SDL_Rect rec = {x, y, hei, hei};
    SDL_SetRenderDrawColor(renderer, colorBd.r, colorBd.g, colorBd.b, SDL_ALPHA_OPAQUE);
    SDL_Rect recBd = {x - 2, y - 2, hei + 4, hei + 4};
    SDL_RenderDrawRect(renderer, &recBd);
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &rec);
}

void makeArrNum(int num) {
    arrNum.clear();
    int n = rand() % image.size();
    for (int i = 0; i < num / 2; ++i) {
        int j = (n + i)%image.size();
        arrNum.push_back(j);
        arrNum.push_back(j);
    }
    if (arrNum.size() < num) {
        arrNum.push_back(-1);
    }


}
void makeArrayIcon(SDL_Renderer* renderer, vector<Icon>& arrayIcon, int level) {
    arrayIcon.clear();
    vector<vector<int>> positions = makePos(level);
    vector<int> chosenIndexes;
    
    for (int i = 0; i < positions.size(); ++i) {
        int num = rand() % arrNum.size();        
        if (arrNum[num] != -1) {
            arrayIcon.push_back(Icon(borderSpace + positions[i][0] * (heiIcon(level) + iconSpace), borderSpace + positions[i][1] * (heiIcon(level) + iconSpace), heiIcon(level), image[arrNum[num]]));
        } else {
            arrayIcon.push_back(Icon(borderSpace + positions[i][0] * (heiIcon(level) + iconSpace), borderSpace + positions[i][1] * (heiIcon(level) + iconSpace), heiIcon(level), special));
        }
        arrNum.erase(arrNum.begin() + num);
    }
}

void choosed(SDL_Renderer* renderer, const string& image, int x, int y, int hei) {
    SDL_Surface* imgSurface = IMG_Load(image.c_str());
    SDL_Texture* imgTexture = SDL_CreateTextureFromSurface(renderer, imgSurface);
    SDL_Rect destRect = {x, y, hei, hei};
    SDL_RenderCopy(renderer, imgTexture, nullptr, &destRect);
    SDL_FreeSurface(imgSurface);
    SDL_DestroyTexture(imgTexture);
}

void makeScore(int level, SDL_Renderer* renderer) {
   scoreRender = Score(colorBg, level, score, timeClick, wigWin, heiWin, "Level: " + std::to_string(level) + "     " + "Score: " + std::to_string(score) + "     " + "Click: " + std::to_string(timeClick));
   SDL_Surface* notiSurface = TTF_RenderText_Solid(font, scoreRender.getNoti().c_str(), {255,255,255});
   
   int textWidth = notiSurface->w;
   int textHeight = notiSurface->h;
   int x = (wigWin - textWidth) / 2; // Tọa độ x để văn bản ở giữa màn hình
   int y = (heiWin * 9) / 10; // Tọa độ y để văn bản ở dưới cùng của màn hình
   
   SDL_Texture* notiTexture = SDL_CreateTextureFromSurface(renderer, notiSurface);
   SDL_Rect notiRect = {x, y, textWidth, textHeight};
   SDL_RenderCopy(renderer, notiTexture, nullptr, &notiRect);
   
   SDL_FreeSurface(notiSurface);
   SDL_DestroyTexture(notiTexture);
}

void cleanup(SDL_Window* window, SDL_Renderer* renderer) {

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_FreeMusic( gMusic );
    window = NULL;
	renderer = NULL;
	gMusic = NULL;
    font = NULL;
    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}
void playSound(const std::string& soundFile, int repeatCount) {
    
    if (soundFile == "music/playgame.mp3") {
        if (!start && choosenum && !gameOver) {
            
            Mix_Music* music = Mix_LoadMUS(soundFile.c_str());
            if (!music) {
                std::cout << "Failed to load music file: " << soundFile << "! SDL_mixer Error: " << Mix_GetError() << std::endl;
                return;
            }
            Mix_PlayMusic(music, repeatCount);
            isPlayingMusicGame = true; 
        }
    } else if (soundFile == "music/loss.mp3") {
        Mix_Music* music = Mix_LoadMUS(soundFile.c_str());
        if (!music) {
            std::cout << "Failed to load music file: " << soundFile << "! SDL_mixer Error: " << Mix_GetError() << std::endl;
            return;
        }
        Mix_PlayMusic(music, repeatCount);
        isPlayingGameOver = true; 
    }else {
        
        Mix_Chunk* soundEffect = Mix_LoadWAV(soundFile.c_str());
        if (!soundEffect) {
            std::cout<< "Failed to load sound effect file: " << soundFile << "! SDL_mixer Error: " << Mix_GetError() << std::endl;
            return;
        }
        Mix_PlayChannel(-1, soundEffect, 0);
    }
}

void handleStartButtonClick(SDL_Event event, bool &start, bool &choosenum) {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    if (mouseX >= wigWin / 3 && mouseX <= wigWin / 3 + wigWin / 3 &&
        mouseY >= heiWin / 3 && mouseY <= heiWin / 3 + heiWin / 3) {
        start = false;
        choosenum = true;
        playSound("music/playgame.mp3", -1);
    }
}

void renderStart(){
    backgroundImage.loadTexture(backgroundImg, renderer);
    backgroundImage.render(0, 0, renderer);
    SDL_RenderPresent(renderer);
}

void renderImagechoose(){
    choosedNum.loadTexture(choose09, renderer);
    choosedNum.render(0, 0, renderer);
    SDL_RenderPresent(renderer);
}

void handleKeyPress(SDL_Keycode key, std::vector<std::string>& chosenImage, bool& chooseNum, bool& play, SDL_Renderer* renderer, std::vector<Icon>& arrayIcon, int level, std::string &special) {

    std::vector<std::vector<std::string>> imageList = {image0, image1, image2, image3, image4, image5, image6, image7, image8, image9};
    int index = key - SDLK_0;
    chosenImage = imageList[index];
    selectSpecial(chosenImage, special);
    chooseNum = false;
    play = true;
    makeArrNum((level + 1) * (level + 1)); 
    makeArrayIcon(renderer, arrayIcon, level);

}

bool checkSpecialIcon(Icon& icon) {
    return (icon.getImage() == special);
}

void handleGameRunningEvent(SDL_Event& event, std::vector<Icon>& arrayIcon, std::vector<Icon>& arrayIconChoosed, int& timeClick, int& level, int& score, SDL_Renderer* renderer, bool& gameOver, bool& win) {
    if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT && !gameOver) {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        SDL_Point mousePoint = {mouseX, mouseY};
        for (auto& i : arrayIcon) {
            SDL_Rect mouseRec = i.getRec();
            if (SDL_PointInRect(&mousePoint, &mouseRec)) {
                if (i.getImage() == special) {
                   if (arrayIcon.size() == 1) {
                        arrayIcon.erase(remove(arrayIcon.begin(), arrayIcon.end(), i), arrayIcon.end());
                    }
                    if (arrayIcon.empty()) { 
                        level++; 
                        if (level == levelwin) {
                            win = true;
                        }
                        else{
                            arrNum.clear();
                            arrayIconChoosed.clear();
                            arrayIcon.clear();
                            makeArrNum((level + 1) * (level + 1)); 
                            makeArrayIcon(renderer, arrayIcon, level);
                            timeClick = static_cast<int>((level + 1) * (level + 1 ) * (2.0 / 3));
                        }
                    }else{
                        arrayIconChoosed.push_back(i);
                    }
                    if (arrayIconChoosed.size() == 2) {
                        timeClick--;
                        choosed(renderer, i.getImage(), i.getPos()[0], i.getPos()[1], i.getHei());
                        SDL_RenderPresent(renderer);
                        SDL_Delay(200);
                        arrayIconChoosed.clear();
                        }
                } else {
                    handleNormalIconClick(arrayIcon, arrayIconChoosed, timeClick, renderer);
                }
                break;
            }
        }
    }
    
    if (arrayIcon.empty() && !win) { 
        level++;
        if (level == levelwin) {
            win = true;
        } else {
            
            arrNum.clear();
            arrayIconChoosed.clear();
            arrayIcon.clear();
            makeArrNum((level + 1) * (level + 1)); 
            makeArrayIcon(renderer, arrayIcon, level);
            timeClick = static_cast<int>((level + 1) * (level + 1 ) * (2.0 / 3));
        }
    }
    if(!win){
        if (timeClick <= 0) {
            gameOver = true;
            if (isPlayingMusicGame) {
                Mix_HaltMusic();
                isPlayingMusicGame = false;
                playSound("music/loss.mp3", 1);
            }
        }

        if (event.type == SDL_KEYDOWN && gameOver) {
            if (event.key.keysym.sym == SDLK_RETURN) { 
                handleRestartLoss(level, score, timeClick, arrayIcon, arrayIconChoosed, renderer, gameOver);
            } else if (event.key.keysym.sym == SDLK_SPACE) { 
                running = false; 
            }
        }


        if (!gameOver) {
            SDL_SetRenderDrawColor(renderer, colorBg.r, colorBg.g, colorBg.b, SDL_ALPHA_OPAQUE);
        }
        SDL_RenderClear(renderer);

        if (!gameOver&&play) {
            drawIcon(renderer);     
        }
        
        makeScore(level, renderer);
        if (gameOver) {
            displayGameOver(renderer);
            renderScore(score, renderer); 
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(1000 / fps);
    }   
}

void renderScore(int score, SDL_Renderer* renderer) {

    std::string scoreText = "Score: " + std::to_string(score);
    int fontSize = heiWin / 5;
    TTF_Font* scoreFont = TTF_OpenFont("image/game.ttf", fontSize);
    if (!scoreFont) {
        return;
    }

    SDL_Surface* surface = TTF_RenderText_Solid(scoreFont, scoreText.c_str(), {255, 255, 255}); // Màu trắng
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    int textWidth = surface->w;
    int textHeight = surface->h;
    int centerX = (wigWin - textWidth) / 2;
    int centerY = (heiWin - textHeight) / 2;


    SDL_Rect rect = {centerX, centerY, textWidth, textHeight};
    SDL_RenderCopy(renderer, texture, nullptr, &rect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    TTF_CloseFont(scoreFont);
}

void handleNormalIconClick(std::vector<Icon>& arrayIcon, std::vector<Icon>& arrayIconChoosed, int& timeClick, SDL_Renderer* renderer) {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    SDL_Point mousePoint = {mouseX, mouseY}; 

    for (auto& i : arrayIcon) {
        SDL_Rect mouseRec = i.getRec();
        if (SDL_PointInRect(&mousePoint, &mouseRec) && find(arrayIconChoosed.begin(), arrayIconChoosed.end(), i) == arrayIconChoosed.end() && i.getImage() != special) {
            arrayIconChoosed.push_back(i);
            if (arrayIconChoosed.size() == 2) {
                choosed(renderer, i.getImage(), i.getPos()[0], i.getPos()[1], i.getHei());
                SDL_RenderPresent(renderer);
                SDL_Delay(200);
                if (arrayIconChoosed[0].getImage() == arrayIconChoosed[1].getImage()) {
                    arrayIcon.erase(remove(arrayIcon.begin(), arrayIcon.end(), arrayIconChoosed[0]), arrayIcon.end());
                    arrayIcon.erase(remove(arrayIcon.begin(), arrayIcon.end(), arrayIconChoosed[1]), arrayIcon.end());
                    arrayIconChoosed.clear();
                    playSound("music/choosetrue.mp3",1);
                    score += 5;
                    if (arrayIcon.empty()) { 
                        level++; 
                        if (level == levelwin) {
                            win = true;
                        }
                        else{
                            arrNum.clear();
                            arrayIconChoosed.clear();
                            arrayIcon.clear();
                            makeArrNum((level + 1) * (level + 1)); 
                            makeArrayIcon(renderer, arrayIcon, level);
                            timeClick = static_cast<int>((level + 1) * (level + 1 ) * (2.0 / 3));
                        }
                    }
                } else {
                    arrayIconChoosed.clear();
                    timeClick--;
                    playSound("music/choosefalse.mp3",1);
                }
            }
        }
    }
}

void handleRestartLoss(int& level, int& score, int& timeClick, std::vector<Icon>& arrayIcon, std::vector<Icon>& arrayIconChoosed, SDL_Renderer* renderer, bool& gameOver) {
    level = 1;
    score = 0;
    timeClick = 2;
    makeArrNum((level + 1) * (level + 1)); 
    makeArrayIcon(renderer, arrayIcon, level);
    gameOver = false;
    choosenum = true;
    play = false;
    if (isPlayingGameOver) {
        Mix_HaltMusic(); 
        isPlayingGameOver = false; 
    }  
    playSound("music/playgame.mp3", -1);
}
void handleRestartWin(SDL_Keycode key, bool& running, int& level, int& score, int& timeClick,
                    bool& choosenum, bool& play, bool& win, bool& isWin, bool& isPlayingGameOver) {
    if (key == SDLK_RETURN) {
        level = 1;
        score = 0;
        timeClick = 2;
        makeArrNum((level + 1) * (level + 1));
        makeArrayIcon(renderer, arrayIcon, level);
        gameOver = false;
        choosenum = true;
        play = false;
        win = false;
        isWin = false;
        if (isPlayingGameOver) {
            Mix_HaltMusic();
            isPlayingGameOver = false;
        }
        playSound("music/playgame.mp3", -1);
    } else if (key == SDLK_SPACE) {
        running = false;
    }
}


void drawIcon(SDL_Renderer* renderer) {
    for (int i = 0; i < arrayIcon.size(); ++i) {          
        choosed(renderer, backside, arrayIcon[i].getPos()[0], arrayIcon[i].getPos()[1], arrayIcon[i].getHei());
    }
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    for (auto& i : arrayIcon) {
        SDL_Rect mouseRec = i.getRec();
        if (SDL_PointInRect(new SDL_Point{mouseX, mouseY}, &mouseRec)) {
            drawIcon(i.getPos()[0], i.getPos()[1], i.getHei(), renderer);
        }
        if (find(arrayIconChoosed.begin(), arrayIconChoosed.end(), i) != arrayIconChoosed.end()) {
            drawIcon(i.getPos()[0], i.getPos()[1], i.getHei(), renderer);
            choosed(renderer, i.getImage(), i.getPos()[0], i.getPos()[1], i.getHei());
        }          
    }
}
void renderWin(){
    SDL_RenderClear(renderer);
    if (isPlayingMusicGame) {
        Mix_HaltMusic();
        isPlayingMusicGame = false;
    }
    playSound("music/win.mp3", 1);
    winImage.loadTexture(winImg,renderer);
    winImage.render(0,0,renderer);
    SDL_RenderPresent(renderer);
}


void read(const string path, vector<string> &image0,vector<string> &image1, vector<string> &image2, vector<string> &image3, vector<string> &image4, 
    vector<string> &image5, vector<string> &image6,vector<string> &image7, vector<string> &image8, vector<string> &image9 , bool &img0 , bool &img1 , 
    bool &img2 , bool &img3 , bool &img4 , bool &img5 , bool &img6 , bool &img7 , bool &img8 , bool &img9 )
{
    ifstream file(path);
    if(file.is_open()){
        string k;

        while(file>>k){
            if(k=="image0"){
                img0 = true;
            }else if(k=="image1"){
                img0=false;
                img1=true;
            }else if(k=="image2"){
                img1=false;
                img2=true;
            }
            else if(k=="image3"){
                img2=false;
                img3=true;
            }
            else if(k=="image4"){
                img3=false;
                img4=true;
            }
            else if(k=="image5"){
                img4=false;
                img5=true;
            }
            else if(k=="image6"){
                img5=false;
                img6=true;
            }
            else if(k=="image7"){
                img6=false;
                img7=true;
            }
            else if(k=="image8"){
                img7=false;
                img8=true;
            }else if(k=="image9"){
                img8=false;
                img9=true;
            }

            if(img0) image0.push_back(k);
            else if(img1) image1.push_back(k);
            else if(img2) image2.push_back(k);
            else if(img3) image3.push_back(k);
            else if(img4) image4.push_back(k);
            else if(img5) image5.push_back(k);
            else if(img6) image6.push_back(k);
            else if(img7) image7.push_back(k);
            else if(img8) image8.push_back(k);
            else if(img9) image9.push_back(k);
        }

        image0.erase(image0.begin());
        image1.erase(image1.begin());
        image2.erase(image2.begin());
        image3.erase(image3.begin());
        image4.erase(image4.begin());
        image5.erase(image5.begin());
        image6.erase(image6.begin());
        image7.erase(image7.begin());
        image8.erase(image8.begin());
        image9.erase(image9.begin());
    }
    else cout<<"NOT OPEN";
}
void selectSpecial(std::vector<std::string>& image, std::string& special){
    
    std::srand(time(0));
    int randomIndex = std::rand() % image.size();
    special = image[randomIndex];
    image.erase(image.begin() + randomIndex);
}
