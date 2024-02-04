#include "Menu.h"
#include "FileManager.h"

SDL_Color white = {255, 255, 255};
SDL_Color cyan = {127,255,212};
SDL_Color black = {0, 0, 0};
SDL_Rect backRect{50, 50, 50, 50};
SDL_Texture *backPic;
SDL_Rect PauseMenu::soundRect, PauseMenu::soundBarRect;
SDL_Rect SoundMenu::soundRect, SoundMenu::soundBarRect;
SDL_Texture *SoundMenu::speakerPic, *PauseMenu::speakerPic;

Uint32 PlayMenu::lastTick;
SDL_Rect PlayMenu::cannonRect, PlayMenu::barRect, PlayMenu::messageRect, PlayMenu::pauseMenuRect;
SDL_Texture *PlayMenu::cannonPic, *PlayMenu::textMessage, *PlayMenu::pauseMenuPic;
Map PlayMenu::map;


int SoundMenu::prevVolume;
bool SoundMenu::isMute;

double dx, dy;
int x_mouse, y_mouse;
std::string EndMenu::text, EndMenu::textCpy;

void MainMenu::init(){
    setRectWithCenter(titleRect, 300, 100, 300, 80);
    setRectWithCenter(startRect, 300, 250, 100, 50);
    setRectWithCenter(modeRect, 300, 400, 100, 50);
    setRectWithCenter(scoreRect, 300, 550, 180, 50);
    setRectWithCenter(soundMenuRect, 500, 700, 64, 64);
    setRectWithCenter(settingRect, 100, 700, 64, 64);
    titleMessage = TextureManager::LoadFont(comicFontPath, 30, "Bouncing Balls", cyan);
    startMessage = TextureManager::LoadFont(comicFontPath, 24, "Start!", white);
    modeMessage = TextureManager::LoadFont(comicFontPath, 24, "Modes", white);
    scoreMessage = TextureManager::LoadFont(comicFontPath, 24, "Score Board", white);
    soundMenuPic = TextureManager::LoadTexture(musicalNotePicPath);
    settingPic = TextureManager::LoadTexture(cogPicPath);
    backPic = TextureManager::LoadTexture(backPicPath);
}

void MainMenu::render(){
    SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(Game::renderer, &startRect);
    SDL_RenderDrawRect(Game::renderer, &modeRect);
    SDL_RenderDrawRect(Game::renderer, &scoreRect);
    SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
    SDL_RenderCopy(Game::renderer, titleMessage, nullptr, &titleRect);
    SDL_RenderCopy(Game::renderer, startMessage, nullptr, &startRect);
    SDL_RenderCopy(Game::renderer, modeMessage, nullptr, &modeRect);
    SDL_RenderCopy(Game::renderer, scoreMessage, nullptr, &scoreRect);
    SDL_RenderCopy(Game::renderer, soundMenuPic, nullptr, &soundMenuRect);
    SDL_RenderCopy(Game::renderer, settingPic, nullptr, &settingRect);
}

void MainMenu::handleEvents(SDL_Event event) const{
    switch (event.type) {
        case SDL_QUIT:
            Game::isRunning = false;
            break;
        case SDL_MOUSEBUTTONDOWN:
            SDL_GetMouseState(&x_mouse, &y_mouse);
            if(pointInRect(scoreRect, x_mouse, y_mouse))
                Game::menuQueue.push_back(Score);
            else if(pointInRect(startRect, x_mouse, y_mouse)) {
                PlayMenu::init();
                Game::menuQueue.push_back(Play);
            }
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
    countdownMessage = TextureManager::LoadFont(comicFontPath, 26, "Countdown", white);
    randomMessage = TextureManager::LoadFont(comicFontPath, 26, "Random", cyan);
    infinityMessage = TextureManager::LoadFont(comicFontPath, 26, "Infinity", white);
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
                countdownMessage = TextureManager::LoadFont(comicFontPath, 26, "Countdown", cyan);
                randomMessage = TextureManager::LoadFont(comicFontPath, 26, "Random", white);
                infinityMessage = TextureManager::LoadFont(comicFontPath, 26, "Infinity", white);
            }
            else if(pointInRect(infinityRect, x_mouse, y_mouse)) {
                Game::gameMode = Infinity;
                countdownMessage = TextureManager::LoadFont(comicFontPath, 26, "Countdown", white);
                randomMessage = TextureManager::LoadFont(comicFontPath, 26, "Random", white);
                infinityMessage = TextureManager::LoadFont(comicFontPath, 26, "Infinity", cyan);
            }
            else if(pointInRect(randomRect, x_mouse, y_mouse)) {
                Game::gameMode = Random;
                countdownMessage = TextureManager::LoadFont(comicFontPath, 26, "Countdown", white);
                randomMessage = TextureManager::LoadFont(comicFontPath, 26, "Random", cyan);
                infinityMessage = TextureManager::LoadFont(comicFontPath, 26, "Infinity", white);
            }
            break;
        default:
            break;
    }
}

