
#include "Player.h"

Player::Player()
{
  initialiseSprite(player_texture, "Data/Images/Pixel Adventure 1/Free/Main Characters/Ninja Frog/Frog Spritesheet.png");
  player_texture_rect = sf::IntRect(0, 0, 32, 32);
  sprite -> setTextureRect(player_texture_rect);
  sprite -> scale(1.25, 1.25);

  width = getSprite()->getGlobalBounds().width;
  height = getSprite()->getGlobalBounds().height;
}

void Player::movementInput(float dt)
{
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
  {
    if (velocity.x > -1)
    {
      velocity.x -= dt * 5;
    }
    else
    {
      velocity.x = -1;
    }
  }
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
  {
    if (velocity.x < 1)
    {
      velocity.x += dt * 5;
    }
    else
    {
      velocity.x = 1;
    }
  }
  else
  {
    velocity.x = 0;
  }
}

bool Player::horizontalCollision(sf::Sprite* sprite, sf::Vector2f new_pos)
{
  float sprite_width = sprite->getGlobalBounds().width;
  float sprite_height = sprite->getGlobalBounds().height;

  sf::Vector2f sprite_min = sprite -> getPosition();
  sf::Vector2f sprite_max(sprite_min.x + sprite_width,
                          sprite_min.y + sprite_height);

  sf::Vector2f player_min = new_pos;
  sf::Vector2f player_max(new_pos.x + width, new_pos.y + height);
  player_min.x += 2;
  player_min.y += 10;
  player_max.x -= 2;
  player_max.y -= 10;

  if (
    player_min.x < sprite_max.x &&
    player_max.x > sprite_min.x &&
    player_min.y < sprite_max.y &&
    player_max.y > sprite_min.y)
  {
    if (player_min.x > sprite_min.x)
    {
      left_collide = true;
    }
    else
    {
      right_collide = true;
    }
    return true;
  }
  else
  {
    return false;
  }
}

bool Player::groundCollision(sf::Sprite* sprite)
{
  float sprite_width = sprite->getGlobalBounds().width;
  float sprite_height = sprite->getGlobalBounds().height;

  sf::Vector2f sprite_min = sprite -> getPosition();
  sf::Vector2f sprite_max(sprite_min.x + sprite_width,
                          sprite_min.y + sprite_height);

  sf::Vector2f ground_min = getPosition();
  ground_min.y += height + 1;
  sf::Vector2f ground_max(ground_min.x + width, ground_min.y);
  ground_min.x += 5;
  ground_max.x -= 5;

  if (
    ground_min.x < sprite_max.x &&
    ground_max.x > sprite_min.x &&
    ground_min.y < sprite_max.y &&
    ground_max.y > sprite_min.y)
  {
    setPosition(getPosition().x, sprite_min.y - height);
    is_grounded = true;
    can_jump = true;
    can_wall_jump_right = true;
    can_wall_jump_left = true;
    velocity.y = 0;
    return true;
  }
  else
  {
    return false;
  }
}

bool Player::ceilingCollision(sf::Sprite* sprite)
{
  float sprite_width = sprite->getGlobalBounds().width;
  float sprite_height = sprite->getGlobalBounds().height;

  sf::Vector2f sprite_min = sprite -> getPosition();
  sf::Vector2f sprite_max(sprite_min.x + sprite_width,
                          sprite_min.y + sprite_height);

  sf::Vector2f top_min = getPosition();
  top_min.y -= 1;
  sf::Vector2f top_max(top_min.x + width, top_min.y);
  top_min.x += 5;
  top_max.x -= 5;

  if (
    top_min.x < sprite_max.x &&
    top_max.x > sprite_min.x &&
    top_min.y < sprite_max.y &&
    top_max.y > sprite_min.y)
  {
    setPosition(getPosition().x, sprite_min.y + height + 1);
    velocity.y = 0;
    return true;
  }
  else
  {
    return false;
  }
}

bool Player::normalCollision(sf::Sprite* sprite)
{
  float sprite_width = sprite->getGlobalBounds().width;
  float sprite_height = sprite->getGlobalBounds().height;

  sf::Vector2f sprite_min = sprite -> getPosition();
  sf::Vector2f sprite_max(sprite_min.x + sprite_width,
                          sprite_min.y + sprite_height);

  sf::Vector2f player_min = getPosition();
  sf::Vector2f player_max(player_min.x + width, player_min.y + height);

  if (
    player_min.x < sprite_max.x &&
    player_max.x > sprite_min.x &&
    player_min.y < sprite_max.y &&
    player_max.y > sprite_min.y)
  {
    return true;
  }
  else
  {
    return false;
  }
}

void Player::gravity(float dt)
{
  if (!is_grounded)
  {
    if (velocity.y > -5)
    {
      velocity.y -= 6 * dt;
    }
    else
    {
      velocity.y = -5;
    }
  }

  if (is_wall_jump && (can_wall_jump_right or can_wall_jump_left))
  {
    velocity.y = -1;
  }
}

void Player::animations(float dt)
{
  frame_time -= dt;
  if (frame_time < 0)
  {
    frame_time = 0.05;
    frame.x += 1;
  }

  if (is_hit)
  {
    hitAnimation();
  }
  else if (velocity.x == 0 && velocity.y == 0)
  {
    idleAnimation();
  }
  else if (velocity.x != 0 && velocity.y == 0)
  {
    walkAnimation();
  }
  else if (is_wall_jump)
  {
    wallJumpAnimation();
  }
  else if (velocity.y != 0)
  {
    jumpAnimation();
  }

  player_texture_rect.left = frame.x * 32;
  player_texture_rect.top = frame.y * 32;
  flipX();
  sprite -> setTextureRect(player_texture_rect);
}

void Player::flipX()
{
  if (velocity.x < 0)
  {
    player_texture_rect.width = -32;
    is_x_flipped = true;
  }
  else if (velocity.x > 0)
  {
    player_texture_rect.width = 32;
    is_x_flipped = false;
  }

  if (is_x_flipped)
  {
    player_texture_rect.left += 32;
  }
}

void Player::idleAnimation()
{
  frame.y = 0;
  if (frame.x > 10)
  {
    frame.x = 0;
  }
}

void Player::walkAnimation()
{
  frame.y = 1;
  if (frame.x > 11)
  {
    frame.x = 0;
  }
}

void Player::jumpAnimation()
{
  frame.y = 3;
  frame.x = 0;
}

void Player::wallJumpAnimation()
{
  frame.y = 4;
  frame.x = 0;
}

void Player::hitAnimation()
{
  frame.y = 2;
  if (frame.x > 6)
  {
    frame.x = 0;
  }
}

void Player::hitHandler(float dt)
{
  hit_cooldown -= dt;
  if (hit_cooldown < 0)
  {
    hit_cooldown = 1;
    is_hit = false;
  }
}

void Player::restartPlayer()
{
  health = 3;

  is_grounded = false;
  is_wall_jump = false;
  left_collide = false;
  right_collide = false;
  is_hit = false;

  can_jump = false;
  can_wall_jump_right = false;
  can_wall_jump_left = false;

  hit_cooldown = 1;
  frame_time = 0.05;
}
