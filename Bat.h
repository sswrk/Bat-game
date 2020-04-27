#ifndef Bat_h
#define Bat_h

#include "Obstacle.h"
#include <vector>
#include <math.h>

using namespace std;
using namespace sf;

class Bat : public Drawable{
private:
    Sprite sprite;
    Vector2f vecf;
    FloatRect box;
    Texture* texture;
    bool dead = false;
    float velocity;
    float downf = 1000.0f;
    float jumpf =  (-500.0f);
    float rotation_velocity = 60.0f;
    int cscore = 0;
    inline void draw(RenderTarget& target, RenderStates states) const { target.draw(sprite); }
public:
	Bat(Texture& texture, const RenderWindow& window, float velocity);
    void animate(const float delta, const RenderWindow& window, vector<Obstacle>& obstacles);
    void jump();
    inline int getScore() const { return cscore; }
	void kill(const RenderWindow& window);
    bool isDead() { return dead; }
};

#endif