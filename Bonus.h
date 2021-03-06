#ifndef BONUS_H
#define BONUS_H


#include <SFML/Graphics.hpp>
#include "common.h"
using namespace std;
using namespace sf;

class Bonus : public Drawable{
private:
    Sprite sprite;
    const Texture* texture;

    float* velocity;
    int duration;

    void draw(RenderTarget& target, RenderStates states) const override;

public:
    Bonus(const Texture& texture, float position, const RenderWindow& window, float* velocity);
    void animate(float delta, const RenderWindow& window);
    inline bool collision(const FloatRect& box) const { return sprite.getGlobalBounds().intersects(box); }
    inline bool notVisibleAnymore() { return sprite.getPosition().x <= 0; }
    inline int getDuration() { return duration; }
};


#endif //BONUS_H
