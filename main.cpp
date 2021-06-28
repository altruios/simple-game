#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <math.h>
#include <optional>
#include "./includes/Enemy.hpp"

void mirror_wrap(sf::CircleShape &shape, sf::Window &w)
{
     auto position = shape.getPosition();
     auto borders = w.getSize();
     if (position.x < 0)
     {
          shape.setPosition(borders.x, position.y);
     }
     else if (position.x > borders.x)
     {
          shape.setPosition(0, position.y);
     }
     if (position.y < 0)
     {
          shape.setPosition(position.x, borders.y);
     }
     else if (position.y > borders.y)
     {
          shape.setPosition(position.x, 0);
     }
}

template <typename... Args>
void print(Args &&...args)
{
     (std::cout << ... << args) << '\n';
}
enum level_powers
{
     health,
     power,
     speed,
};

// class Enemy
// {
// public:
//      sf::CircleShape shape;
//      sf::Vector2f velocity;
//      float speed = 1;
//      float max_speed;
//      float health;
//      int id;
//      sf::Color color;
//      float radius;
//      Enemy() : radius(3), color(sf::Color::Cyan), id(1), velocity(1.5f, 4.3f), max_speed(2), health(10)
//      {
//           this->shape.setRadius(this->radius);
//           this->shape.setFillColor(this->color);
//      }
//      Enemy(float radius, sf::Color c, int id) : velocity(1.5f, 4.3f), max_speed(2), health(10)
//      {
//           this->shape.setRadius(radius);
//           this->shape.setFillColor(c);
//           this->id = id;
//      }
//      void take_damage(float damage)
//      {
//           this->health -= damage;
//      }
//      void set_radius(float r)
//      {
//           this->radius = r;
//           this->shape.setRadius(this->radius);
//      }
//      bool operator==(const Enemy &e)
//      {
//           return e.id == this->id;
//      }

//      void move(sf::Vector2f pos_target)
//      {
//           //get the direction towards this positional target
//           //normalize difference between current enemy pos, and target pos - add to vector... yes? just do it...
//           auto position = this->shape.getPosition();
//           auto radius = this->shape.getRadius();
//           sf::Vector2f center{position.x + radius, position.y + radius};
//           auto aim_dir = pos_target - center;
//           auto aim_norm = aim_dir / float(sqrt(pow(aim_dir.x, 2) + pow(aim_dir.y, 2)));
//           this->velocity.x = aim_norm.x + this->speed;
//           this->velocity.y = aim_norm.y + this->speed;
//           this->shape.setPosition(
//               this->shape.getPosition().x + this->velocity.x,
//               this->shape.getPosition().y + this->velocity.y);
//           this->speed = std::min(this->speed + 1, this->max_speed);
//      }
// };

void filter_E(std::vector<Enemy> &enemies, Enemy &e)
{
     std::cout << "filter_E called line count>> " << enemies.size() << std::endl;
     for (int i = 0; i < enemies.size(); i++)
     {
          if (!(enemies[i] == e))
          {
               enemies.erase(enemies.begin() + i);
               std::cout << "filtered enemy!" << std::endl;
          }
     }
}

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
     Player() : speed(1), max_speed(10.f), max_bullets(100), health(100), power(10)
     {
          this->shape.setRadius(4.f);
          this->shape.setPointCount(3);
          this->shape.setFillColor(sf::Color::Green);
     }
     sf::Vector2f get_center()
     {
          auto pos = this->shape.getPosition();
          auto r = this->shape.getRadius();
          return sf::Vector2f(pos.x + r, pos.y + r);
     }
     void level_up(auto amount)
     {

          this->max_health += amount / 2;
          this->speed += amount / 2;
          this->max_bullets += amount / 2;
          this->health = this->max_health;
          this->level++;
     }
     void exp_gain(Enemy &e)
     {
          print("e max speed", e.max_speed);
          this->experiance = this->experiance + e.max_speed * 100;
          if (this->experiance > this->level * 1000)
          {
               print("leveling");
               this->level_up(this->level);
               this->shape.setRadius(this->level);
          }
          print("exp now is: ", this->experiance);
     }
};

