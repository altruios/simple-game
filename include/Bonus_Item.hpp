#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <math.h>
#include <optional>
class Bonus_Item{
     public:
     sf::CircleShape shape;
     int id;
     bool can_erase;
     int life_counter = 1000;
     int power;
     sf::Vector2f velocity;
     int amount;
     Bonus_Item(sf::Vector2f pos, int amount,sf::Color color, int id);
     void move();
     void set_power(int p);
     void update(sf::RenderWindow &window);
          void mirror_wrap(sf::RenderWindow &window);

};