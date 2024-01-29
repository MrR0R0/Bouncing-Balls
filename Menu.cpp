#include "Menu.h"
#include "TextureManager.h"
#include "FileManager.h"
#include "Paths.h"

SDL_Color white = {255, 255, 255};
SDL_Color cyan = {127,255,212};

std::string EndMenu::text, EndMenu::textCpy;

void MainMenu::init(){
    setRectWithCenter(titleRect, 300, 100, 300, 80);
    setRectWithCenter(startRect, 300, 250, 100, 50);
    setRectWithCenter(modeRect, 300, 400, 100, 50);
    setRectWithCenter(scoreRect, 300, 550, 180, 50);
    setRectWithCenter(soundMenuRect, 500, 700, 64, 64);
    setRectWithCenter(settingRect, 100, 700, 64, 64);
    titleMessage = TextureManager::LoadFont("..\\fonts\\comic.ttf", 30, "Bouncing Balls", cyan);
    startMessage = TextureManager::LoadFont("..\\fonts\\comic.ttf", 24, "Start!", white);
    modeMessage = TextureManager::LoadFont("..\\fonts\\comic.ttf", 24, "Modes", white);
    scoreMessage = TextureManager::LoadFont("..\\fonts\\comic.ttf", 24, "Score Board", white);
    soundMenuPic = TextureManager::LoadTexture(soundMenuPicPath);
    settingPic = TextureManager::LoadTexture("..\\assets\\cog.png");
}

void MainMenu::render(){
    SDL_RenderCopy(Game::renderer, titleMessage, nullptr, &titleRect);
    SDL_RenderCopy(Game::renderer, startMessage, nullptr, &startRect);
    SDL_RenderCopy(Game::renderer, modeMessage, nullptr, &modeRect);
    SDL_RenderCopy(Game::renderer, scoreMessage, nullptr, &scoreRect);
    SDL_RenderCopy(Game::renderer, soundMenuPic, nullptr, &soundMenuRect);
    SDL_RenderCopy(Game::renderer, settingPic, nullptr, &settingRect);
    SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(Game::renderer, &startRect);
    SDL_RenderDrawRect(Game::renderer, &modeRect);
    SDL_RenderDrawRect(Game::renderer, &scoreRect);
    SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
}

void MainMenu::handleEvents(SDL_Event event) {
    int x_mouse, y_mouse;
    switch (event.type) {
        case SDL_QUIT:
            Game::isRunning = false;
            break;
        case SDL_MOUSEBUTTONDOWN:
            SDL_GetMouseState(&x_mouse, &y_mouse);
            if(pointInRect(scoreRect, x_mouse, y_mouse))
                Game::menuQueue.push_back(Score);
            else if(pointInRect(startRect, x_mouse, y_mouse))
                Game::menuQueue.push_back(Play);
            else if(pointInRect(modeRect, x_mouse, y_mouse))
                Game::menuQueue.push_back(Modes);
            else if(pointInRect(settingRect, x_mouse, y_mouse))
                Game::menuQueue.push_back(Settings);
            else if(pointInRect(soundMenuRect, x_mouse, y_mouse))
                Game::menuQueue.push_back(Sound);
            break;
        default:
            break;
    }
}

void ModeMenu::init(){
    setRectWithCenter(countdownRect, 300, 250, 9*20, 50);
    setRectWithCenter(randomRect, 300, 400, 6*20, 50);
    setRectWithCenter(infinityRect, 300, 550, 8*20, 50);
    setRectWithCenter(backRect, 100, 100, 64, 64);
    countdownMessage = TextureManager::LoadFont("..\\fonts\\comic.ttf", 26, "Countdown", white);
    randomMessage = TextureManager::LoadFont("..\\fonts\\comic.ttf", 26, "Random", cyan);
    infinityMessage = TextureManager::LoadFont("..\\fonts\\comic.ttf", 26, "Infinity", white);
    backPic = TextureManager::LoadTexture(backPicPath);
}

void ModeMenu::render(){
    SDL_RenderCopy(Game::renderer, countdownMessage, nullptr, &countdownRect);
    SDL_RenderCopy(Game::renderer, randomMessage, nullptr, &randomRect);
    SDL_RenderCopy(Game::renderer, infinityMessage, nullptr, &infinityRect);
    SDL_RenderCopy(Game::renderer, backPic, nullptr, &backRect);
    SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(Game::renderer, &infinityRect);
    SDL_RenderDrawRect(Game::renderer, &randomRect);
    SDL_RenderDrawRect(Game::renderer, &countdownRect);
    SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
}

