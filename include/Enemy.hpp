#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <math.h>
#include <optional>
class Enemy{
     public:
     sf::CircleShape shape;
     sf::Vector2f velocity;
     float speed = 1;
     float max_speed;
     float health;
     int id;
     sf::Color color;
     float radius;
     Enemy();
     Enemy(float radius, sf::Color c, int id);
     void take_damage(float damage);
     void set_radius(float r);
     bool operator==(const Enemy &e);
     void move(sf::Vector2f pos_target);
     void update(sf::RenderWindow &window,sf::Vector2f pos_target);
     void mirror_wrap(sf::RenderWindow &window);
}
;