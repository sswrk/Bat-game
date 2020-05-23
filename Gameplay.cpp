#include "Gameplay.h"
#include <iostream>

Gameplay::Gameplay(){
    window.create(VideoMode(window_width, window_height), "Bat Game", Style::Close);
    window.setFramerateLimit(120);

    loadObjects();
    loadTexts();
    loadFile();
}

void Gameplay::run(){
    while(window.isOpen()){
        time = clock.restart();
        window.clear(Color::Black);
        while(window.pollEvent(event))
            handleEvent();
        if(!paused)
            animateObjects();
        drawObjects();
        window.display();
    }
    delete bonus;
    delete bat;
}

void Gameplay::handleEvent(){
    if(event.type == Event::Closed)
        window.close();
    else if(event.type == Event::KeyPressed && event.key.code == Keyboard::Space && lost)
        restart();
    else if(event.type == Event::KeyPressed && event.key.code == Keyboard::Space)
        if(!paused)
            bat->jump();
        else paused = false;
    else if(event.type == Event::KeyPressed && event.key.code == Keyboard::P && !bat->isDead())
        paused = !paused;
}

void Gameplay::setScore() {
    current_score_text.setString("Wynik: " + to_string(bat->getScore()));
    if(bat->getScore() > high_score){
        high_score = bat->getScore();
        output_file.open("score.txt");
        output_file << high_score;
        output_file.close();
        high_score_text.setString("Rekord: " + to_string(high_score));
    }
}

void Gameplay::generateBonus() {
    if(bonus != nullptr && bonus->notVisibleAnymore())
        deleteBonus();
    if(bonus == nullptr && !bat->hasBonus())
        bonus = new Bonus(bonus_texture, 1.5f*objects_distance + static_cast<float>(window_width)/2.0f, window, &velocity);
}

void Gameplay::restart(){
    bat->reset(window);
    obstacles.clear();
    loadObstacles();
    grass.clear();
    loadGrass();
    deleteBonus();
    lost = false;
    paused = false;
}

void Gameplay::animateObjects(){
    for(auto& g: grass) g.animate(time.asSeconds(), window);
    for(auto& obstacle : obstacles) obstacle.animate(time.asSeconds(), window);
    if(bonus != nullptr) bonus->animate(time.asSeconds(), window);
    bat->animate(time.asSeconds(), window, obstacles, bonus);
    if(bat->isDead()){
        paused = true;
        lost = true;
    }
}

void Gameplay::drawObjects(){
    window.draw(background);
    window.draw(moon);
    window.draw(*bat);
    for(auto& obstacle : obstacles) window.draw(obstacle);
    for(auto& g : grass) window.draw(g);
    if(bonus != nullptr) window.draw(*bonus);
    if(paused)
        window.draw(menu_text);
    if(lost) {
        conclusion.setString("Oj! Wynik: "+to_string(bat->getScore()));
        window.draw(conclusion);
    }
    else {
        window.draw(current_score_text);
        window.draw(high_score_text);
    }
}

void Gameplay::updateScore() {
    setScore();
    if((int)random(1, 100)%bonus_rarity==0) generateBonus();
}

void Gameplay::deleteBonus(){
    delete bonus;
    bonus = nullptr;
}

void Gameplay::loadObjects(){
    loadBat();
    loadGrass();
    loadObstacles();
    loadBackground();
    loadBonus();
}

void Gameplay::loadBat() {
    bat_texture.loadFromFile("Resources/Bat.png");
    bat = new Bat(bat_texture, window, &velocity);
    Observer::setBat(bat);
}

void Gameplay::loadGrass(){
    grass_texture.loadFromFile("Resources/Grass.png");
    grass.emplace_back(grass_texture, 0.0f, window, &velocity);
    grass.emplace_back(grass_texture, window_width, window, &velocity);
}

void Gameplay::loadObstacles() {
    obstacle_texture.loadFromFile("Resources/Obstacle.png");
    for(int i=0; i<3; i++){
        Obstacle obstacle(obstacle_texture, static_cast<float>((i + 2) * objects_distance), window, &velocity);
        obstacles.push_back(obstacle);
    }
}

void Gameplay::loadBackground() {
    background_texture.loadFromFile("Resources/Background.png");
    background.setTexture(background_texture);
    background.setPosition(0, 0);

    moon_texture.loadFromFile("Resources/Moon.png");
    moon.setTexture(moon_texture);
    moon.setPosition( 300, 10);
}

void Gameplay::loadBonus() {
    bonus_texture.loadFromFile("Resources/Bonus.png");
    bonus = nullptr;
}

void Gameplay::loadTexts(){
    text_font.loadFromFile("Resources/Font.ttf");

    loadScoreText();
    loadMenuText();
    loadConclusionText();
}

void Gameplay::loadScoreText(){
    current_score_text.setFont(text_font);
    current_score_text.setPosition(20, 20);
    current_score_text.setCharacterSize(30);
    current_score_text.setFillColor(Color::White);
    current_score_text.setString("Wynik: 0");
}

void Gameplay::loadMenuText() {
    menu_text.setFont(text_font);
    menu_text.setCharacterSize(30);
    menu_text.setFillColor(Color::White);
    menu_text.setString("Spacja - Graj  |  P - Pauza");
    menu_text.setOrigin(
            menu_text.getGlobalBounds().left +(menu_text.getGlobalBounds().width / 2.0f),
            menu_text.getGlobalBounds().top +(menu_text.getGlobalBounds().height / 2.0f)
    );
    menu_text.setPosition((Vector2f)(window.getSize()) / 2.0f);
    menu_text.move(0.0, 50.0f);
}

void Gameplay::loadConclusionText(){
    conclusion = menu_text;
    conclusion.setFont(text_font);
    conclusion.setCharacterSize(40);
    conclusion.setFillColor(Color::White);
    conclusion.setOrigin(
            conclusion.getGlobalBounds().left +(conclusion.getGlobalBounds().width / 2.0f),
            conclusion.getGlobalBounds().top +(conclusion.getGlobalBounds().height / 2.0f)
    );
    conclusion.setPosition((Vector2f)(window.getSize()) / 2.0f);
    conclusion.move(-100.0, -70.0);
}

void Gameplay::loadFile() {
    input_file.open("score.txt");
    if (!input_file) {
        output_file.open("score.txt");
        output_file << 0;
        output_file.close();
        output_file.open("score.txt");
    }
    input_file >> high_score;
    input_file.close();
    high_score_text.setFont(text_font);
    high_score_text.setPosition(20, 50);
    high_score_text.setCharacterSize(24);
    high_score_text.setFillColor(Color::White);
    high_score_text.setString("Rekord: " + to_string(high_score));
}