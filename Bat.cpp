#include "Bat.h"
#include "Observer.h"

Bat::Bat(Texture& texture, const RenderWindow& window, float* velocity)
: velocity(velocity), texture(&texture), bonus_passes(0){

	sprite.setTexture(texture);
	sprite.setOrigin((Vector2f)(texture.getSize())/2.0f);
	sprite.setPosition((Vector2f)(window.getSize())/2.0f);
	box = sprite.getGlobalBounds();
}

void Bat::animate(const float time, const RenderWindow& window, vector<Obstacle>& obstacles, Bonus*& bonus){
    vector_force.y+= gravity * time * *velocity / objects_distance * 2.0f;
    sprite.move(vector_force * time);
    sprite.rotate(rotation_velocity*time);
    if (sprite.getRotation() >= min_rotation && sprite.getRotation() <= max_rotation)
        sprite.setRotation(min_rotation);

    box.left = sprite.getPosition().x - (texture->getSize().x/2.0f);
    box.top = sprite.getPosition().y - (texture->getSize().y/2.0f);

    checkCollisions(obstacles, window);
    checkIfObstaclePassed(obstacles);
    checkIfBonusAcquired(bonus);
}

void Bat::jump(){
    sprite.setRotation(max_rotation);
    vector_force.y = jump_force * sqrt(*velocity / objects_distance * 2.0f);
}

void Bat::reset(const RenderWindow& window){
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

void Bat::checkCollisions(vector<Obstacle> &obstacles, const RenderWindow& window) {
    if (sprite.getPosition().y <= 0.0f || sprite.getPosition().y >= window.getSize().y)
        dead = true;
    for (auto& obstacle : obstacles)
        if (obstacle.collision(box) && bonus_passes==0)
            dead = true;
}

void Bat::checkIfObstaclePassed(vector<Obstacle>& obstacles) {
    for (auto& obstacle : obstacles){
        if (!obstacle.isPassed() && sprite.getPosition().x > obstacle.getPosition()+texture->getSize().x){
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
}

void Bat::checkIfBonusAcquired(Bonus* bonus) {
    if(bonus != nullptr && bonus->collision(box)){
        bonus_passes = bonus->getDuration();
        *velocity*=2;
        sprite.setColor(Color(255, 255, 0, 128));
        notifyBonusAcquired();
    }
}

void Bat::notifyScoreChanged() {
    observer->updateScore();
}

void Bat::notifyBonusAcquired(){
    observer->deleteBonus();
}
