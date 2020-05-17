#include "Bonus.h"

Bonus::Bonus(const Texture& texture, const float position, const RenderWindow& window, float velocity)
        :velocity(velocity), texture(&texture), duration(3){
    float offset = random(-(float)window.getSize().y+300.0f, (float)window.getSize().y-300.0f);
    sprite.setTexture(texture);
    sprite.setOrigin(static_cast<float>(texture.getSize().x), window.getSize().y/2);
    sprite.setScale(1.0f, -1.0f);
    sprite.setPosition(position, offset);
}

void Bonus::animate(const float delta, const RenderWindow& window){
    sprite.move(-velocity * delta, 0.0f);
}

void Bonus::draw(RenderTarget& target, RenderStates states) const{
    target.draw(sprite);
}