void ModeMenu::handleEvents(SDL_Event event) {
    int x_mouse, y_mouse;
    switch (event.type) {
        case SDL_QUIT:
            Game::isRunning = false;
            break;
        case SDL_MOUSEBUTTONDOWN:
            SDL_GetMouseState(&x_mouse, &y_mouse);
            if(pointInRect(backRect, x_mouse, y_mouse))
                Game::menuQueue.pop_back();
            else if(pointInRect(countdownRect, x_mouse, y_mouse)) {
                Game::gameMode = Countdown;
                countdownMessage = TextureManager::LoadFont("..\\fonts\\comic.ttf", 26, "Countdown", cyan);
                randomMessage = TextureManager::LoadFont("..\\fonts\\comic.ttf", 26, "Random", white);
                infinityMessage = TextureManager::LoadFont("..\\fonts\\comic.ttf", 26, "Infinity", white);
            }
            else if(pointInRect(infinityRect, x_mouse, y_mouse)) {
                Game::gameMode = Infinity;
                countdownMessage = TextureManager::LoadFont("..\\fonts\\comic.ttf", 26, "Countdown", white);
                randomMessage = TextureManager::LoadFont("..\\fonts\\comic.ttf", 26, "Random", white);
                infinityMessage = TextureManager::LoadFont("..\\fonts\\comic.ttf", 26, "Infinity", cyan);
            }
            else if(pointInRect(randomRect, x_mouse, y_mouse)) {
                Game::gameMode = Random;
                countdownMessage = TextureManager::LoadFont("..\\fonts\\comic.ttf", 26, "Countdown", white);
                randomMessage = TextureManager::LoadFont("..\\fonts\\comic.ttf", 26, "Random", cyan);
                infinityMessage = TextureManager::LoadFont("..\\fonts\\comic.ttf", 26, "Infinity", white);
            }
            break;
        default:
            break;
    }
}

void SettingsMenu::init(){
    setRectWithCenter(theme1Rect, 112, 300, 150, 300);
    setRectWithCenter(theme2Rect, 300, 300, 150, 300);
    setRectWithCenter(theme3Rect, 487, 300, 150, 300);
    setRectWithCenter(ball1Rect, 150, 600, 50, 50);
    setRectWithCenter(ball2Rect, 300, 600, 50, 50);
    setRectWithCenter(ball3Rect, 450, 600, 50, 50);
    setRectWithCenter(backgroundRect, 300, 100, 150, 50);
    setRectWithCenter(ballRect, 300, 525, 150, 50);
    setRectWithCenter(backRect, 75, 75, 64, 64);
    backgroundMessage = TextureManager::LoadFont("..\\fonts\\comic.ttf", 24, "Backgrounds", white);
    ballMessage = TextureManager::LoadFont("..\\fonts\\comic.ttf", 24, "Ball Texture", white);
    theme1Pic = TextureManager::LoadTexture(theme1Path);
    theme2Pic = TextureManager::LoadTexture(theme2Path);
    theme3Pic = TextureManager::LoadTexture(theme3Path);
    ball1Pic = TextureManager::LoadTexture(ball1Path);
    ball2Pic = TextureManager::LoadTexture(ball2Path);
    ball3Pic = TextureManager::LoadTexture(ball3Path);
    backPic = TextureManager::LoadTexture(backPicPath);
}

void SettingsMenu::render(){
    SDL_RenderCopy(Game::renderer, backgroundMessage, nullptr, &backgroundRect);
    SDL_RenderCopy(Game::renderer, ballMessage, nullptr, &ballRect);
    SDL_RenderCopy(Game::renderer, theme1Pic, nullptr, &theme1Rect);
    SDL_RenderCopy(Game::renderer, theme2Pic, nullptr, &theme2Rect);
    SDL_RenderCopy(Game::renderer, theme3Pic, nullptr, &theme3Rect);
    SDL_RenderCopy(Game::renderer, ball1Pic, nullptr, &ball1Rect);
    SDL_RenderCopy(Game::renderer, ball2Pic, nullptr, &ball2Rect);
    SDL_RenderCopy(Game::renderer, ball3Pic, nullptr, &ball3Rect);
    SDL_RenderCopy(Game::renderer, backPic, nullptr, &backRect);
    SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(Game::renderer, &theme1Rect);
    SDL_RenderDrawRect(Game::renderer, &theme2Rect);
    SDL_RenderDrawRect(Game::renderer, &theme3Rect);
    SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
}

