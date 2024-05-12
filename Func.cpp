#include "Func.h"

bool running = true;
bool play = false;//true để load từ ảnh chọn số vào trong game
int wigWin = 600;
int heiWin = wigWin + 100;
int level = 3;
int score = 0;
int borderSpace = static_cast<int>(wigWin * 0.1);
int iconSpace = 12;
int fps = 60;
int timeClick = 6;
bool gameOver = false;//true để hiển thị ảnh gameover và lựa chọn
bool start = true;//true hiển thị ảnh nền và ảnh nút start, false để chạy game vào trong
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
Mix_Music *gMusic = NULL;
TTF_Font* font = NULL;
SDL_Texture* texture = NULL;
SDL_Color colorBg = {52, 73, 94};
std::vector<Icon> arrayIcon;
std::vector<Icon> arrayIconChoosed;
std::string special = "image/aot.jpg";
std::string backside = "image/player.jpg";
std::string GOver = "image/gameover.jpg";
std::string startImg = "image/start.jpg";
std::string backgroundImg = "image/background.jpg";
 
std::vector<std::string> image = {"image/1.jpg", "image/2.jpg", "image/3.jpg", "image/4.jpg", "image/5.jpg", "image/6.jpg"};
std::vector<int> arrNum;
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

    window = SDL_CreateWindow("DT", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, wigWin, heiWin, SDL_WINDOW_SHOWN);
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

    font = TTF_OpenFont("image/game.ttf", 24);
    if (!font) {
        //cout << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << endl;
        return false;
    }
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 1024 ) < 0 )
				{
					cout<<"SDL_mixer could not initialize! SDL_mixer Error: "<<Mix_GetError()<<endl;
					return false;
				}
    gMusic = Mix_LoadMUS( "music/Tuongquan.mp3" );
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
    return static_cast<int>((wigWin - (2 * borderSpace + (level * iconSpace))) / (level + 1));
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
    scoreRender = Score(colorBg, level, score, timeClick, wigWin, heiWin, "Level: " + to_string(level) + "  " + "Score: " + to_string(score) + "  " + "Click: " + to_string(timeClick));
    SDL_Surface* notiSurface = TTF_RenderText_Solid(font, scoreRender.getNoti().c_str(), {52, 152, 219});
    SDL_Texture* notiTexture = SDL_CreateTextureFromSurface(renderer, notiSurface);
    SDL_Rect notiRect = {0, wigWin, notiSurface->w, notiSurface->h};
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
    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void playSound(const std::string& soundFile, int repeatCount) {
    // Ngừng bài nhạc đang phát
    Mix_HaltMusic();

    // Tải và phát bài nhạc mới
    Mix_Music* music = Mix_LoadMUS(soundFile.c_str());
    if (!music) {
        std::cerr << "Failed to load music file: " << soundFile << "! SDL_mixer Error: " << Mix_GetError() << std::endl;
        return;
    }
    Mix_PlayMusic(music, repeatCount); // Phát với số lần lặp lại đã chỉ định

    // Giải phóng bộ nhớ đã cấp phát cho bài nhạc
    Mix_FreeMusic(music);
}

void showStartScreen() {
    backgroundImage.loadTexture(backgroundImg, renderer);
    backgroundImage.render(0, 0, renderer);
    startImage.loadTexture(startImg, renderer);
    startImage.renderIndex(wigWin/4,heiWin/4,wigWin/2,heiWin/2, renderer);
    SDL_RenderPresent(renderer);
}