#ifndef GRASS_H
#define GRASS_H

#include <SFML/Graphics.hpp>
#include "common.h"

using namespace std;
using namespace sf;

class Grass : public Drawable{
private:
    Sprite sprite;
    const Texture* texture;
    float* velocity;
    float position_original;
    void draw(RenderTarget& target, RenderStates states) const override;
public:
    Grass(const Texture& texture, const float position, const RenderWindow& window, float* velocity);
    void animate(float delta, const RenderWindow& window);
};

#endif //GRASS_H
