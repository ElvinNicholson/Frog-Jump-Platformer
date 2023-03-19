
#include "Block.h"

void Block::createBlock(sf::Texture &block_texture, float x, float y, BlockType _type)
{
  type = _type;
  setTexture(block_texture);

  switch(type)
  {
    case BlockType::BLOCK:
      texture_rect = sf::IntRect(192, 80, 16, 16);
      break;

    case BlockType::SPIKE:
      texture_rect = sf::IntRect(336, 24, 16, 8);
      break;

    case BlockType::GRASS_NW:
      texture_rect = sf::IntRect(96, 0, 16, 16);
      break;

    case BlockType::GRASS_N:
      texture_rect = sf::IntRect(112, 0, 16, 16);
      break;

    case BlockType::GRASS_NE:
      texture_rect = sf::IntRect(128, 0, 16, 16);
      break;

    case BlockType::GRASS_W:
      texture_rect = sf::IntRect(96, 16, 16, 16);
      break;

    case BlockType::GRASS_M:
      texture_rect = sf::IntRect(112, 16, 16, 16);
      break;

    case BlockType::GRASS_E:
      texture_rect = sf::IntRect(128, 16, 16, 16);
      break;

    case BlockType::GRASS_SW:
      texture_rect = sf::IntRect(96, 32, 16, 16);
      break;

    case BlockType::GRASS_S:
      texture_rect = sf::IntRect(112, 32, 16, 16);
      break;

    case BlockType::GRASS_SE:
      texture_rect = sf::IntRect(128, 32, 16, 16);
      break;

    case BlockType::GRASS_RIGHT:
      texture_rect = sf::IntRect(160, 16, 16, 16);
      break;

    case BlockType::GRASS_LEFT:
      texture_rect = sf::IntRect(144, 16, 16, 16);
      break;

    case BlockType::BRICK_NW:
      texture_rect = sf::IntRect(272, 64, 16, 16);
      break;

    case BlockType::BRICK_N:
      texture_rect = sf::IntRect(288, 64, 16, 16);
      break;

    case BlockType::BRICK_NE:
      texture_rect = sf::IntRect(304, 64, 16, 16);
      break;

    case BlockType::BRICK_W:
      texture_rect = sf::IntRect(272, 80, 16, 16);
      break;

    case BlockType::BRICK_M:
      texture_rect = sf::IntRect(288, 80, 16, 16);
      break;

    case BlockType::BRICK_E:
      texture_rect = sf::IntRect(304, 80, 16, 16);
      break;

    case BlockType::BRICK_SW:
      texture_rect = sf::IntRect(272, 96, 16, 16);
      break;

    case BlockType::BRICK_S:
      texture_rect = sf::IntRect(288, 96, 16, 16);
      break;

    case BlockType::BRICK_SE:
      texture_rect = sf::IntRect(304, 96, 16, 16);
      break;
  }

  sprite -> setTextureRect(texture_rect);
  sprite -> setScale(2.5, 2.5);
  setPosition(x, y);
}
