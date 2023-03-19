
#ifndef PLATFORMERSFML_MUSHROOM_H
#define PLATFORMERSFML_MUSHROOM_H

// Game codebase
#include "Gameobject.h"

class Mushroom : public GameObject
{
 public:
  void createMushroom(sf::Texture &texture, float x, float y);
  void movement();
  bool blockCollision(sf::Sprite* sprite, sf::Vector2f new_pos);
  bool groundCollision(sf::Sprite* sprite, sf::Vector2f new_pos);
  void animations(float dt);

  bool going_left = false;
  bool going_right = true;
  float speed = 150;
  sf::Vector2f velocity;

 protected:

 private:
  void flipX();

  sf::IntRect texture_rect;
  sf::Vector2f frame;
  float frame_time = 0.05;
  bool is_x_flipped;
};

#endif // PLATFORMERSFML_MUSHROOM_H
