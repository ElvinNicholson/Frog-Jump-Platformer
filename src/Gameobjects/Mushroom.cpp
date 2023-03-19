
#include "Mushroom.h"

void Mushroom::createMushroom(sf::Texture& texture, float x, float y)
{
  setTexture(texture);
  texture_rect = sf::IntRect(0, 0, 32, 32);
  sprite -> setTextureRect(texture_rect);
  sprite -> setScale(1.25, 1.25);
  setPosition(x, y);
}

void Mushroom::movement()
{
  if (going_left)
  {
    velocity.x = -1;
  }
  else if (going_right)
  {
    velocity.x = 1;
  }
}

bool Mushroom::blockCollision(sf::Sprite* sprite, sf::Vector2f new_pos)
{
  float sprite_width = sprite->getGlobalBounds().width;
  float sprite_height = sprite->getGlobalBounds().height;

  float mushroom_width = getSprite() -> getGlobalBounds().width;
  float mushroom_height = getSprite() -> getGlobalBounds().height;

  sf::Vector2f sprite_min = sprite -> getPosition();
  sf::Vector2f sprite_max(sprite_min.x + sprite_width, sprite_min.y + sprite_height);

  sf::Vector2f mushroom_min = new_pos;
  sf::Vector2f mushroom_max(new_pos.x + mushroom_width, new_pos.y + mushroom_height);
  mushroom_min.x += 2;
  mushroom_min.y += 10;
  mushroom_max.x -= 2;
  mushroom_min.y -= 10;

  if (
    mushroom_min.x < sprite_max.x &&
    mushroom_max.x > sprite_min.x &&
    mushroom_min.y < sprite_max.y &&
    mushroom_max.y > sprite_min.y)
  {
    if (mushroom_min.x > sprite_min.x)
    {
      going_right = true;
      going_left  = false;
    }
    else
    {
      going_left  = true;
      going_right = false;
    }
    return true;
  }
  else
  {
    return false;
  }
}

bool Mushroom::groundCollision(sf::Sprite* sprite, sf::Vector2f new_pos)
{
  float sprite_width = sprite->getGlobalBounds().width;
  float sprite_height = sprite->getGlobalBounds().height;

  float mushroom_width = getSprite() -> getGlobalBounds().width;
  float mushroom_height = getSprite() -> getGlobalBounds().height;

  sf::Vector2f sprite_min = sprite -> getPosition();
  sf::Vector2f sprite_max(sprite_min.x + sprite_width, sprite_min.y + sprite_height);

  sf::Vector2f ground_check = new_pos;
  ground_check.y += mushroom_height + 1;

  if (going_right)
  {
    ground_check.x += mushroom_width;
  }

  if (
    ground_check.x < sprite_max.x &&
    ground_check.x > sprite_min.x &&
    ground_check.y < sprite_max.y &&
    ground_check.y > sprite_min.y)
  {
    return true;
  }
  else
  {
    return false;
  }
}

void Mushroom::animations(float dt)
{
  frame_time -= dt;
  if (frame_time < 0)
  {
    frame_time = 0.05;
    frame.x += 1;
  }

  frame.y = 0;
  if (frame.x > 15)
  {
    frame.x = 0;
  }

  texture_rect.left = frame.x * 32;
  texture_rect.top = frame.y * 32;
  flipX();
  sprite -> setTextureRect(texture_rect);
}

void Mushroom::flipX()
{
  if (velocity.x < 0)
  {
    texture_rect.width = -32;
    is_x_flipped = true;
  }
  else if (velocity.x > 0)
  {
    texture_rect.width = 32;
    is_x_flipped = false;
  }

  if (is_x_flipped)
  {
    texture_rect.left += 32;
  }
}
