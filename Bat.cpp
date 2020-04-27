#include "Bat.h"

Bat::Bat(Texture& texture, const RenderWindow& window, float velocity):velocity(velocity), texture(&texture){
	sprite.setTexture(texture);
	sprite.setOrigin((Vector2f)(texture.getSize())/2.0f);
	sprite.setPosition((Vector2f)(window.getSize())/2.0f);
	box = sprite.getGlobalBounds();
}

void Bat::kill(const RenderWindow& window){
	sprite.setPosition((Vector2f)(window.getSize())/2.0f);
	sprite.setRotation(0.0f);
	vecf*=0.0f;
	cscore = 0;
	dead = false;
}

void Bat::animate(const float time, const RenderWindow& window, vector<Obstacle>& obstacles){
	vecf.y+=downf * time * velocity/200.f;
	sprite.move(vecf*time);
	sprite.rotate(rotation_velocity*time);
	
	if (sprite.getRotation() >= 60.0f && sprite.getRotation() <= 330.0f)
		sprite.setRotation(60.0f);

	if (sprite.getPosition().y <= 0.0f || sprite.getPosition().y >= window.getSize().y)
		dead = true;

	box.left = sprite.getPosition().x - (texture->getSize().x / 2.0f);
	box.top = sprite.getPosition().y - (texture->getSize().y / 2.0f);

	for (auto& obstacle : obstacles){
		if (obstacle.collision(box)) dead = true;
		if (!obstacle.isPassed() && sprite.getPosition().x > obstacle.getPosition()){
			obstacle.setPassed();
			cscore++;
		}
	}
}

void Bat::jump(){
    sprite.setRotation(330.0f);
	vecf.y = jumpf*sqrt(velocity/200.f);
}