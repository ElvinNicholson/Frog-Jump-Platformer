
#include "SpikedBall.h"

void SpikedBall::createSpikedBall(sf::Texture& chain_texture, sf::Texture& ball_texture, float x, float y)
{
  setTexture(chain_texture);
  sprite -> setOrigin(20, 20);
  setPosition(x + 20, y - 20);

  ball.setTexture(ball_texture);
  ball.getSprite()->setOrigin(20, -100);
  ball.setPosition(getPosition().x, getPosition().y);
}

void SpikedBall::rotation(float dt)
{
  sprite->rotate(speed * dt);
  ball.getSprite()->rotate(speed * dt);
}

bool SpikedBall::ballCollision(sf::Sprite* player)
{
  float player_width = player->getGlobalBounds().width;
  float player_height = player->getGlobalBounds().height;

  sf::FloatRect ball_bounds = ball.getSprite()->getGlobalBounds();

  sf::Vector2f player_min = player -> getPosition();
  sf::Vector2f player_max(player_min.x + player_width,
                          player_min.y + player_height);

  sf::Vector2f ball_min(ball_bounds.left, ball_bounds.top);
  sf::Vector2f ball_max(ball_bounds.left + ball_bounds.width,
                        ball_bounds.top + ball_bounds.height);
  ball_max.x += 16;
  ball_min.y += 16;
  ball_max.x -= 16;
  ball_max.y -= 16;

  if (
    ball_min.x < player_max.x &&
    ball_max.x > player_min.x &&
    ball_min.y < player_max.y &&
    ball_max.y > player_min.y)
  {
    return true;
  }
  else
  {
    return false;
  }
}