void SettingsMenu::handleEvents(SDL_Event event){
    int x_mouse, y_mouse;
    switch (event.type) {
        case SDL_QUIT:
            Game::isRunning = false;
            break;
        case SDL_MOUSEBUTTONDOWN:
            SDL_GetMouseState(&x_mouse, &y_mouse);
            if(pointInRect(backRect, x_mouse, y_mouse)) {
                Game::menuQueue.pop_back();
            }
            else if(pointInRect(theme1Rect, x_mouse, y_mouse)) {
                Game::background = TextureManager::LoadTexture(theme1Path);
            }
            else if(pointInRect(theme2Rect, x_mouse, y_mouse)) {
                Game::background = TextureManager::LoadTexture(theme2Path);
            }
            else if(pointInRect(theme3Rect, x_mouse, y_mouse)) {
                Game::background = TextureManager::LoadTexture(theme3Path);
            }
            break;
        default:
            break;
    }
}

void SoundMenu::init() {
    setRectWithCenter(theme1Rect, 100, 600, 120, 50);
    setRectWithCenter(theme2Rect, 300, 600, 100, 50);
    setRectWithCenter(theme3Rect, 500, 600, 100, 50);
    setRectWithCenter(musicRect, 300, 450, 100, 50);
    setRectWithCenter(soundBarRect, 250, 300, 200, 50);
    setRectWithCenter(soundRect,  250, 300, 200, 50);
    setRectWithCenter(speakerRect, 450, 300, 50, 50);
    setRectWithCenter(soundMessageRect, 300, 150, 150, 50);
    setRectWithCenter(backRect, 50, 50, 50, 50);
    soundMessage = TextureManager::LoadFont("..\\fonts\\comic.ttf", 28, "Sound", white);
    musicMessage = TextureManager::LoadFont("..\\fonts\\comic.ttf", 28, "Music", white);
    theme1Message = TextureManager::LoadFont("..\\fonts\\comic.ttf", 24, "Ice Dance", white);
    theme2Message = TextureManager::LoadFont("..\\fonts\\comic.ttf", 24, "Mario", white);
    theme3Message = TextureManager::LoadFont("..\\fonts\\comic.ttf", 24, "Castle", white);
    speakerPic = TextureManager::LoadTexture(unmutePicPath);
    backPic = TextureManager::LoadTexture(backPicPath);
    loadMusic("..\\assets\\ice_dance.mp3");
    isMute = false;
}

void SoundMenu::render(){
    SDL_RenderCopy(Game::renderer, musicMessage, nullptr, &musicRect);
    SDL_RenderCopy(Game::renderer, theme1Message, nullptr, &theme1Rect);
    SDL_RenderCopy(Game::renderer, theme2Message, nullptr, &theme2Rect);
    SDL_RenderCopy(Game::renderer, theme3Message, nullptr, &theme3Rect);
    SDL_RenderCopy(Game::renderer, soundMessage, nullptr, &soundMessageRect);
    SDL_RenderCopy(Game::renderer, speakerPic, nullptr, &speakerRect);
    SDL_RenderCopy(Game::renderer, backPic, nullptr, &backRect);
    SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(Game::renderer, &theme1Rect);
    SDL_RenderDrawRect(Game::renderer, &theme2Rect);
    SDL_RenderDrawRect(Game::renderer, &theme3Rect);
    SDL_RenderDrawRect(Game::renderer, &soundRect);
    SDL_SetRenderDrawColor(Game::renderer, 0, 255, 255, 255);
    SDL_RenderFillRect(Game::renderer, &soundBarRect);
    SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
}

void SoundMenu::handleEvents(SDL_Event event){
    int x_mouse, y_mouse;
    switch (event.type) {
        case SDL_QUIT:
            Game::isRunning = false;
            break;
        case SDL_MOUSEBUTTONDOWN:
            SDL_GetMouseState(&x_mouse, &y_mouse);
            if(pointInRect(soundRect, x_mouse, y_mouse)) {
                soundBarRect.w = x_mouse - soundRect.x;
                prevVolume = soundBarRect.w;
                Mix_VolumeMusic((int)(x_mouse - soundRect.x)*128.0/soundRect.w);
            }
            else if(pointInRect(backRect, x_mouse, y_mouse)){
                Game::menuQueue.pop_back();
            }
            else if(pointInRect(theme1Rect, x_mouse, y_mouse)) {
                loadMusic(music1Path);
            }
            else if(pointInRect(theme2Rect, x_mouse, y_mouse)) {
                loadMusic(music2Path);
            }
            else if(pointInRect(theme3Rect, x_mouse, y_mouse)) {
                loadMusic(music3Path);
            }
            else if(pointInRect(speakerRect, x_mouse, y_mouse)) {
                if(isMute){
                    speakerPic = TextureManager::LoadTexture(unmutePicPath);
                    isMute = false;
                    soundBarRect.w = prevVolume;
                    Mix_ResumeMusic();
                    Mix_VolumeMusic((int)(soundBarRect.w)*128.0/soundRect.w);
                }
                else{
                    speakerPic = TextureManager::LoadTexture(mutePicPath);
                    isMute = true;
                    prevVolume = soundBarRect.w;
                    soundBarRect.w = 0;
                    Mix_PauseMusic();
                }
            }
            break;
        default:
            break;
    }
}

