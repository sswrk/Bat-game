#include "Obstacle.h"

Obstacle::Obstacle(const Texture& texture, const float position, const RenderWindow& window, float* velocity)
: velocity(velocity), texture(&texture), position_original(1200){
	float offset = random(-(texture.getSize().y / 3.0f), texture.getSize().y / 3.0f);

	top.setTexture(texture);
	top.setOrigin(static_cast<float>(texture.getSize().x), static_cast<float>(texture.getSize().y / 2.0f));
	top.setScale(1.0f, -1.0f);
	top.setPosition(position, offset);

	bottom.setTexture(texture);
	bottom.setOrigin(static_cast<float>(texture.getSize().x), static_cast<float>(texture.getSize().y / 2.0f));
	bottom.setPosition(position, static_cast<float>(window.getSize().y) + offset);
}

void Obstacle::animate(const float delta, const RenderWindow& window){
	top.move(-*velocity * delta, 0.0f);
	bottom.move(-*velocity * delta, 0.0f);

	if (top.getPosition().x <= 0){
		float offset = random(-(texture->getSize().y / 3.0f), texture->getSize().y / 3.0f);
		top.setPosition(position_original, offset);
		bottom.setPosition(position_original, static_cast<float>(window.getSize().y) + offset);
		passed = false;
	}
}

void Obstacle::draw(RenderTarget& target, RenderStates states) const{
	target.draw(top);
	target.draw(bottom);
}