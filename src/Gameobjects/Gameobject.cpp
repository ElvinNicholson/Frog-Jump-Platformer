
#include "Gameobject.h"

GameObject::GameObject()
{
  sprite = new sf::Sprite();
}

GameObject::~GameObject()
{
  delete sprite;
}

bool GameObject::initialiseSprite(sf::Texture &texture, std::string filename)
{
  texture.loadFromFile(filename);
  sprite -> setTexture(texture);
  return true;
}

bool GameObject::setTexture(sf::Texture &texture)
{
  sprite -> setTexture(texture);
  return true;
}

bool GameObject::setOriginCentre()
{
  sprite -> setOrigin(sprite->getGlobalBounds().width/2, sprite->getGlobalBounds().height/2);
  return true;
}

bool GameObject::setPosition(float x, float y)
{
  sprite -> setPosition(x, y);
  return true;
}

sf::Sprite* GameObject::getSprite()
{
  return sprite;
}

sf::Vector2f GameObject::getPosition()
{
  return sprite -> getPosition();
}
