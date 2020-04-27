#include "Gameplay.h"

#include <iostream>

Gameplay::Gameplay(float velocity){
	window.create(VideoMode(550, 600), "Bat Game", Style::Close);
	window.setFramerateLimit(120);

    this->velocity = velocity;

	bat_texture.loadFromFile("Resources/Bat.png");
	bat = new Bat(bat_texture, window, velocity);

	grass_texture.loadFromFile("Resources/Grass.png");
	grass.emplace_back(grass_texture, 0.0f, window, velocity);
	grass.emplace_back(grass_texture, 550.0f, window, velocity);

	obstacle_texture.loadFromFile("Resources/Obstacle.png");
	for(int i=0; i<3; i++){
	    Obstacle obstacle(obstacle_texture, (float)((i + 2) * 400), window, velocity);
        obstacles.push_back(obstacle);
    }

	background_texture.loadFromFile("Resources/Background.png");
	background.setTexture(background_texture);
	background.setPosition(0, 0);

	moon_texture.loadFromFile("Resources/Moon.png");
	moon.setTexture(moon_texture);
	moon.setPosition( 300, 10);

	text_font.loadFromFile("Resources/Font.ttf");
	cscore_text.setFont(text_font);
    cscore_text.setPosition(20, 20);
    cscore_text.setCharacterSize(30);
    cscore_text.setFillColor(Color::White);
    cscore_text.setString("Wynik: 0");

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

    conclusion.setFont(text_font);
    conclusion.setCharacterSize(40);
    conclusion.setFillColor(Color::White);
    conclusion.setOrigin(
            conclusion.getGlobalBounds().left +(conclusion.getGlobalBounds().width / 2.0f),
            conclusion.getGlobalBounds().top +(conclusion.getGlobalBounds().height / 2.0f)
    );
    conclusion.setPosition((Vector2f)(window.getSize()) / 2.0f);
    conclusion.move(-100.0, -70.0);

    input_file.open("score.txt");
    if(!input_file){
        output_file.open("score.txt");
        output_file<<0;
        output_file.close();
        output_file.open("score.txt");
    }
    input_file>>hscore;
    input_file.close();
	hscore_text.setFont(text_font);
	hscore_text.setPosition(20, 50);
	hscore_text.setCharacterSize(24);
	hscore_text.setFillColor(Color::White);
	hscore_text.setString("Rekord: " + to_string(hscore));
}

void Gameplay::run(){
	while(window.isOpen()){
		time = clock.restart();
        window.clear(Color::Black);
		while(window.pollEvent(event))
			if(event.type == Event::Closed)
				window.close();
			else if(event.type == Event::KeyPressed && event.key.code == Keyboard::Space && lost == true){
                bat->kill(window);
                obstacles.clear();
                for(int i=0; i<3; i++){
                    Obstacle obstacle(obstacle_texture, (float)((i + 2) * 400), window, velocity);
                    obstacles.push_back(obstacle);
                }
                grass.clear();
                grass.emplace_back(grass_texture, 0.0f, window, velocity);
                grass.emplace_back(grass_texture, 550.0f, window, velocity);
                lost = false;
                paused = false;
			}
			else if(event.type == Event::KeyPressed && event.key.code == Keyboard::Space)
                if(!paused)
                    bat->jump();
                else paused = false;
            else if(event.type == Event::KeyPressed && event.key.code == Keyboard::P)
                if(!paused)
                    paused = true;
                else paused = false;

		if(!paused){
		    for(auto& g: grass) g.animate(time.asSeconds(), window);
			for(auto& obstacle : obstacles) obstacle.animate(time.asSeconds(), window);
			bat->animate(time.asSeconds(), window, obstacles);
			if(bat->isDead()){
                paused = true;
                lost = true;
			}
            cscore_text.setString("Wynik: " + to_string(bat->getScore()));
            if(bat->getScore()>hscore){
                hscore = bat->getScore();
                output_file.open("score.txt");
                output_file<<hscore;
                output_file.close();
                hscore_text.setString("Rekord: " + to_string(hscore));
            }
		}
		window.draw(background);
		window.draw(moon);
		window.draw(*bat);
		for(auto& obstacle : obstacles) window.draw(obstacle);
        for(auto& g : grass) window.draw(g);
		if(paused)
			window.draw(menu_text);
		if(lost) {
            conclusion.setString("Oj! Wynik: "+to_string(bat->getScore()));
            window.draw(conclusion);
        }
		else {
            window.draw(cscore_text);
            window.draw(hscore_text);
        }
		window.display();
	}
	delete bat;
}