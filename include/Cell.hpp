#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <math.h>
#include <optional>
class Cell{
     sf::Vector2f position;
     sf::Vector2f direction;
     std::vector<sf::Vector3f> desired_dirs;
     std::vector<sf::Vector3f> avoided_dirs;
     sf::CircleShape shape;
     int speed;
     float desire_factor;
     Cell(sf::Vector2f pos,sf::Vector2f dir, int speed);
     void move();
     void update(sf::RenderWindow &window, sf::Vector3f target_pos, sf::Vector3f avoid_pos);
     void set_desired_direction();
     sf::Vector3f find_open(std::vector<Cell> &cells);
     sf::Vector3f find_biggest(std::vector<Cell>&cells);
};