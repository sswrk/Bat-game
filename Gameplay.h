#ifndef Gameplay_h
#define Gameplay_h

#include <fstream>
#include <vector>
#include "Bat.h"
#include "Obstacle.h"
#include "Grass.h"

using namespace std;
using namespace sf;

class Gameplay{
private:
    RenderWindow window;
    Clock clock;
    Time time;
    Event event;

    bool lost = false;

    float velocity;

    Texture bat_texture;
    Bat * bat;
    Texture obstacle_texture;
    vector<Obstacle> obstacles;
    Texture grass_texture;
    vector<Grass> grass;
    Texture moon_texture;
    Sprite moon;
    Texture background_texture;
    Sprite background;

    Font text_font;
    Text conclusion;
    Text menu_text;
    Text cscore_text;
    Text hscore_text;
    int hscore;
    ifstream input_file;
    ofstream output_file;

    bool paused = true;
public:
	Gameplay(float velocity);
	void run();
};

#endif