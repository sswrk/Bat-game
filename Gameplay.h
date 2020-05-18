#ifndef Gameplay_h
#define Gameplay_h

#include <fstream>
#include <vector>
#include "Bat.h"
#include "Obstacle.h"
#include "Grass.h"
#include "Bonus.h"
#include "Observer.h"
#include "Misc.h"

using namespace std;
using namespace sf;

class Gameplay : public Observer{
private:
    RenderWindow window;
    Clock clock;
    Time time;
    Event event;

    bool lost = false;

    float* velocity;

    int bonus_rarity;

    Texture bat_texture;
    Bat* bat;
    Texture obstacle_texture;
    vector<Obstacle> obstacles;
    Texture grass_texture;
    vector<Grass> grass;
    Texture moon_texture;
    Sprite moon;
    Texture background_texture;
    Sprite background;
    Texture bonus_texture;
    Bonus * bonus;

    Font text_font;
    Text conclusion;
    Text menu_text;
    Text current_score_text;
    Text high_score_text;
    int high_score;
    ifstream input_file;
    ofstream output_file;

    bool paused = true;
public:
    void setScore();
    void generateBonus();
	Gameplay(float velocity);
	void run();
	void updateScore() override;
	void deleteBonus() override;
    void loadObjects();
    void loadTexts();
    void loadFile();

    void restart();
    void animateObjects();
    void drawObjects();
};

#endif