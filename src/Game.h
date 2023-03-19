
#ifndef PLATFORMER_GAME_H
#define PLATFORMER_GAME_H

// Game engine
#include <SFML/Graphics.hpp>

// Game codebase
#include "Gameobjects/Tittle.h"
#include "Gameplay.h"
#include "Gamestate.h"

class Game
{
 public:
  Game(sf::RenderWindow& window);
  ~Game();
  bool init();
  void update(float dt);
  void render();
  void mouseClicked(sf::Event event);
  void keyPressed(sf::Event event);

 protected:

 private:
  void scrollingBackground(float dt);
  void checkNewState();

  Gamestate last_state;
  Gamestate current_state;
  Tittle tittle;
  Gameplay gameplay;

  sf::RenderWindow& window;
  sf::Vector2i click_pos;

  sf::Texture background_texture;
  sf::Sprite background_sprite;
  sf::IntRect background_rect;

};

#endif // PLATFORMER_GAME_H
