#include "Func.h"

using namespace std;


int main(int argc, char* argv[]) {
    if (!init(window, renderer)) {
        cleanup(window, renderer);
        return 1;
    }
    
    makeArrNum((level + 1) * (level + 1)); 
    makeArrayIcon(renderer, arrayIcon, level);

    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            if(start){
                backgroundImage.loadTexture(backgroundImg, renderer);
                backgroundImage.render(0, 0, renderer);
                startImage.loadTexture(startImg, renderer);
                startImage.renderIndex(wigWin/4,heiWin/4,wigWin/2,heiWin/2, renderer);
                SDL_RenderPresent(renderer);

                if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                    int mouseX, mouseY;
                    SDL_GetMouseState(&mouseX, &mouseY);
                    if (mouseX >= wigWin/4 && mouseX <= wigWin/4 + wigWin/2 &&
                        mouseY >= heiWin/4 && mouseY <= heiWin/4 + heiWin/2) {
                        start = false;
                        play = true;
                        playSound("music/nhacplay.mp3",-1);
                    }
                }
            }
            else{
                if(play) {
                    if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT && !gameOver) {
                        int mouseX, mouseY;
                        SDL_GetMouseState(&mouseX, &mouseY);
                        SDL_Point mousePoint = {mouseX, mouseY};
                        for (auto& i : arrayIcon) {
                            SDL_Rect mouseRec = i.getRec();
                            if (SDL_PointInRect(&mousePoint, &mouseRec) && i.getImage() == special) {
                                if (arrayIcon.size() == 1) {
                                    arrayIcon.erase(remove(arrayIcon.begin(), arrayIcon.end(), i), arrayIcon.end());
                                }
                                if (arrayIcon.empty()) { 
                                    level++; 
                                    if (level > 6) {
                                        level = 6;
                                    }
                                    arrNum.clear();
                                    arrayIconChoosed.clear();
                                    arrayIcon.clear();
                                    makeArrNum((level + 1) * (level + 1)); 
                                    makeArrayIcon(renderer, arrayIcon, level);
                                    timeClick = static_cast<int>((level + 1) * (level + 1 ) * (2.0 / 3));
                                }
                                arrayIconChoosed.push_back(i);
                                if (arrayIconChoosed.size() == 2) {
                                    timeClick--;
                                    choosed(renderer, i.getImage(), i.getPos()[0], i.getPos()[1], i.getHei());
                                    SDL_RenderPresent(renderer);
                                    SDL_Delay(200);
                                    arrayIconChoosed.clear();
                                }
                            }
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
                                        playSound("music/deotin.mp3",1);
                                        score += 5;
                                        if (arrayIcon.empty()) { 
                                            level++; 
                                            if (level > 6) {
                                                level = 6;
                                            }
                                            arrNum.clear();
                                            arrayIconChoosed.clear();
                                            arrayIcon.clear();
                                            makeArrNum((level + 1) * (level + 1)); 
                                            makeArrayIcon(renderer, arrayIcon, level);
                                            timeClick = static_cast<int>((level + 1) * (level + 1 ) * (2.0 / 3));
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
                    if (timeClick <= 0) {
                        gameOver = true;
                    }
                    if (event.type == SDL_KEYDOWN && gameOver) {
                        if (event.key.keysym.sym == SDLK_RETURN) { 
                            play = false;
                            // Reset game
                            level = 3;
                            score = 0;
                            timeClick = 2;
                            makeArrNum((level + 1) * (level + 1)); 
                            makeArrayIcon(renderer, arrayIcon, level);
                            gameOver = false;
                            continue;
                        } else if (event.key.keysym.sym == SDLK_SPACE) { 
                            running = false;
                        }
                    }
                
                    // Clear the renderer
                    if (!gameOver) {
                        SDL_SetRenderDrawColor(renderer, colorBg.r, colorBg.g, colorBg.b, SDL_ALPHA_OPAQUE);
                    }
                    SDL_RenderClear(renderer);

                    // Draw icons
                    if (!gameOver) {
                        for (int i = 0; i < arrayIcon.size(); ++i) {          
                            choosed(renderer, backside, arrayIcon[i].getPos()[0], arrayIcon[i].getPos()[1], arrayIcon[i].getHei());
                        }
                        // Handle mouse hover and clicks           
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
                    // Update and render score notification
                    makeScore(level, renderer);
                    if (gameOver) {
                        displayGameOver(renderer);
                    }
                    // Render to window
                    SDL_RenderPresent(renderer);
                    // Delay to control FPS
                    SDL_Delay(1000 / fps);
                }
            }
        }
    }
    // Cleanup and exit
    cleanup(window, renderer);
    return 0;
}