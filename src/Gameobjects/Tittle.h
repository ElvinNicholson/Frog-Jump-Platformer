
#ifndef PLATFORMERSFML_TITTLE_H
#define PLATFORMERSFML_TITTLE_H

// System libs
#include <iostream>
#include <fstream>

// Game engine
#include <SFML/Graphics.hpp>

// Game codebase
#include "../Gamestate.h"
#include "../Level.h"
#include "Gameobject.h"

class Tittle
{
 public:
  Tittle();

  void updateTittle(float dt);
  void renderTittle(sf::RenderWindow* window);
  void restartTittle();

  Gamestate* current_state;

  Level level_selected;

  sf::Vector2i click_pos;
  sf::Vector2i mouse_pos;

 protected:

 private:
  bool mouseCollision(sf::Sprite* sprite, sf::Vector2i mouse);

  void buttonHandler();
  void buttonLevel1();
  void buttonLevel2();
  void buttonLevel3();
  void buttonLevel4();
  void buttonLevelCustom();

  void updateScore();

  int score_line;
  bool clicked;

  sf::Texture tittle_texture;
  GameObject tittle;

  sf::Texture level_menu_texture;
  GameObject level_menu;

  sf::Texture button_level_texture;
  GameObject level_1;
  GameObject level_2;
  GameObject level_3;
  GameObject level_4;
  GameObject level_custom;

  sf::Font font;
  sf::Text score_text;
};

#endif // PLATFORMERSFML_TITTLE_H
