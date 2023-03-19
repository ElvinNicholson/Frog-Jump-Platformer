
#ifndef PLATFORMERSFML_SPIKEDBALL_H
#define PLATFORMERSFML_SPIKEDBALL_H

// Game codebase
#include "Gameobject.h"

class SpikedBall : public GameObject
{
 public:
  void createSpikedBall(sf::Texture &chain_texture, sf::Texture &ball_texture, float x, float y);
  void rotation(float dt);
  bool ballCollision(sf::Sprite* player);

  GameObject ball;

 protected:

 private:
  float speed = 100;
};

#endif // PLATFORMERSFML_SPIKEDBALL_H
