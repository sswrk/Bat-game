#ifndef HELICOPTER_GRASS_H
#define HELICOPTER_GRASS_H

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Grass : public Drawable{
private:
    Sprite sprite;
    const Texture* texture;
    float velocity;
    float position_original;
    void draw(RenderTarget& target, RenderStates states) const;
public:
    Grass(const Texture& texture, const float position, const RenderWindow& window, float velocity);
    void animate(const float delta, const RenderWindow& window);
};

#endif //HELICOPTER_GRASS_H
