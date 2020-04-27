#ifndef Obstacle_h
#define Obstacle_h

#include <SFML/Graphics.hpp>
#include "Misc.h"

using namespace std;
using namespace sf;

class Obstacle : public Drawable{
private:
    Sprite top;
    Sprite bottom;
    const Texture* texture;
    float velocity;
    float position_orig;
    void draw(RenderTarget& target, RenderStates states) const;
    bool passed = false;
public:
	Obstacle(const Texture& texture, const float position, const RenderWindow& window, float velocity);
	void animate(const float delta, const RenderWindow& window);
	inline bool collision(const FloatRect& box) const { return bottom.getGlobalBounds().intersects(box) || top.getGlobalBounds().intersects(box); };
	inline const float getPosition() const { return bottom.getPosition().x; };
	bool isPassed() { return passed; }
	void setPassed() { passed = true; }
};

#endif