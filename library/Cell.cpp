#include <Cell.hpp>
    Cell::Cell(sf::Vector2f pos,sf::Vector2f dir, int speed){
          this->shape.setPosition(pos);
          this->direction = dir;
          this->speed=speed;
          this->desire_factor=static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    }
     void Cell::move(){

          this->shape.setPosition(this->direction.x,this->direction.y);
     }
     void Cell::update(sf::RenderWindow &window, sf::Vector3f target_pos, sf::Vector3f avoid_pos){
          //normalize... etc

          this->avoided_dirs.push_back(avoid_pos);
          this->desired_dirs.push_back(target_pos);
          this->set_desired_direction();
          this->move();
     }
     void Cell::set_desired_direction(){
          sf::Vector2f result{0.f,0.f};
          auto position = this->shape.getPosition();
          auto radius = this->shape.getRadius();
          sf::Vector2f center{position.x + radius, position.y + radius};
          for(int i=0;i<this->desired_dirs.size();i++){
               //weighted by third vector
               float weight_desire = desired_dirs[i].z;
               sf::Vector2f d_dir = sf::Vector2f(desired_dirs[i].x,desired_dirs[i].y);
               float weight_avoid = avoided_dirs[i].z;
               sf::Vector2f a_dir = sf::Vector2f(avoided_dirs[i].x,avoided_dirs[i].y);
               result.x+=(weight_avoid*a_dir.x)+(weight_desire*d_dir.x);
               result.y+=(weight_avoid*a_dir.y)+(weight_desire*d_dir.y);
          }
          auto aim_dir = result - center;
          auto aim_norm = aim_dir / float(sqrt(pow(aim_dir.x, 2) + pow(aim_dir.y, 2)));
          this->direction.x = aim_norm.x * this->speed;
          this->direction.y = aim_norm.y * this->speed;

     }
     sf::Vector3f Cell::find_biggest(std::vector<Cell> &cells){
          Cell biggest = cells[0];
          for(Cell c:cells){
               if(c.shape.getRadius()>biggest.shape.getRadius()){
                    biggest = c;
               }
          }

     
          return biggest;
     }
     sf::Vector3f Cell::find_open(std::vector<Cell> &cells){
          sf::Vector3f result{0.f,0.f,0.f};
          for(Cell c : cells){
               sf::Vector2f pos = this->shape.getPosition();
               sf::Vector2f c_pos=c->shape.getPosition();
               float distance= sqrt(pow((pos.x-c_pos.x),2) + pow((pos.y-c_pos.y),2));
               result.x+=cpos.x;
               result.y+=cpos.y;
               result.z+=distace;
          }
          result.x=result.x/cells.size();
          result.y=result.y/cells.size();
          result.z=reuslt.z/cells.size();

          return result;
     }