void SettingsMenu::init(){
    std::string redBallTheme1Path = "..\\assets\\theme1";
    redBallTheme1Path += redBallPicPath;
    std::string greenBallTheme2Path = "..\\assets\\theme2";
    greenBallTheme2Path += greenBallPicPath;
    std::string blueBallTheme3Path = "..\\assets\\theme3";
    blueBallTheme3Path += blueBallPicPath;

    setRectWithCenter(background1Rect, 112, 300, 150, 300);
    setRectWithCenter(background2Rect, 300, 300, 150, 300);
    setRectWithCenter(background3Rect, 487, 300, 150, 300);
    setRectWithCenter(ball1Rect, 150, 650, 75, 75);
    setRectWithCenter(ball2Rect, 300, 650, 75, 75);
    setRectWithCenter(ball3Rect, 450, 650, 75, 75);
    setRectWithCenter(backgroundMessageRect, 300, 100, 150, 50);
    setRectWithCenter(ballMessageRect, 300, 525, 150, 50);
    backgroundMessage = TextureManager::LoadFont(comicFontPath, 24, "Backgrounds", white);
    ballMessage = TextureManager::LoadFont(comicFontPath, 24, "Ball Texture", white);
    background1Pic = TextureManager::LoadTexture(background1Path);
    background2Pic = TextureManager::LoadTexture(background2Path);
    background3Pic = TextureManager::LoadTexture(background3Path);
    ball1Pic = TextureManager::LoadTexture(redBallTheme1Path.c_str());
    ball2Pic = TextureManager::LoadTexture(greenBallTheme2Path.c_str());
    ball3Pic = TextureManager::LoadTexture(blueBallTheme3Path.c_str());
    backPic = TextureManager::LoadTexture(backPicPath);
}

void SettingsMenu::render(){
    SDL_RenderCopy(Game::renderer, backgroundMessage, nullptr, &backgroundMessageRect);
    SDL_RenderCopy(Game::renderer, ballMessage, nullptr, &ballMessageRect);
    SDL_RenderCopy(Game::renderer, background1Pic, nullptr, &background1Rect);
    SDL_RenderCopy(Game::renderer, background2Pic, nullptr, &background2Rect);
    SDL_RenderCopy(Game::renderer, background3Pic, nullptr, &background3Rect);
    SDL_RenderCopy(Game::renderer, ball1Pic, nullptr, &ball1Rect);
    SDL_RenderCopy(Game::renderer, ball2Pic, nullptr, &ball2Rect);
    SDL_RenderCopy(Game::renderer, ball3Pic, nullptr, &ball3Rect);
    SDL_RenderCopy(Game::renderer, backPic, nullptr, &backRect);
    SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(Game::renderer, &background1Rect);
    SDL_RenderDrawRect(Game::renderer, &background2Rect);
    SDL_RenderDrawRect(Game::renderer, &background3Rect);
    SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
}