void SoundMenu::loadMusic(const char *path) {
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 1, 2048);
    Game::music = Mix_LoadMUS(path);
    if(Game::music == nullptr)
        std::cout << "Failed to load the music!\n";
    //Mix_PlayMusic(Game::music, -1);
}

void ScoreMenu::setScores(const char* path) {
    int max_char = 10;
    std::string name;
    scores = FileManager::getTopTen(path);
    for(int i=0; i<std::min((int)scores.size(), max_char); i++){
        name = scores[i].second;
        if(scores[i].second.size()>10) name = scores[i].second.substr(0, max_char) + "...";
        setRectWithCenter(scoresRect[i], 450, 50*(i+6), std::to_string(scores[i].first).size()*15, 50);
        scoresMessage[i] = TextureManager::LoadFont("..\\fonts\\comic.ttf", 24, std::to_string(scores[i].first).c_str(), white);
        setRectWithCorner(namesRect[i], 100, 50 * (i + 6) - 25, (int)(name.size() + 2) * 15, 50);
        namesMessage[i] = TextureManager::LoadFont("..\\fonts\\comic.ttf", 24, (std::to_string(i + 1) + ". " + name).c_str(), white);
    }
}

void ScoreMenu::renderScores(){
    for(int i=0; i<scores.size(); i++){
        SDL_RenderCopy(Game::renderer, scoresMessage[i], nullptr, &scoresRect[i]);
        SDL_RenderCopy(Game::renderer, namesMessage[i], nullptr, &namesRect[i]);
    }
}

void ScoreMenu::init(){
    setRectWithCenter(scoreRect, 300, 100, 250, 70);
    setRectWithCenter(infinityRect, 120, 200, 100, 50);
    setRectWithCenter(countdownRect, 300, 200, 150, 50);
    setRectWithCenter(randomRect, 480, 200, 100, 50);
    setRectWithCenter(backRect, 50, 50, 50, 50);
    infinityMessage = TextureManager::LoadFont("..\\fonts\\comic.ttf", 24, "infinity", white);
    randomMessage = TextureManager::LoadFont("..\\fonts\\comic.ttf", 24, "random", white);
    countdownMessage = TextureManager::LoadFont("..\\fonts\\comic.ttf", 24, "countdown", cyan);
    scoreMessage = TextureManager::LoadFont("..\\fonts\\comic.ttf", 28, "Highest Scores", white);
    backPic = TextureManager::LoadTexture(backPicPath);
    setScores(countdownScoresPath);
}

void ScoreMenu::render(){
    SDL_RenderCopy(Game::renderer, infinityMessage, nullptr, &infinityRect);
    SDL_RenderCopy(Game::renderer, countdownMessage, nullptr, &countdownRect);
    SDL_RenderCopy(Game::renderer, randomMessage, nullptr, &randomRect);
    SDL_RenderCopy(Game::renderer, scoreMessage, nullptr, &scoreRect);
    SDL_RenderCopy(Game::renderer, backPic, nullptr, &backRect);
    renderScores();
}

