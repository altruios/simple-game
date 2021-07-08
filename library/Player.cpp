#include <Player.hpp>
     Player::Player() : speed(1), max_speed(10.f), max_bullets(100), health(100), power(10)
     {
          this->shape.setRadius(4.f);
          this->shape.setPointCount(3);
          this->shape.setFillColor(sf::Color::Green);
     }
     sf::Vector2f Player::get_center()
     {
          auto pos = this->shape.getPosition();
          auto r = this->shape.getRadius();
          return sf::Vector2f(pos.x + r, pos.y + r);
     }
     void Player::level_up(int amount)
     {

          this->max_health += amount / 2;
          this->speed += .01;
          this->max_bullets += amount / 2;
          this->power+=1;
          this->health = this->max_health;
          this->level++;
          this->shape.setRadius(this->level);

     }
     void Player::exp_gain(Enemy &e)
     {
          this->experiance = this->experiance + e.max_speed * 100;
          if (this->experiance > this->level * 1000)
          {
               this->level_up(this->level);
          }
     }
     void Player::add_bonus(Bonus_Item &b){
     }
     void Player::move(sf::Vector2f dir){
          this->shape.setPosition(
               this->shape.getPosition().x+dir.x*this->speed,
               this->shape.getPosition().y+dir.y*this->speed
          );
     }
     void Player::update(sf::RenderWindow &window, sf::Vector2f dir){
          this->move(dir);
          this->mirror_wrap(window);

     }
     void Player::mirror_wrap(sf::RenderWindow &w){
          
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
     void Player::fire(std::vector<Bullet>&bullets,sf::RenderWindow &window, int &bullet_id){
          if (bullets.size() < this->max_bullets){
               sf::Vector2f aim_dir;
               sf::Vector2f mouse_pos_window = sf::Vector2f(sf::Mouse::getPosition(window));
               sf::Vector2f aim_dir_norm;
               aim_dir = mouse_pos_window - this->get_center();
               aim_dir_norm = aim_dir / float(sqrt(pow(aim_dir.x, 2) + pow(aim_dir.y, 2)));
               Bullet b1{this->power,  bullet_id++,  this->power,  this->max_bullets};
               b1.velocity = aim_dir_norm*b1.max_speed;
               b1.shape.setPosition(this->get_center());
               bullets.push_back(b1);
               bullets[bullets.size() - 1].set_power(this->power);
          }
     }
