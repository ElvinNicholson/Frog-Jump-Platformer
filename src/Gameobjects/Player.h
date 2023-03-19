
#ifndef PLATFORMERSFML_PLAYER_H
#define PLATFORMERSFML_PLAYER_H

// Game codebase
#include "Gameobject.h"

class Player : public GameObject
{
 public:
  Player();

  void movementInput(float dt);
  bool horizontalCollision(sf::Sprite* sprite, sf::Vector2f new_pos);
  bool groundCollision(sf::Sprite* sprite);
  bool ceilingCollision(sf::Sprite* sprite);
  bool normalCollision(sf::Sprite* sprite);
  void gravity(float dt);
  void animations(float dt);
  void hitHandler(float dt);
  void restartPlayer();

  int health = 3;

  bool is_grounded = false;
  bool is_wall_jump = false;
  bool left_collide = false;
  bool right_collide = false;
  bool is_hit = false;

  bool can_jump = false;
  bool can_wall_jump_right = false;
  bool can_wall_jump_left = false;

  sf::Vector2f velocity;
  float speed = 200;

 protected:

 private:
  void flipX();
  void idleAnimation();
  void walkAnimation();
  void jumpAnimation();
  void wallJumpAnimation();
  void hitAnimation();

  sf::Texture player_texture;
  sf::IntRect player_texture_rect;
  sf::Vector2f frame;
  float hit_cooldown = 1;
  float frame_time = 0.05;
  bool is_x_flipped;

  float width;
  float height;
};

#endif // PLATFORMERSFML_PLAYER_H