void SettingsMenu::handleEvents(SDL_Event event) const{
    switch (event.type) {
        case SDL_QUIT:
            Game::isRunning = false;
            break;
        case SDL_MOUSEBUTTONDOWN:
            SDL_GetMouseState(&x_mouse, &y_mouse);
            if(pointInRect(backRect, x_mouse, y_mouse)) {
                Game::menuQueue.pop_back();
            }
            else if(pointInRect(background1Rect, x_mouse, y_mouse)) {
                Game::background = TextureManager::LoadTexture(background1Path);
            }
            else if(pointInRect(background2Rect, x_mouse, y_mouse)) {
                Game::background = TextureManager::LoadTexture(background2Path);
            }
            else if(pointInRect(background3Rect, x_mouse, y_mouse)) {
                Game::background = TextureManager::LoadTexture(background3Path);
            }
            else if(pointInRect(ball1Rect, x_mouse, y_mouse)) {
                Game::ballTheme = Glass;
            }
            else if(pointInRect(ball2Rect, x_mouse, y_mouse)) {
                Game::ballTheme = Marble;
            }
            else if(pointInRect(ball3Rect, x_mouse, y_mouse)) {
                Game::ballTheme = Bowling;
            }
            break;
        default:
            break;
    }
}

void SoundMenu::init() {
    setRectWithCenter(theme1Rect, 100, 600, 130, 50);
    setRectWithCenter(theme2Rect, 300, 600, 150, 50);
    setRectWithCenter(theme3Rect, 500, 600, 100, 50);
    setRectWithCenter(musicRect, 300, 470, 100, 50);
    setRectWithCenter(soundBarRect, 250, 300, 200, 50);
    setRectWithCenter(soundRect,  250, 300, 200, 50);
    setRectWithCenter(speakerRect, 450, 300, 50, 50);
    setRectWithCenter(volumeMessageRect, 300, 150, 150, 70);
    volumeMessage = TextureManager::LoadFont(comicFontPath, 28, "Volume", white);
    musicMessage = TextureManager::LoadFont(comicFontPath, 28, "Music", white);
    theme1Message = TextureManager::LoadFont(comicFontPath, 24, "Undertale", white);
    theme2Message = TextureManager::LoadFont(comicFontPath, 24, "White Lady", white);
    theme3Message = TextureManager::LoadFont(comicFontPath, 24, "Suika", white);
    speakerPic = TextureManager::LoadTexture(unmutePicPath);
    backPic = TextureManager::LoadTexture(backPicPath);
    loadMusic(music1Path);
    isMute = false;
}