void ScoreMenu::handleEvents(SDL_Event event){
    int x_mouse, y_mouse;
    switch (event.type) {
        case SDL_QUIT:
            Game::isRunning = false;
            break;
        case SDL_MOUSEBUTTONDOWN:
            SDL_GetMouseState(&x_mouse, &y_mouse);
            if(pointInRect(backRect, x_mouse, y_mouse)){
                Game::menuQueue.pop_back();
            }
            else if(pointInRect(randomRect, x_mouse, y_mouse)){
                setScores(randomScoresPath);
                infinityMessage = TextureManager::LoadFont("..\\fonts\\comic.ttf", 24, "infinity", white);
                randomMessage = TextureManager::LoadFont("..\\fonts\\comic.ttf", 24, "random", cyan);
                countdownMessage = TextureManager::LoadFont("..\\fonts\\comic.ttf", 24, "countdown", white);
            }
            else if(pointInRect(infinityRect, x_mouse, y_mouse)){
                setScores(infinityScoresPath);
                infinityMessage = TextureManager::LoadFont("..\\fonts\\comic.ttf", 24, "infinity", cyan);
                randomMessage = TextureManager::LoadFont("..\\fonts\\comic.ttf", 24, "random", white);
                countdownMessage = TextureManager::LoadFont("..\\fonts\\comic.ttf", 24, "countdown", white);            }
            else if(pointInRect(countdownRect, x_mouse, y_mouse)){
                setScores(countdownScoresPath);
                infinityMessage = TextureManager::LoadFont("..\\fonts\\comic.ttf", 24, "infinity", white);
                randomMessage = TextureManager::LoadFont("..\\fonts\\comic.ttf", 24, "random", white);
                countdownMessage = TextureManager::LoadFont("..\\fonts\\comic.ttf", 24, "countdown", cyan);
            }
            break;
        default:
            break;
    }
}

void PlayMenu::setAngle(int &xMouse, int &yMouse){
    dy = abs(yMouse - (cannonRect.y + cannonRect.h/2));
    dx = abs(xMouse - (cannonRect.x + cannonRect.w/2));
    angle = 90 - atan(dy/dx) * 180 / M_PI;
    if(yMouse > cannonRect.y + cannonRect.h/2)
        angle = 90;
    if(xMouse <= cannonRect.x + cannonRect.w/2) {
        angle *= -1;
    }
}

void PlayMenu::init(){
    setRectWithCenter(backRect, 25, 775, 50, 50);
    setRectWithCenter(cannonRect, 300, 750, 100, 100);
    backPic = TextureManager::LoadTexture(backPicPath);
    cannonPic = TextureManager::LoadTexture("..\\assets\\arrow.jpg");
    mp.LoadMap();
}

void PlayMenu::render() {
    mp.render();
    SDL_RenderCopy(Game::renderer, backPic, nullptr, &backRect);
    SDL_RenderCopyEx(Game::renderer, cannonPic, nullptr, &cannonRect, angle, nullptr, SDL_FLIP_NONE);
}

void PlayMenu::handleEvents(SDL_Event event) {
    int x_mouse, y_mouse;
    SDL_GetMouseState(&x_mouse, &y_mouse);
    setAngle(x_mouse, y_mouse);
    switch (event.type) {
        case SDL_QUIT:
            Game::isRunning = false;
            break;
        case SDL_MOUSEBUTTONDOWN:
            if(pointInRect(backRect, x_mouse, y_mouse)){
                mp.destroy();
                Game::menuQueue.pop_back();
                init();
            }
            else{
                mp.addShootingBall(angle, cannonRect);
            }
            break;
        default:
            break;
    }
}

void PlayMenu::update(){
    mp.update();
}

void EndMenu::init() {
    topText = "It's over!";
    text="";
    setRectWithCorner(fullTextRect, 50, 300, 21*20, 50);
    setRectWithCorner(enterNameRect, 50, 250, 220, 50);
    setRectWithCenter(topRect, 300, 100, topText.length()*25, 75);
    setRectWithCorner(tickRect, 500, 300, 50, 50);
    setRectWithCorner(warningRect, 50, 450, 500, 40);
    tickPic = TextureManager::LoadTexture("..\\assets\\tick_icon.png");
    topMessage = TextureManager::LoadFont("..\\fonts\\comic.ttf", 28, topText.c_str(), cyan);
    enterNameMessage = TextureManager::LoadFont("..\\fonts\\comic.ttf", 28, "Enter Your Name:", white);
    warningMessage = TextureManager::LoadFont("..\\fonts\\comic.ttf", 20, "*Number of letters should be below 5 and over 19",
                                                {255, 0, 0});
    endMode = Idle;
}

void EndMenu::render(){
    SDL_RenderCopy(Game::renderer, tickPic, nullptr, &tickRect);
    SDL_RenderCopy(Game::renderer, enterNameMessage, nullptr, &enterNameRect);
    SDL_RenderCopy(Game::renderer, topMessage, nullptr, &topRect);
    SDL_RenderCopy(Game::renderer, textMessage, nullptr, &textRect);
    SDL_RenderCopy(Game::renderer, warningMessage, nullptr, &warningRect);
    SDL_SetRenderDrawColor(Game::renderer, 255, 0, 0, 255);
    SDL_RenderDrawRect(Game::renderer, &fullTextRect);
    SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
}

