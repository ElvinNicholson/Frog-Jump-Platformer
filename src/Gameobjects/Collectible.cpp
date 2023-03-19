
#include "Collectible.h"

void Collectible::createCollectible(sf::Texture& texture, float x, float y, CollectibleType _type)
{
  type = _type;
  setTexture(texture);

  switch(type)
  {
    case CollectibleType::KEY:
      texture_rect = sf::IntRect(0, 0, 32, 32);
      frame.y = 0;
      value = 0;
      break;

    case CollectibleType::DIAMOND:
      texture_rect = sf::IntRect(0, 32, 32, 32);
      frame.y = 1;
      value = 5;
      break;

    case CollectibleType::EMERALD:
      texture_rect = sf::IntRect(0, 64, 32, 32);
      frame.y = 2;
      value = 10;
      break;

    case CollectibleType::RUBY:
      texture_rect = sf::IntRect(0, 96, 32, 32);
      frame.y = 3;
      value = 15;
      break;
  }

  sprite -> setTextureRect(texture_rect);
  sprite -> setScale(1.25, 1.25);
  setPosition(x, y);
}

void Collectible::animations(float dt)
{
  frame_time -= dt;
  if (frame_time < 0)
  {
    frame_time = 0.1;
    frame.x += 1;
  }

  switch(type)
  {
    case CollectibleType::KEY:
      if (frame.x > 7)
      {
        frame.x = 0;
      }
      break;

    case CollectibleType::DIAMOND:
    case CollectibleType::EMERALD:
    case CollectibleType::RUBY:
      if (frame.x > 3)
      {
        frame.x = 0;
      }
      break;
  }

  texture_rect.left = frame.x * 32;
  texture_rect.top = frame.y * 32;
  sprite -> setTextureRect(texture_rect);
}
