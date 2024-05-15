 #include "Func.h"
 #include <algorithm>
 #include <random>


using namespace std;

int main(int argc, char* argv[]) {
    if (!init(window, renderer)) {
        cleanup(window, renderer);
        return 1;
    }
    read("C:\\Users\\thinh\\OneDrive\\Documents\\VSCodeSDL\\DT\\image.txt", image0, image1, image2, image3, image4, image5, image6, image7, image8, image9, img0, img1, img2, img3, img4, img5, img6, img7, img8, img9);
    random_device rd;
    mt19937 g(rd());
    shuffle(image0.begin(), image0.end(), g);

    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            if(start){
                renderStart();
                if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                    handleStartButtonClick( event, start,choosenum);
                }
            }
            else{
                if (choosenum) {
                    renderImagechoose();
                    if (event.type == SDL_KEYDOWN) {
                        SDL_Keycode keyPressed = event.key.keysym.sym;
                        if (keyPressed >= SDLK_0 && keyPressed <= SDLK_9) {
                            handleKeyPress(keyPressed, image, choosenum, play, renderer, arrayIcon, level,special);
                        }
                    }
                }
                if (play) {
                    handleGameRunningEvent(event, arrayIcon, arrayIconChoosed, timeClick, level, score, renderer, gameOver,win);
                    if(win&&!isWin){
                        renderWin();
                        isWin = true;
                    }
                    if (isWin && event.type == SDL_KEYDOWN){
                        handleRestartWin(event.key.keysym.sym, running, level, score, timeClick, choosenum, play, win, isWin, isPlayingGameOver);
                    }
                }
            }
        }
    }
    cleanup(window, renderer);
    return 0;
}