void EndMenu::update() {
    if(redirect){
        text = makeValid(text);
        if(text.length()>=5) {
            setRectWithCenter(redirectRect, 300, 550, 300, 50);
            redirectMessage = TextureManager::LoadFont("..\\fonts\\comic.ttf", 28, "Your Score Was Stored :)",
                                                       {128, 128, 0});
            switch (Game::gameMode) {
                case Random:
                    FileManager::addScore(randomScoresPath, text, Game::score);
                    break;
                case Infinity:
                    FileManager::addScore(infinityScoresPath, text, Game::score);
                    break;
                case Countdown:
                    FileManager::addScore(countdownScoresPath, text, Game::score);
                    break;
                default:
                    break;
            }
        }
        else{
            setRectWithCenter(redirectRect, 300, 550, 350, 50);
            redirectMessage = TextureManager::LoadFont("..\\fonts\\comic.ttf", 28, "Your Score Was not Stored :(",
                                                       {128, 128, 0});
        }
        SDL_RenderCopy(Game::renderer, redirectMessage, nullptr, &redirectRect);
        SDL_RenderPresent(Game::renderer);
        SDL_Delay(2000);
        Game::menuQueue.pop_back();
        text="";
    }
}

void EndMenu::handleEvents(SDL_Event event) {
    int x_mouse, y_mouse;
    keystates = SDL_GetKeyboardState(nullptr);
    switch (event.type) {
        case SDL_QUIT:
            Game::isRunning = false;
            break;
        case SDL_MOUSEBUTTONDOWN:
            SDL_GetMouseState(&x_mouse, &y_mouse);
            if(pointInRect(tickRect, x_mouse, y_mouse)){
                redirect = true;
            }
            else if(pointInRect(fullTextRect, x_mouse, y_mouse))
                endMode = Write;
            else
                endMode = Idle;
            break;
        default:
            break;
    }
    if(endMode==Write){
        if(event.type == SDL_KEYUP){
            if(left && index>0) {
                left = false;
                index--;
            }
            else if(right && index<text.length()){
                right = false;
                index++;
            }
            else if(index>0 && backspace){
                text.erase(index-1, 1);
                index--;
                backspace=false;
            }
            else if(del && index<text.length()){
                text.erase(index, 1);
                del = false;
            }
        }
        else if(event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_BACKSPACE:
                    if(text.length()>0)
                        backspace = true;
                    break;
                case SDLK_LEFT:
                    if(index>0)
                        left = true;
                    break;
                case SDLK_RIGHT:
                    if(index<text.length())
                        right = true;
                    break;
                case SDLK_DELETE:
                    if(index<text.length())
                        del = true;
                    break;
            }
        }
        if(event.type == SDL_TEXTINPUT && text.length()<20){
            text += event.text.text;
            index++;
        }
        else if((keystates[SDL_SCANCODE_C] && SDL_GetModState()) && KMOD_CTRL)
            SDL_SetClipboardText(text.c_str());
        else if((keystates[SDL_SCANCODE_V] && SDL_GetModState()) && KMOD_CTRL) {
            text = SDL_GetClipboardText();
            text = text.substr(0, 20);
            index = text.length();
        }
        if(text.length() >= 0) {
            textCpy = text;
            textCpy.insert(index, "_");
            setRectWithCorner(textRect, 50 + 5, 300, textCpy.length() * 20, 50);
            textMessage = TextureManager::LoadFont("..\\fonts\\comic.ttf", 26, textCpy.c_str(), white);
        }
    }
    else if(endMode == Idle){
        if(text.length() >= 0) {
            setRectWithCorner(textRect, 50 + 5, 300, text.length() * 20, 50);
            textMessage = TextureManager::LoadFont("..\\fonts\\comic.ttf", 26, text.c_str(), white);
        }
    }
}

std::string EndMenu::makeValid(const std::string str) {
    int righInd, leftInd;
    bool flag=true;
    for(int i=0; i<str.length() && flag; i++)
        if(str[i]!=' '){
            flag = false;
            leftInd = i;
        }
    flag = true;
    for(int i=str.length()-1; i>=0 && flag; i--)
        if(str[i]!=' '){
            flag = false;
            righInd = i;
        }
    if(righInd<leftInd)
        return "";
    return str.substr(leftInd, righInd-leftInd+1);

}