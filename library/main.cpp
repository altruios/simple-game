#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <math.h>
#include <optional>
#include <Enemy.hpp>
#include <Bonus_Item.hpp>
#include <Bullet.hpp>
#include <Player.hpp>
struct GAME_STATE{
     bool is_paused;
     int score;
     int bullet_power;
     int level;
     int bullet_id;
     int item_id;
     int enemy_id;
     std::string _message;
     sf::Text message;
     sf::Font message_style;
     std::vector<Bullet> bullets;
     std::vector<Enemy> enemies;
     std::vector<Bonus_Item> items;
     std::vector<Player> players;
     GAME_STATE(int score, int bullet_power,Player player, Enemy e){
          this->level=0;
          this->is_paused=false;
          this->score=score;
          this->bullet_power=bullet_power;
          this->players.push_back(player);
          this->bullet_id=0;
          this->item_id=0;
          this->enemy_id=1;
          this->enemies.push_back(e);
          if(!this->message_style.loadFromFile("arial.ttf")){
               std::cout<<"could not load text"<<std::endl;
               std::cout<<"failed to load"<<std::endl;
          }else{
               std::cout<<"successfuly loading of font"<<std::endl;
          }
          this->message.setFont(this->message_style);
          this->_message=
          "level: "+std::to_string(this->level)+"\n"+
          "score: "+std::to_string(this->score)+"\n"+
          "power: "+std::to_string(this->bullet_power)+"\n"+
          "enemy count: "+std::to_string(this->enemies.size());
          std::cout<<this->_message<<std::endl;
          this->message.setString(this->_message);

          std::cout<<"1"<<std::endl;

          this->message.setFillColor(sf::Color::Blue);
          std::cout<<"2"<<std::endl;

          this->message.setCharacterSize(24);               
          std::cout<<"3"<<std::endl;

          this->message.setPosition(250,250);           
          std::cout<<"4"<<std::endl;
          
     }
     void set_state(){
          this->level = this->players[0].level;
          this->bullet_power=this->players[0].power;
          this->_message=
          "level: "+std::to_string(this->level)+"\n"+
          "score: "+std::to_string(this->score)+"\n"+
          "power: "+std::to_string(this->bullet_power)+"\n"+
          "bullet count:"+std::to_string(this->bullets.size())+"\n"+
          "enemy count: "+std::to_string(this->enemies.size());
          this->message.setString(this->_message);

     }
     sf::Text* get_state(){
          return &this->message;
     }
};



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

void filter_E(std::vector<Enemy> &enemies, Enemy &e){
     for (int i = 0; i < enemies.size(); i++){
          if (!(enemies[i] == e)){
               enemies.erase(enemies.begin() + i);
         //      std::cout << "filtered enemy!" << std::endl;
          }
     }
}


Enemy *collision_detection(Bullet v, std::vector<Enemy> &enemies){
     for (Enemy &e : enemies){
          auto bullet_pos = v.shape.getPosition();
          auto enemy_pos = e.shape.getPosition();
          auto enemy_radius = e.shape.getRadius();
          auto bullet_radius = v.shape.getRadius();
          auto d = bullet_pos - enemy_pos;
          auto distance = (d.x * d.x) + (d.y * d.y);
          auto radi_sum = enemy_radius + bullet_radius;
          if (distance < radi_sum * radi_sum){
               return &e;
          }
     }
     return nullptr; //empty case
}

void filter_B(std::vector<Bullet> &bullets, Bullet &b){
     for (int i = 0; i < bullets.size(); i++){
          if (!(bullets[i] == b)){
               bullets.erase(bullets.begin() + i);
          }
     }
}
Bonus_Item *collision_detection_item(Player v, Bonus_Item &b){
          auto player_pos = v.shape.getPosition();
          auto bonus_pos = b.shape.getPosition();
          auto bonus_radius = b.shape.getRadius();
          auto player_radius = v.shape.getRadius();
          auto d = player_pos - bonus_pos;
          auto distance = (d.x * d.x) + (d.y * d.y);
          auto radi_sum =bonus_radius + player_radius;
          if (distance < radi_sum * radi_sum){
               return &b;
          }
     
     return nullptr; //empty case
}
void render_step(sf::RenderWindow &window, GAME_STATE &game){
     auto player_center = game.players[0].get_center();
     for (size_t i = 0; i < game.bullets.size(); i++){
          game.bullets[i].shape.move(game.bullets[i].velocity);
          Enemy *hit_target = collision_detection(game.bullets[i], game.enemies);
          if (hit_target != nullptr){
               hit_target->take_damage(game.bullets[i].damage);
               game.bullets[i].can_erase=true;
          }
     }
     for (size_t i = 0; i < game.enemies.size(); i++){
          game.enemies[i].update(window,player_center);
     }
     for(size_t i=0; i< game.items.size();i++){
          Bonus_Item *hit_target = collision_detection_item(game.players[0], game.items[i]);
          if(hit_target != nullptr){
               game.players[0].add_bonus(*hit_target);
               hit_target->can_erase=true;
          }
     }

     for(size_t i=0;i<game.cells.size();i++){
          
          cells[i].update(window,cells[i].find_open(cells),cells[i].find_biggest(cells)) )
     
     }

     game.set_state();

}
void draw(sf::RenderWindow &window, GAME_STATE &game){

     window.clear();
     window.draw(game.players[0].shape);
     for (size_t i = 0; i < game.enemies.size(); i++){
          window.draw(game.enemies[i].shape);
     }
     for (size_t i = 0; i < game.bullets.size(); i++){
          window.draw(game.bullets[i].shape);
     }
     for(size_t i=0; i<game.items.size();i++){
     window.draw(game.items[i].shape);
     }
     sf::Text *state = game.get_state();
     std::cout<<"the problem is window drawing state"<<std::endl;
     window.draw(*state);
          std::cout<<"or it could be something else"<<std::endl;

}