class Bullet
{
public:
     sf::CircleShape shape;
     sf::Vector2f velocity;
     float max_speed;
     int id;
     bool can_erase;
     int counter;
     float damage;
     Bullet(float radius = 5.f, int id = 0)
         : velocity(0.f, 0.f), max_speed(15.f), damage(1)
     {
          this->shape.setRadius(radius);
          this->shape.setFillColor(sf::Color::Blue);
          this->id = id;
     }
     bool operator==(const Bullet &bullet)
     {
          return bullet.id == this->id;
     }
     Bullet(float radius, int id, float damage, int counter)
     {
          this->shape.setRadius(radius);
          this->id = id;
          this->damage = damage;
          this->counter = counter;
     }
     Bullet(const Bullet &b, int i)
     {
          this->id = i;
          this->damage = 1;
          std::cout << "copy constructor called"
                    << "\n";
     }
     void check(int max_allowed)
     {
          this->counter--;
          bool result = !(this->can_erase) ? (this->counter <= 0) : true;
          print("result:",result);
          this->can_erase = result;
     }
     void set_power(int power)
     {
          this->damage = power;
          this->shape.setRadius(this->shape.getRadius() + power);
     }
     void update(sf::RenderWindow &window)
     {
          this->shape.move(this->velocity);
          mirror_wrap(this->shape, window);
     }
};

Enemy *collision_detection(Bullet v, std::vector<Enemy> &enemies)
{
     for (Enemy &e : enemies)
     {
          auto bullet_pos = v.shape.getPosition();
          auto enemy_pos = e.shape.getPosition();
          auto enemy_radius = e.shape.getRadius();
          auto bullet_radius = v.shape.getRadius();
          auto d = bullet_pos - enemy_pos;
          auto distance = (d.x * d.x) + (d.y * d.y);
          auto radi_sum = enemy_radius + bullet_radius;
          if (distance < radi_sum * radi_sum)
          {
               return &e;
          }
     }
     return nullptr; //empty case
}

void filter_B(std::vector<Bullet> &bullets, Bullet &b)
{
     for (int i = 0; i < bullets.size(); i++)
     {
          if (!(bullets[i] == b))
          {
               bullets.erase(bullets.begin() + i);
          }
     }
}

void render_step(sf::RenderWindow &window, std::vector<Bullet> &bullets, std::vector<Enemy> &enemies, Player &player)
{
     auto player_center = player.get_center();
     for (size_t i = 0; i < bullets.size(); i++)
     {
          bullets[i].shape.move(bullets[i].velocity);
          mirror_wrap(bullets[i].shape, window);
          Enemy *hit_target = collision_detection(bullets[i], enemies);
          if (hit_target != nullptr)
          {
               hit_target->take_damage(bullets[i].damage);
               bullets[i].can_erase = true;
          }
     }
     for (size_t i = 0; i < enemies.size(); i++)
     {
          enemies[i].move(player_center);
          mirror_wrap(enemies[i].shape, window);
     }
}
void draw(sf::RenderWindow &window, std::vector<Bullet> &bullets, std::vector<Enemy> &enemies, Player &player1)
{
     window.draw(player1.shape);
     for (size_t i = 0; i < enemies.size(); i++)
     {
          window.draw(enemies[i].shape);
          print("enemy count", enemies.size());
     }
     for (size_t i = 0; i < bullets.size(); i++)
     {
          window.draw(bullets[i].shape);
          print("bullet count", bullets.size());
     }
}

