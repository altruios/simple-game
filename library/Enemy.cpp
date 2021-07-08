#include <Enemy.hpp>
#include<math.h>

Enemy::Enemy() : radius(3), color(sf::Color::Cyan), id(1), velocity(1.5f, 4.3f), max_speed(2), health(10){
     this->shape.setRadius(this->radius);
     this->shape.setFillColor(this->color);
}
Enemy::Enemy(float radius, sf::Color c, int id) : velocity(1.5f, 4.3f), max_speed(2), health(10){
     this->shape.setRadius(radius);
     this->shape.setFillColor(c);
     this->id = id;
}
void Enemy::take_damage(float damage){
     this->health -= damage;
     this->shape.setRadius(std::min(1.f,this->shape.getRadius()-damage));
}
void Enemy::set_radius(float r){
     this->radius = r;
     this->shape.setRadius(this->radius);
}
bool Enemy::operator==(const Enemy &e){
     return e.id == this->id;
}

void Enemy::move(sf::Vector2f pos_target){
    //get the direction towards this positional target
    //normalize difference between current enemy pos, and target pos - add to vector... yes? just do it...
    auto position = this->shape.getPosition();
    auto radius = this->shape.getRadius();
    sf::Vector2f center{position.x + radius, position.y + radius};
    auto aim_dir = pos_target - center;
    auto aim_norm = aim_dir / float(sqrt(pow(aim_dir.x, 2) + pow(aim_dir.y, 2)));
    this->velocity.x = aim_norm.x * this->speed;
    this->velocity.y = aim_norm.y * this->speed;
    this->shape.setPosition(
        this->shape.getPosition().x + this->velocity.x,
        this->shape.getPosition().y + this->velocity.y
     );
    this->speed = std::min(this->speed + 1, this->max_speed);
}
void Enemy::update(sf::RenderWindow &window,sf::Vector2f pos_target){
     this->move(pos_target);
     this->mirror_wrap(window);

}
void Enemy::mirror_wrap(sf::RenderWindow &w){
          
     auto position = this->shape.getPosition();
     auto borders = w.getSize();
     if (position.x < 0)
     {
         this->shape.setPosition(borders.x, position.y);
     }
     else if (position.x > borders.x)
     {
          this->shape.setPosition(0, position.y);
     }
     if (position.y < 0)
     {
          this->shape.setPosition(position.x, borders.y);
     }
     else if (position.y > borders.y)
     {
          this->shape.setPosition(position.x, 0);
     }
     }