void SoundMenu::render(){
    SDL_RenderCopy(Game::renderer, musicMessage, nullptr, &musicRect);
    SDL_RenderCopy(Game::renderer, theme1Message, nullptr, &theme1Rect);
    SDL_RenderCopy(Game::renderer, theme2Message, nullptr, &theme2Rect);
    SDL_RenderCopy(Game::renderer, theme3Message, nullptr, &theme3Rect);
    SDL_RenderCopy(Game::renderer, volumeMessage, nullptr, &volumeMessageRect);
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
    switch (event.type) {
        case SDL_QUIT:
            Game::isRunning = false;
            break;
        case SDL_MOUSEBUTTONDOWN:
            SDL_GetMouseState(&x_mouse, &y_mouse);
            if(pointInRect(soundRect, x_mouse, y_mouse)) {
                PauseMenu::soundBarRect.w = x_mouse - soundRect.x;
                soundBarRect.w = x_mouse - soundRect.x;
                prevVolume = soundBarRect.w;
                Mix_VolumeMusic((int)((x_mouse - soundRect.x)*128.0/soundRect.w));
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
                    PauseMenu::speakerPic = TextureManager::LoadTexture(unmutePicPath);
                    speakerPic = TextureManager::LoadTexture(unmutePicPath);
                    isMute = false;
                    soundBarRect.w = prevVolume;
                    Mix_ResumeMusic();
                    Mix_VolumeMusic((int)((soundBarRect.w)*128.0/soundRect.w));
                }
                else{
                    PauseMenu::speakerPic = TextureManager::LoadTexture(mutePicPath);
                    speakerPic = TextureManager::LoadTexture(mutePicPath);
                    isMute = true;
                    prevVolume = soundBarRect.w;
                    PauseMenu::soundBarRect.w = 0;
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
    if(isMute)
        Mix_PauseMusic();
}

void ScoreMenu::setScores(const char* path) {
    int max_char = 10;
    std::string name;
    scores = FileManager::getTopTen(path);
    for(int i=0; i<std::min((int)scores.size(), 10); i++){
        name = scores[i].second;
        if(scores[i].second.size()>10) name = scores[i].second.substr(0, max_char) + "...";
        setRectWithCenter(scoresRect[i], 450, 50*(i+6), (int)std::to_string(scores[i].first).size()*15, 50);
        scoresMessage[i] = TextureManager::LoadFont(comicFontPath, 24, std::to_string(scores[i].first).c_str(), white);
        setRectWithCorner(namesRect[i], 100, 50 * (i + 6) - 25, (int)(name.size() + 2) * 15, 50);
        namesMessage[i] = TextureManager::LoadFont(comicFontPath, 24, (std::to_string(i + 1) + ". " + name).c_str(), white);
    }
}

void ScoreMenu::renderScores(){
    for(int i=0; i<std::min((int)scores.size(), 10); i++){
        SDL_RenderCopy(Game::renderer, scoresMessage[i], nullptr, &scoresRect[i]);
        SDL_RenderCopy(Game::renderer, namesMessage[i], nullptr, &namesRect[i]);
    }
}

void ScoreMenu::init(){
    setRectWithCenter(scoreRect, 300, 100, 250, 70);
    setRectWithCenter(infinityRect, 120, 200, 100, 50);
    setRectWithCenter(countdownRect, 300, 200, 150, 50);
    setRectWithCenter(randomRect, 480, 200, 100, 50);
    infinityMessage = TextureManager::LoadFont(comicFontPath, 24, "infinity", white);
    randomMessage = TextureManager::LoadFont(comicFontPath, 24, "random", white);
    countdownMessage = TextureManager::LoadFont(comicFontPath, 24, "countdown", cyan);
    scoreMessage = TextureManager::LoadFont(comicFontPath, 28, "Highest Scores", white);
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
                infinityMessage = TextureManager::LoadFont(comicFontPath, 24, "infinity", white);
                randomMessage = TextureManager::LoadFont(comicFontPath, 24, "random", cyan);
                countdownMessage = TextureManager::LoadFont(comicFontPath, 24, "countdown", white);
            }
            else if(pointInRect(infinityRect, x_mouse, y_mouse)){
                setScores(infinityScoresPath);
                infinityMessage = TextureManager::LoadFont(comicFontPath, 24, "infinity", cyan);
                randomMessage = TextureManager::LoadFont(comicFontPath, 24, "random", white);
                countdownMessage = TextureManager::LoadFont(comicFontPath, 24, "countdown", white);            }
            else if(pointInRect(countdownRect, x_mouse, y_mouse)){
                setScores(countdownScoresPath);
                infinityMessage = TextureManager::LoadFont(comicFontPath, 24, "infinity", white);
                randomMessage = TextureManager::LoadFont(comicFontPath, 24, "random", white);
                countdownMessage = TextureManager::LoadFont(comicFontPath, 24, "countdown", cyan);
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
    angle = angle > 70 ? 70 : angle;
    if(xMouse <= cannonRect.x + cannonRect.w/2) {
        angle *= -1;
    }
}

void PlayMenu::init(){
    generateRandomMap();
    map.LoadMap();
    setRectWithCenter(cannonRect, 300, 750, 75, 115);
    setRectWithCenter(barRect, 300, 630, 600, 5);
    setRectWithCenter(messageRect, 300, 350, 300, 80);
    setRectWithCenter(pauseMenuRect, 50, 750, 50, 50);
    cannonPic = TextureManager::LoadTexture(cannonPicPath);
    pauseMenuPic = TextureManager::LoadTexture(pausePicPath);
    textMessage = TextureManager::LoadFont(comicFontPath, 28, "Game Over!", white);
    backPic = TextureManager::LoadTexture(backPicPath);
    lastTick = SDL_GetTicks();
}

void PlayMenu::render() {
    SDL_RenderFillRect(Game::renderer, &barRect);
    map.render();
    SDL_RenderCopy(Game::renderer, pauseMenuPic, nullptr, &pauseMenuRect);
    SDL_RenderCopy(Game::renderer, backPic, nullptr, &backRect);
    SDL_RenderCopyEx(Game::renderer, cannonPic, nullptr, &cannonRect, angle, nullptr, SDL_FLIP_NONE);
    Ball nextBall(Map::ballQueue.front(), 300, 750, 0, 0);
    Ball afterNextBall(Map::ballQueue.back(), 200, 750, 0, 0);
    nextBall.render();
    afterNextBall.render();
}

void PlayMenu::handleEvents(SDL_Event event) {
    SDL_GetMouseState(&x_mouse, &y_mouse);
    keyStates = SDL_GetKeyboardState(nullptr);
    setAngle(x_mouse, y_mouse);
    switch (event.type) {
        case SDL_QUIT:
            Game::isRunning = false;
            break;
        case SDL_MOUSEBUTTONDOWN:
            if(pointInRect(backRect, x_mouse, y_mouse)){
                map.destroy();
                Game::menuQueue.pop_back();
                Game::score = 0;
            }
            else if(pointInRect(pauseMenuRect, x_mouse, y_mouse)){
                Game::menuQueue.emplace_back(Pause);
            }
            else if(map.shootingBall.empty()){
                map.addShootingBall(angle, cannonRect);
                lastTick = SDL_GetTicks();
            }
            break;
        case SDL_KEYDOWN:
            if(keyStates[SDL_SCANCODE_T]){
                Map::ballQueue.reverse();
            }
            break;
        default:
            break;
    }
}

void PlayMenu::update(){
    map.update();
    if(map.passedTheBar(barRect.y + barRect.h/2)){
        SDL_RenderCopy(Game::renderer, textMessage, nullptr, &messageRect);
        SDL_RenderPresent(Game::renderer);
        map.destroy();
        SDL_Delay(2000);
        if(!Game::menuQueue.empty())
            Game::menuQueue.pop_back();
        Game::menuQueue.push_back(End);
    }
}

void EndMenu::init() {
    backspace=false; del=false; left=false; right=false; redirect=false;
    index = 0;
    topText = "It's over!";
    text="";
    setRectWithCorner(fullTextRect, 50, 300, 21*20, 50);
    setRectWithCorner(enterNameRect, 50, 250, 220, 50);
    setRectWithCenter(topRect, 300, 100, (int)topText.length()*25, 75);
    setRectWithCorner(tickRect, 500, 300, 50, 50);
    setRectWithCorner(warningRect, 50, 450, 500, 40);
    tickPic = TextureManager::LoadTexture("..\\assets\\tick_icon.png");
    topMessage = TextureManager::LoadFont(comicFontPath, 28, topText.c_str(), cyan);
    enterNameMessage = TextureManager::LoadFont(comicFontPath, 28, "Enter Your Name:", white);
    warningMessage = TextureManager::LoadFont(comicFontPath, 20, "*Number of letters should be below 5 and over 19",
                                                {255, 0, 0});
    backPic = TextureManager::LoadTexture(backPicPath);
    endMode = Idle;
}

void EndMenu::render(){
    SDL_RenderCopy(Game::renderer, tickPic, nullptr, &tickRect);
    SDL_RenderCopy(Game::renderer, backPic, nullptr, &backRect);
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
        SDL_RenderClear(Game::renderer);
        SDL_RenderCopy(Game::renderer, Game::background, nullptr, &Game::backgroundRect);
        if(text.length()>=5) {
            setRectWithCenter(redirectRect, 300, 400, 400, 50);
            redirectMessage = TextureManager::LoadFont(comicFontPath, 28, "Your Score Was Stored :)",
                                                       white);
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
            setRectWithCenter(redirectRect, 300, 400, 400, 50);
            redirectMessage = TextureManager::LoadFont(comicFontPath, 28, "Your Score Was not Stored :(",
                                                       white);
        }
        SDL_RenderCopy(Game::renderer, redirectMessage, nullptr, &redirectRect);
        SDL_RenderPresent(Game::renderer);
        SDL_Delay(1500);
        Game::menuQueue.pop_back();
        Game::score = 0;
        PlayMenu::map.destroy();
        init();
    }
}

void EndMenu::handleEvents(SDL_Event event) {
    keyStates = SDL_GetKeyboardState(nullptr);
    switch (event.type) {
        case SDL_QUIT:
            Game::isRunning = false;
            break;
        case SDL_MOUSEBUTTONDOWN:
            SDL_GetMouseState(&x_mouse, &y_mouse);
            if(pointInRect(backRect, x_mouse, y_mouse) || pointInRect(tickRect, x_mouse, y_mouse)) {
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
                    if(!text.empty())
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
        else if((keyStates[SDL_SCANCODE_C] && SDL_GetModState()) && KMOD_CTRL)
            SDL_SetClipboardText(text.c_str());
        else if((keyStates[SDL_SCANCODE_V] && SDL_GetModState()) && KMOD_CTRL) {
            text = SDL_GetClipboardText();
            text = text.substr(0, 20);
            index = (int)text.length();
        }
        if(text.length() >= 0) {
            textCpy = text;
            textCpy.insert(index, "_");
            setRectWithCorner(textRect, 50 + 5, 300, (int)textCpy.length() * 20, 50);
            textMessage = TextureManager::LoadFont(comicFontPath, 26, textCpy.c_str(), white);
        }
    }
    else if(endMode == Idle){
        if(text.length() >= 0) {
            setRectWithCorner(textRect, 50 + 5, 300, (int)text.length() * 20, 50);
            textMessage = TextureManager::LoadFont(comicFontPath, 26, text.c_str(), white);
        }
    }
}

std::string EndMenu::makeValid(const std::string &str) {
    int rightInd, leftInd;
    bool flag=true;
    for(int i=0; i<str.length() && flag; i++)
        if(str[i]!=' '){
            flag = false;
            leftInd = i;
        }
    flag = true;
    for(int i=(int)(str.length()-1); i>=0 && flag; i--)
        if(str[i]!=' '){
            flag = false;
            rightInd = i;
        }
    if(rightInd<leftInd)
        return "";
    return str.substr(leftInd, rightInd-leftInd+1);

}

void PauseMenu::init(){

    //Pause
    setRectWithCenter(pauseMessageRect, 300, 70, 230, 75);
    pauseMessage = TextureManager::LoadFont(comicFontPath, 30, "Pause Menu", white);

    //Music related :
    setRectWithCenter(musicRect, 300, 520, 80, 50);
    setRectWithCenter(theme1Rect, 450, 580, 130, 50);
    setRectWithCenter(theme2Rect, 450, 650, 150, 50);
    setRectWithCenter(theme3Rect, 450, 720, 100, 50);
    setRectWithCenter(soundBarRect, 200, 610, 200, 50);
    setRectWithCenter(soundRect,  200, 610, 200, 50);
    setRectWithCenter(speakerRect, 200, 690, 50, 50);
    musicMessage = TextureManager::LoadFont(comicFontPath, 26, "Music", white);
    theme1Message = TextureManager::LoadFont(comicFontPath, 24, "Undertale", white);
    theme2Message = TextureManager::LoadFont(comicFontPath, 24, "White Lady", white);
    theme3Message = TextureManager::LoadFont(comicFontPath, 24, "Suika", white);
    speakerPic = TextureManager::LoadTexture(unmutePicPath);


    //Background related :
    setRectWithCenter(backgroundMessageRect, 300, 150, 160, 50);
    backgroundMessage = TextureManager::LoadFont(comicFontPath, 26, "Backgrounds", white);
    setRectWithCenter(background1Rect, 112, 340, 150, 250);
    setRectWithCenter(background2Rect, 300, 340, 150, 250);
    setRectWithCenter(background3Rect, 487, 340, 150, 250);
    background1Pic = TextureManager::LoadTexture(background1Path);
    background2Pic = TextureManager::LoadTexture(background2Path);
    background3Pic = TextureManager::LoadTexture(background3Path);

    backPic = TextureManager::LoadTexture(backPicPath);
}

void PauseMenu::render(){
    SDL_RenderCopy(Game::renderer, pauseMessage, nullptr, &pauseMessageRect);
    SDL_RenderCopy(Game::renderer, backgroundMessage, nullptr, &backgroundMessageRect);
    SDL_RenderCopy(Game::renderer, pauseMessage, nullptr, &pauseMessageRect);
    SDL_RenderCopy(Game::renderer, background1Pic, nullptr, &background1Rect);
    SDL_RenderCopy(Game::renderer, background2Pic, nullptr, &background2Rect);
    SDL_RenderCopy(Game::renderer, background3Pic, nullptr, &background3Rect);
    SDL_RenderCopy(Game::renderer, backPic, nullptr, &backRect);

    SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(Game::renderer, &background1Rect);
    SDL_RenderDrawRect(Game::renderer, &background2Rect);
    SDL_RenderDrawRect(Game::renderer, &background3Rect);
    SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
    SDL_RenderCopy(Game::renderer, musicMessage, nullptr, &musicRect);
    SDL_RenderCopy(Game::renderer, theme1Message, nullptr, &theme1Rect);
    SDL_RenderCopy(Game::renderer, theme2Message, nullptr, &theme2Rect);
    SDL_RenderCopy(Game::renderer, theme3Message, nullptr, &theme3Rect);
    SDL_RenderCopy(Game::renderer, speakerPic, nullptr, &speakerRect);
    SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(Game::renderer, &theme1Rect);
    SDL_RenderDrawRect(Game::renderer, &theme2Rect);
    SDL_RenderDrawRect(Game::renderer, &theme3Rect);
    SDL_RenderDrawRect(Game::renderer, &soundRect);
    SDL_SetRenderDrawColor(Game::renderer, 0, 255, 255, 255);
    SDL_RenderFillRect(Game::renderer, &soundBarRect);
    SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
}

void PauseMenu::handleEvents(SDL_Event event) {
    switch (event.type) {
        case SDL_QUIT:
            Game::isRunning = false;
            break;
        case SDL_MOUSEBUTTONDOWN:
            SDL_GetMouseState(&x_mouse, &y_mouse);
            if(pointInRect(backRect, x_mouse, y_mouse)){
                Game::menuQueue.pop_back();
            }
            else if(pointInRect(soundRect, x_mouse, y_mouse)) {
                soundBarRect.w = x_mouse - soundRect.x;
                SoundMenu::prevVolume = soundBarRect.w;
                SoundMenu::soundBarRect.w = x_mouse - soundRect.x;
                Mix_VolumeMusic((int)((x_mouse - soundRect.x)*128.0/soundRect.w));
            }
            else if(pointInRect(background1Rect, x_mouse, y_mouse)) {
        Game::background = TextureManager::LoadTexture(background1Path);
    }
            else if(pointInRect(background2Rect, x_mouse, y_mouse)) {
        Game::background = TextureManager::LoadTexture(background2Path);
    }
            else if(pointInRect(background3Rect, x_mouse, y_mouse)) {
        Game::background = TextureManager::LoadTexture(background3Path);
    }
            else if(pointInRect(speakerRect, x_mouse, y_mouse)) {
                if(SoundMenu::isMute){
                    SoundMenu::speakerPic = TextureManager::LoadTexture(unmutePicPath);
                    speakerPic = TextureManager::LoadTexture(unmutePicPath);
                    SoundMenu::isMute = false;
                    soundBarRect.w = SoundMenu::prevVolume;
                    Mix_ResumeMusic();
                    Mix_VolumeMusic((int)((soundBarRect.w)*128.0/soundRect.w));
                }
                else{
                    SoundMenu::speakerPic = TextureManager::LoadTexture(mutePicPath);
                    speakerPic = TextureManager::LoadTexture(mutePicPath);
                    SoundMenu::isMute = true;
                    SoundMenu::soundBarRect.w = 0;
                    soundBarRect.w = 0;
                    Mix_PauseMusic();
                }
            }
            else if(pointInRect(theme1Rect, x_mouse, y_mouse)) {
                SoundMenu::loadMusic(music1Path);
            }
            else if(pointInRect(theme2Rect, x_mouse, y_mouse)) {
                SoundMenu::loadMusic(music2Path);
            }
            else if(pointInRect(theme3Rect, x_mouse, y_mouse)) {
                SoundMenu::loadMusic(music3Path);
            }
            break;
    }
}