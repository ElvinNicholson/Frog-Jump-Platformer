
#ifndef PLATFORMERSFML_BLOCK_H
#define PLATFORMERSFML_BLOCK_H

//  Game codebase
#include "Gameobject.h"
#include "BlockType.h"

class Block : public GameObject
{
 public:
  void createBlock(sf::Texture &texture, float x, float y, BlockType _type);

  BlockType type;

 protected:

 private:
  sf::IntRect texture_rect;
};

#endif // PLATFORMERSFML_BLOCK_H
