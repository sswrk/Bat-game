#include "Bat.h"
#include "Observer.h"

Bat::Bat(Texture& texture, const RenderWindow& window, float*& velocity)
:velocity(velocity), texture(&texture), bonus_passes(0){
	sprite.setTexture(texture);
	sprite.setOrigin((Vector2f)(texture.getSize())/2.0f);
	sprite.setPosition((Vector2f)(window.getSize())/2.0f);
	box = sprite.getGlobalBounds();
}

void Bat::kill(const RenderWindow& window){
	sprite.setPosition((Vector2f)(window.getSize())/2.0f);
	sprite.setRotation(0.0f);
    sprite.setColor(Color(255, 255, 255, 255));
    if(bonus_passes!=0) {
        bonus_passes = 0;
        *velocity/=2;
    }
    vector_force*=0.0f;
    current_score = 0;
    notifyScoreChanged();
	dead = false;
}

void Bat::animate(const float time, const RenderWindow& window, vector<Obstacle>& obstacles, Bonus*& bonus){
    vector_force.y+= downforce * time * *velocity / 200.f;
	sprite.move(vector_force * time);
	sprite.rotate(rotation_velocity*time);
	
	if (sprite.getRotation() >= 60.0f && sprite.getRotation() <= 330.0f)
		sprite.setRotation(60.0f);

	if (sprite.getPosition().y <= 0.0f || sprite.getPosition().y >= window.getSize().y)
		dead = true;

	box.left = sprite.getPosition().x - (texture->getSize().x / 2.0f);
	box.top = sprite.getPosition().y - (texture->getSize().y / 2.0f);

	for (auto& obstacle : obstacles){
		if (obstacle.collision(box) && bonus_passes==0) dead = true;
		if (!obstacle.isPassed() && sprite.getPosition().x > obstacle.getPosition()+30){
			obstacle.setPassed();
			current_score++;
			if(bonus_passes>0){
			    bonus_passes--;
			    if(bonus_passes==0) {
                    sprite.setColor(Color(255, 255, 255, 255));
                    *velocity/=2;
                }
			}
            notifyScoreChanged();
		}
	}
	if(bonus != nullptr && bonus->collision(box)){
	    bonus_passes = bonus->getDuration();
	    sprite.setColor(Color(255, 255, 0, 128));
        notifyBonusAcquired();
	}
}

void Bat::jump(){
    sprite.setRotation(330.0f);
    vector_force.y = jumpforce * sqrt(*velocity / 200.f);
}

void Bat::notifyScoreChanged() {
    observer->updateScore();
}

void Bat::notifyBonusAcquired(){
    *velocity*=2;
    observer->deleteBonus();
}
