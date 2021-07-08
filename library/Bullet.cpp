#include <Bullet.hpp>

Bullet::Bullet(float radius, int id)
         : velocity(0.1f, 0.1f), max_speed(15.f), damage(1)
     {
          this->shape.setRadius(radius);
          this->shape.setFillColor(sf::Color::Blue);
          this->id = id;
     }
     bool Bullet::operator==(const Bullet &bullet)
     {
          return bullet.id == this->id;
     }
Bullet::Bullet(float radius, int id, float damage, int counter )
     {
          this->shape.setRadius(radius);
          this->id = id;
          this->damage = damage;
          this->counter = counter;
          this->max_speed=15;
     }
Bullet::Bullet(const Bullet &b, int i)
     {
          this->id = i;
          this->damage = 1;
          //std::cout << "copy constructor called"
         //           << "\n";
     }
     void Bullet::check(int max_allowed)
     {
          this->counter--;
          bool result = !(this->can_erase) ? (this->counter <= 0):true;
          //print("result:",result);
          this->can_erase = result;
     }
     int Bullet::get_power(){
          return this->damage;
     }
     void Bullet::set_power(int power)
     {
          this->damage = power;
          this->set_color(power);
     }

     void Bullet::set_color( int const color){
          if(color<100){this->shape.setFillColor(sf::Color::Blue);}
          if(color<90){this->shape.setFillColor(sf::Color::Green);}
          if(color<80){this->shape.setFillColor(sf::Color::Magenta);}
          if(color<70){this->shape.setFillColor(sf::Color::Yellow);}
          if(color<60){this->shape.setFillColor(sf::Color::White);}
          if(color<50){this->shape.setFillColor(sf::Color::Cyan);}
          if(color<40){this->shape.setFillColor(sf::Color(255,0,155,255 ));}
          if(color<30){this->shape.setFillColor(sf::Color(155,0,155,255 ));}
          if(color<20){this->shape.setFillColor(sf::Color(155,0,55,255  ));}
          if(color<10){this->shape.setFillColor(sf::Color(55,0,55,255   ));}
          
     }
     void Bullet::update(sf::RenderWindow &window)
     {
          this->shape.move(this->velocity);
          this->mirror_wrap(window);
     }
     void Bullet::mirror_wrap(sf::RenderWindow &w){
          
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