void player_controls(sf::RenderWindow &window, std::vector<Bullet> &bullets, Player &player1,int bullet_id)
{
     //SHOOT
     Bullet b1{1.1f, 1};
     sf::Vector2f aim_dir;
     sf::Vector2f mouse_pos_window;
     sf::Vector2f aim_dir_norm;
     if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
     {
          mouse_pos_window = sf::Vector2f(sf::Mouse::getPosition(window));
          aim_dir = mouse_pos_window - player1.get_center();
          aim_dir_norm = aim_dir / float(sqrt(pow(aim_dir.x, 2) + pow(aim_dir.y, 2)));
          b1.velocity = aim_dir_norm * b1.max_speed;
          b1.shape.setPosition(player1.get_center());
          if (bullets.size() < player1.max_bullets)
          {
               Bullet b{player1.power,  bullet_id++,  player1.power,  player1.max_bullets};
               bullets.push_back(b);
               bullets[bullets.size() - 1].set_power(player1.power);
          }
     }

     //CONTROLS
     if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
     {
          //std::cout<<"Left"<<std::endl;
          player1.shape.setPosition(player1.shape.getPosition().x - player1.speed, player1.shape.getPosition().y);
     }
     if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
     {
          //std::cout<<"Right"<<std::endl;
          player1.shape.setPosition(player1.shape.getPosition().x + player1.speed, player1.shape.getPosition().y);
     }
     if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
     {
          //std::cout<<"Up"<<std::endl;
          player1.shape.setPosition(player1.shape.getPosition().x, player1.shape.getPosition().y - player1.speed);
     }
     if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
     {
          //std::cout<<"Down"<<std::endl;
          player1.shape.setPosition(player1.shape.getPosition().x, player1.shape.getPosition().y + player1.speed);
     }
     mirror_wrap(player1.shape, window);
}

void spawn_new_entites(sf::RenderWindow &window, std::vector<Bullet> &bullets, std::vector<Enemy> &enemies, Player &player1, int &enemy_id)
{

     if (enemies.size() < 10)
     {
          enemy_id++;
          Enemy e{rand() % 29, sf::Color::Red, enemy_id};
          enemies.push_back(e);
     }
}

void cleanup(std::vector<Bullet> &bullets, std::vector<Enemy> &enemies, Player &player1)
{
     for (size_t i = 0; i < bullets.size(); i++)
     {
          bullets[i].check(10);
          if (bullets[i].can_erase)
          {
               bullets.erase(bullets.begin() + i);
          }
     }
     for (size_t i = 0; i < enemies.size(); i++)
     {
          auto health = enemies[i].health;
          if (health <= 0)
          {
               player1.exp_gain(enemies[i]);
               enemies.erase(enemies.begin() + i);
          }
     }
}
int main()
{
     sf::RenderWindow window(sf::VideoMode(2000, 2000), "hello world");
     window.setFramerateLimit(60);
     int bullet_count = 0;
     int enemy_id = 0;
     // Create a graphical text to display
     sf::Vector2i center_window((sf::VideoMode::getDesktopMode().width / 2) - 45, (sf::VideoMode::getDesktopMode().height / 2) - 45);
     Player player1;
     player1.shape.setPosition(center_window.x, center_window.y);
     Enemy enemy1{};
     std::vector<Enemy> enemies;

     enemy1.shape.setPosition(center_window.x / 5, center_window.y / 5);
     enemy1.set_radius(10);

     enemies.push_back(enemy1);
     std::vector<Bullet> bullets;
     std::vector<Player> players;
     players.push_back(player1);
     while (window.isOpen())
     {
          sf::Event event;
          while (window.pollEvent(event))
          {
               if (event.type == sf::Event::Closed)
               {
                    window.close();
               }
          }
          window.clear();

          player_controls(window, bullets, player1,bullet_count);

          //MOVEMENT AND COLLISION DETECTION
          render_step(window, bullets, enemies, player1);

          //DRAW
          draw(window, bullets, enemies, player1);

          //CLEANUP
          cleanup(bullets, enemies, player1);

          window.display();
          spawn_new_entites(window, bullets, enemies, player1, enemy_id);
          print("level", player1.level, "bp:", player1.power, " s:", player1.speed);
     }

     return 0;
}