#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <math.h>
#include <optional>
class Bullet{
     public:
     sf::CircleShape shape;
     sf::Vector2f velocity;
     float max_speed;
     int id;
     bool can_erase;
     int counter;
     float damage;
     Bullet(float radius = 5.f, int id = 0);
     bool operator==(const Bullet &bullet);
     Bullet(float radius, int id, float damage, int counter );
     Bullet(const Bullet &b, int i);
     void check(int max_allowed);
     void set_power(int power);
     int get_power();
     void set_color(int power);
     void update(sf::RenderWindow &window);
     void mirror_wrap(sf::RenderWindow &window);
};
