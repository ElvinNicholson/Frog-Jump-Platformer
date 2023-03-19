
#ifndef PLATFORMERSFML_COLLECTIBLE_H
#define PLATFORMERSFML_COLLECTIBLE_H

// Game codebase
#include "Gameobject.h"
#include "CollectibleType.h"

class Collectible : public GameObject
{
 public:
  void createCollectible(sf::Texture &texture, float x, float y, CollectibleType _type);
  void animations(float dt);

  CollectibleType type;
  int value = 0;

 protected:

 private:
  sf::IntRect texture_rect;
  sf::Vector2f frame;
  float frame_time = 0.1;
};

#endif // PLATFORMERSFML_COLLECTIBLE_H
