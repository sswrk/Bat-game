#ifndef Gameplay_h
#define Gameplay_h

#include <fstream>
#include <vector>
#include "Bat.h"
#include "Obstacle.h"
#include "Grass.h"
#include "Bonus.h"
#include "Observer.h"
#include "common.h"

using namespace std;
using namespace sf;

class Gameplay : public Observer{
public:
    Gameplay();
    void run();
private:
    RenderWindow window;
    Clock clock;
    Time time;
    Event event{};

    float velocity = 255.0f;

    bool lost = false;

    Texture bat_texture;
    Bat* bat{};
    Texture obstacle_texture;
    vector<Obstacle> obstacles;
    Texture grass_texture;
    vector<Grass> grass;
    Texture moon_texture;
    Sprite moon;
    Texture background_texture;
    Sprite background;
    Texture bonus_texture;
    Bonus * bonus{};

    Font text_font;
    Text conclusion;
    Text menu_text;
    Text current_score_text;
    Text high_score_text;
    int high_score{};
    ifstream input_file;
    ofstream output_file;

    bool paused = true;

    void setScore();
    void generateBonus();
    void updateScore() override;
    void deleteBonus() override;
    void loadObjects();
    void loadBat();
    void loadGrass();
    void loadObstacles();
    void loadBackground();
    void loadBonus();
    void loadTexts();
    void loadScoreText();
    void loadMenuText();
    void loadConclusionText();
    void loadFile();
    void restart();
    void animateObjects();
    void drawObjects();
    void handleEvent();
};

#endif