void player_controls(sf::RenderWindow &window, GAME_STATE &game){
     //SHOOT
     sf::Vector2f dir(0,0);
     if(!game.is_paused){
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
               game.players[0].fire(game.bullets,window,game.bullet_id);
          }
          //MOVEMENT CONTROLS
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || 
               sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
               dir.x+=-1; dir.y+=0;
          }
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || 
               sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
               dir.x+=1;dir.y+=0;
          }
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || 
               sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
               dir.x+=0; dir.y+=-1;
          }
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || 
               sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
               dir.x+=0; dir.y+=1;
          }
     }
     //GAME CONTROLS:: pause etc

     if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){
               std::cout<<"game is not paused"<<std::endl;
               game.is_paused=!game.is_paused;
     }

     game.players[0].update(window,dir);
}

GAME_STATE setup(){
     sf::Vector2i center_window(
          (sf::VideoMode::getDesktopMode().width / 2), 
          (sf::VideoMode::getDesktopMode().height / 2));
     Player player1;
     player1.shape.setPosition(center_window.x, center_window.y);
     Enemy enemy1{};
     enemy1.shape.setPosition(center_window.x / 5, center_window.y / 5);
     enemy1.set_radius(10);
     GAME_STATE g{0,1,player1,enemy1};
     return g;
}


void spawn_new_entites(sf::RenderWindow &window, GAME_STATE &game){
     if (game.enemies.size() < 10000){
          game.enemy_id++;
          float rand_x = (std::rand())%window.getSize().x-1;
          float rand_y= std::rand()%window.getSize().y-1;
          sf::Vector2f randomVector{rand_x,rand_y};
          float random_pos = (rand() %29);
          Enemy e{random_pos, sf::Color::Red, game.enemy_id};
          e.shape.setPosition(randomVector);
          game.enemies.push_back(e); 
     }
     if (game.items.size()<10){
          game.item_id++;
          float rand_x=(std::rand())%window.getSize().x-1;
          float rand_y=std::rand()%window.getSize().y-1;
          sf::Vector2f randomVector{rand_x,rand_y};
          Bonus_Item item{randomVector,2, sf::Color::Yellow, game.item_id};
          item.shape.setPosition(randomVector);
          game.items.push_back(item);
     }

}

void cleanup(sf::RenderWindow &window, GAME_STATE &game){
     for (size_t i = 0; i < game.bullets.size(); i++){
          game.bullets[i].check(10);
          if (game.bullets[i].can_erase){
               game.bullets.erase(game.bullets.begin() + i);
          }
     }
     for (size_t i = 0; i < game.enemies.size(); i++){
          auto health = game.enemies[i].health;
          if (health <= 0){
               game.players[0].exp_gain(game.enemies[i]);
               game.enemies.erase(game.enemies.begin() + i);
          }
     }
}

int main(){
     //WINDOW SETUP:
     sf::RenderWindow window(sf::VideoMode(1920, 1080), "simple game");
     window.setFramerateLimit(60);
     GAME_STATE game = setup();
     // Create a graphical text to display


     while (window.isOpen()){
          sf::Event event;
          while (window.pollEvent(event)){
               if (event.type == sf::Event::Closed){
                    window.close();
               }
          }


          player_controls(window,game);

          //MOVEMENT AND COLLISION DETECTION
               //do only if game is not paused;
          if(!game.is_paused){
               render_step(window,game);
               spawn_new_entites(window,game);     
               cleanup(window,game);

          }else{
               std::cout<<"game is not paused"<<std::endl;

          }

          draw(window,game);
          window.display();
          std::cout<<"game is paused:"<<game.is_paused<<std::endl;
     }
     return 0;
}