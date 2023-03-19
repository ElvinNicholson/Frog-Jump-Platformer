
#ifndef PLATFORMERSFML_GAMEPLAYMENU_H
#define PLATFORMERSFML_GAMEPLAYMENU_H

// Game codebase
#include "Gameobjects/Gameobject.h"

class GameplayMenu
{
 public:
  GameplayMenu();

  void renderMenu(sf::RenderWindow* window);
  void updateHealth(int health);
  void updateButtonBool();
  void updateScore(int score);
  void setOverMenu(bool result, int score);
  static bool buttonHandler(sf::Sprite* button, sf::Vector2i click_pos, sf::Vector2i mouse_pos);

  // Gameplay UI elements
  GameObject health_bar;
  GameObject scoreboard;
  sf::Text score_counter;

  // Pause Menu elements
  GameObject pause_menu;
  GameObject button_back;
  GameObject button_bool_music;
  GameObject button_bool_sfx;
  GameObject button_restart;
  GameObject button_exit;
  sf::Sprite grey_overlay;

  // Game Over Menu elements
  GameObject over_menu;
  GameObject button_restart_small;
  GameObject button_exit_small;
  GameObject level_banner;
  sf::Text over_score;

  bool paused = false;
  bool finished = false;
  bool music = true;
  bool sfx = true;

 protected:

 private:
  static bool mouseCollision(sf::Sprite* sprite, sf::Vector2i mouse_pos);

  sf::Font font;

  // Gameplay UI elements
  sf::Texture health_texture;
  sf::IntRect health_texture_rect;
  sf::Texture scoreboard_texture;

  // Pause menu elements
  sf::Texture grey_overlay_texture;
  sf::Texture pause_menu_texture;
  sf::Texture button_back_texture;
  sf::Texture button_bool_texture;
  sf::IntRect button_bool_rect_music;
  sf::IntRect button_bool_rect_sfx;
  sf::Texture button_restart_texture;
  sf::Texture button_exit_texture;

  // Game Over menu elements
  sf::Texture over_menu_texture;
  sf::Texture button_restart_small_texture;
  sf::Texture button_exit_small_texture;
  sf::Texture level_banner_texture;
  sf::IntRect level_banner_rect;

};

#endif // PLATFORMERSFML_GAMEPLAYMENU_H
