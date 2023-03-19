
#ifndef PLATFORMERSFML_GAMEOBJECT_H
#define PLATFORMERSFML_GAMEOBJECT_H

// Game engine
#include <SFML/Graphics.hpp>

class GameObject
{
 public:
  GameObject();
  ~GameObject();

  bool initialiseSprite(sf::Texture &texture, std::string filename);
  bool setTexture(sf::Texture &texture);
  bool setOriginCentre();
  bool setPosition(float x, float y);
  sf::Sprite* getSprite();
  sf::Vector2f getPosition();

  bool visible = true;

 protected:
  sf::Sprite* sprite = nullptr;

 private:

};

#endif // PLATFORMERSFML_GAMEOBJECT_H
