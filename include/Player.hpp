#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <math.h>
#include <Enemy.hpp>
#include <Bonus_Item.hpp>
#include <Bullet.hpp>

#include <optional>
class Player
{
public:
     sf::CircleShape shape;
     sf::Vector2f player_center = this->shape.getPosition();
     float speed;
     float max_speed;
     float health;
     float max_health;
     float power;
     int level = 0;
     int experiance = 0;
     int max_bullets;
     Player();
     sf::Vector2f get_center();
     void level_up(int amount);
     void exp_gain(Enemy &e);
     void add_bonus(Bonus_Item &b);
     void move(sf::Vector2f dir);
     void update(sf::RenderWindow &window, sf::Vector2f dir);
     void fire(std::vector<Bullet>&bullets,sf::RenderWindow &window,int &bullet_id);
          void mirror_wrap(sf::RenderWindow &window);

};
