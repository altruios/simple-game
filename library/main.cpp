#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <math.h>
#include <optional>
#include <Enemy.hpp>
#include <Bonus_Item.hpp>
#include <Bullet.hpp>
#include <Player.hpp>
template <typename... Args>
void print(Args &&...args)
{
 //    (std::cout << ... << args) << '\n';
}
enum level_powers
{
     health,
     power,
     speed,
};

void filter_E(std::vector<Enemy> &enemies, Enemy &e)
{
   //  std::cout << "filter_E called line count>> " << enemies.size() << std::endl;
     for (int i = 0; i < enemies.size(); i++)
     {
          if (!(enemies[i] == e))
          {
               enemies.erase(enemies.begin() + i);
         //      std::cout << "filtered enemy!" << std::endl;
          }
     }
}


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
Bonus_Item *collision_detection_item(Player v, Bonus_Item &b)
{
          auto player_pos = v.shape.getPosition();
          auto bonus_pos = b.shape.getPosition();
          auto bonus_radius = b.shape.getRadius();
          auto player_radius = v.shape.getRadius();
          auto d = player_pos - bonus_pos;
          auto distance = (d.x * d.x) + (d.y * d.y);
          auto radi_sum =bonus_radius + player_radius;
          if (distance < radi_sum * radi_sum)
          {
               return &b;
          }
     
     return nullptr; //empty case
}
void render_step(sf::RenderWindow &window, std::vector<Bullet> &bullets, std::vector<Enemy> &enemies, std::vector<Bonus_Item> &bonuses,Player &player)
{
     auto player_center = player.get_center();
     for (size_t i = 0; i < bullets.size(); i++)
     {
          bullets[i].shape.move(bullets[i].velocity);
          Enemy *hit_target = collision_detection(bullets[i], enemies);
          if (hit_target != nullptr)
          {
               hit_target->take_damage(bullets[i].damage);
               bullets[i].can_erase = true;
          }
     }
     for (size_t i = 0; i < enemies.size(); i++){
          enemies[i].update(window,player_center);
     }
     for(size_t i=0; i< bonuses.size();i++){
          Bonus_Item *hit_target = collision_detection_item(player, bonuses[i]);
          if(hit_target != nullptr){
               player.add_bonus(*hit_target);
               hit_target->can_erase=true;
          }
     }


}
void draw(sf::RenderWindow &window, std::vector<Bullet> &bullets, std::vector<Enemy> &enemies, Player &player1)
{
     window.draw(player1.shape);
     for (size_t i = 0; i < enemies.size(); i++)
     {
          window.draw(enemies[i].shape);
      //    print("enemy count", enemies.size());
     }
     for (size_t i = 0; i < bullets.size(); i++)
     {
          window.draw(bullets[i].shape);
     //     print("bullet count", bullets.size());
     }
}

void player_controls(sf::RenderWindow &window, std::vector<Bullet> &bullets, Player &player1,int bullet_id)
{
     //SHOOT

     if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
     {
          player1.fire(bullets,window,bullet_id);
          
     }

     //CONTROLS
     sf::Vector2f dir(0,0);
     if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
          dir.x+=-1; dir.y+=0;
     }
     if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
          dir.x+=1;dir.y+=0;
          }
     if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
          dir.x+=0; dir.y+=-1;
     }
     if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
          dir.x+=0; dir.y+=1;
     }
     player1.update(window,dir);
}



void spawn_new_entites(sf::RenderWindow &window, std::vector<Bullet> &bullets, std::vector<Enemy> &enemies, std::vector<Bonus_Item> &bonuses,Player &player1, int &enemy_id, int&bonus_id)
{

     if (enemies.size() < 10000)
     {
          enemy_id++;
          sf::Vector2f randomVector{(std::rand())%window.getSize().x-1, std::rand()%window.getSize().y-1};
          Enemy e{rand() % 29, sf::Color::Red, enemy_id};
          e.shape.setPosition(randomVector);
          enemies.push_back(e);
     }
     if (bonuses.size()<10){
          bonus_id++;
          sf::Vector2f randomVector{(std::rand())%window.getSize().x-1, std::rand()%window.getSize().y-1};
          Bonus_Item item{randomVector,2, sf::Color::Yellow, bonus_id};
          item.shape.setPosition(randomVector);
          bonuses.push_back(item);
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
     sf::Vector2i center_window((sf::VideoMode::getDesktopMode().width / 2) - 45, (sf::VideoMode::getDesktopMode().height / 2) - 45);
     window.setFramerateLimit(60);
     Player player1;
     player1.shape.setPosition(center_window.x, center_window.y);


     int bullet_count = 0;
     int enemy_id = 0;
     int bonus_id=0;
     // Create a graphical text to display
     Enemy enemy1{};
     std::vector<Enemy> enemies;

     enemy1.shape.setPosition(center_window.x / 5, center_window.y / 5);
     enemy1.set_radius(10);

     enemies.push_back(enemy1);
     std::vector<Bullet> bullets;
     std::vector<Player> players;
     std::vector<Bonus_Item> bonuses;
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
          render_step(window, bullets, enemies, bonuses,player1);

          //DRAW
          draw(window, bullets, enemies, player1);

          //CLEANUP
          cleanup(bullets, enemies, player1);

          window.display();
          spawn_new_entites(window, bullets, enemies, bonuses,player1, enemy_id,bonus_id);
          print("level", player1.level, "bp:", player1.power, " s:", player1.speed);
     }

     return 0;
}