#ifndef Obstacle_h
#define Obstacle_h

#include <SFML/Graphics.hpp>
#include "common.h"

using namespace std;
using namespace sf;

class Obstacle : public Drawable{
private:
    Sprite top;
    Sprite bottom;
    const Texture* texture;
    float* velocity;
    float position_original;
    bool passed = false;
    void draw(RenderTarget& target, RenderStates states) const override;
public:
	Obstacle(const Texture& texture, float position, const RenderWindow& window, float* velocity);
	void animate(float delta, const RenderWindow& window);
	inline bool collision(const FloatRect& box) const { return bottom.getGlobalBounds().intersects(box) || top.getGlobalBounds().intersects(box); };
	inline float getPosition() const { return bottom.getPosition().x; };
	bool isPassed() { return passed; }
	void setPassed() { passed = true; }
};

#endif