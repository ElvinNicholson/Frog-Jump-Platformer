
#ifndef PLATFORMERSFML_DOOR_H
#define PLATFORMERSFML_DOOR_H

// Game codebase
#include "Gameobject.h"

class Door : public GameObject
{
 public:
  Door();

  void animations(float dt);
  void resetDoor();

  bool player_is_near;
  bool play_anim;

 protected:

 private:
  sf::Texture texture;
  sf::IntRect texture_rect;
  sf::Vector2f frame;
  float frame_time = 0.1;
  bool door_open;
};

#endif // PLATFORMERSFML_DOOR_H
