#include "Grass.h"

Grass::Grass(const Texture& texture, const float position, const RenderWindow& window, float* velocity)
        : velocity(velocity), texture(&texture), position_original(550){

    sprite.setTexture(texture);
    sprite.setPosition(position, 570);
}

void Grass::animate(const float delta, const RenderWindow& window){
    sprite.move(-*velocity * delta, 0.0f);
    if (sprite.getPosition().x <= -550)
        sprite.setPosition(position_original, 570);
}

void Grass::draw(RenderTarget& target, RenderStates states) const{
    target.draw(sprite);
}

