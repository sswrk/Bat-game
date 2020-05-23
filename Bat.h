#ifndef Bat_h
#define Bat_h

#include <vector>
#include <cmath>

#include "Obstacle.h"
#include "Bonus.h"
#include "common.h"

using namespace std;
using namespace sf;

class Bat : public Drawable{
private:
    Sprite sprite;
    Texture* texture;
    FloatRect box;

    float* velocity;
    Vector2f vector_force;
    float gravity = 1000.0f;
    float jump_force =  (-500.0f);
    float rotation_velocity = 60.0f;
    float min_rotation = 60.0f;
    float max_rotation = 330.0f;

    class Observer* observer{};

    int bonus_passes;
    int current_score = 0;

    bool dead = false;

    inline void draw(RenderTarget& target, RenderStates states) const override { target.draw(sprite); }
    void checkIfBonusAcquired(Bonus* bonus);
    void checkIfObstaclePassed(vector<Obstacle>& obstacles);
    void checkCollisions(vector<Obstacle>& obstacles, const RenderWindow& window);
    void notifyScoreChanged();
    void notifyBonusAcquired();

public:
	Bat(Texture& texture, const RenderWindow& window, float* velocity);
    void animate(float delta, const RenderWindow& window, vector<Obstacle>& obstacles, Bonus*& bonus);
    void jump();
    void reset(const RenderWindow& window);
    inline void addObserver(Observer* observer) { this->observer = observer; }
    inline int getScore() const { return current_score; }
    inline bool hasBonus() { return bonus_passes!=0; }
    inline bool isDead() { return dead; }
};

#endif