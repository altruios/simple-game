
#include <Bonus_Item.hpp>
#include<math.h>
Bonus_Item::Bonus_Item(sf::Vector2f pos, int amount,sf::Color color, int id):velocity(0.f,0.f){
          this->shape.setPosition(pos);
          this->power = power;
          this->shape.setFillColor(color);
          this->id=id;
          this->amount;
     }
void Bonus_Item:: move(){
     this->life_counter--;
     this->can_erase = this->life_counter>0;
     this->shape.setPosition(this->shape.getPosition()+this->velocity);
     }
void Bonus_Item:: update(sf::RenderWindow &window){
          this->shape.move(this->velocity);
          this->mirror_wrap(window);

}     
void Bonus_Item::mirror_wrap(sf::RenderWindow &w){
          
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


