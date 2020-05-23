#include "Grass.h"

Grass::Grass(const Texture& texture, const float position, const RenderWindow& window, float* velocity)
: velocity(velocity), texture(&texture), position_original(window_width){

    sprite.setTexture(texture);
    sprite.setPosition(position, 570);
}

void Grass::animate(const float delta, const RenderWindow& window){
    sprite.move(-*velocity * delta, 0.0f);
    if (sprite.getPosition().x <= -550)
        sprite.setPosition(position_original, window_height-sprite.getTexture()->getSize().y);
}

void Grass::draw(RenderTarget& target, RenderStates states) const{
    target.draw(sprite);
}

