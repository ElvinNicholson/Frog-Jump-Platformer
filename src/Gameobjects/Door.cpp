
#include "Door.h"

Door::Door()
{
  initialiseSprite(texture, "Data/Images/Other/Door-Sheet.png");
  texture_rect = sf::IntRect(0, 0, 40, 50);
  sprite -> setTextureRect(texture_rect);
  player_is_near = false;
  door_open = false;
  play_anim = false;
}

void Door::animations(float dt)
{
  if (play_anim)
  {
    frame_time -= dt;
    if (frame_time < 0)
    {
      frame_time = 0.1;
      frame.x += 1;
    }
  }

  if (!player_is_near && !door_open)
  {
    frame.x = 0;
  }
  if (player_is_near && !door_open)
  {
    play_anim = true;
    if (frame.x > 4)
    {
      play_anim = false;
      door_open = true;
      frame.x = 4;
    }
  }

  texture_rect.left = frame.x * 40;
  sprite -> setTextureRect(texture_rect);
}

void Door::resetDoor()
{
  player_is_near = false;
  door_open = false;
  play_anim = false;
  frame = sf::Vector2f(0, 0);
  texture_rect = sf::IntRect(0, 0, 40, 50);
  sprite -> setTextureRect(texture_rect);
}
