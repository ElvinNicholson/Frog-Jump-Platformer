
#ifndef PLATFORMERSFML_GAMEPLAY_H
#define PLATFORMERSFML_GAMEPLAY_H

// System libs
#include <fstream>
#include <iostream>

// Game engine
#include <SFML/Graphics.hpp>

// Game codebase
#include "Gameobjects/Block.h"
#include "Gameobjects/Collectible.h"
#include "Gameobjects/Door.h"
#include "Gameobjects/Gameobject.h"
#include "Gameobjects/Mushroom.h"
#include "Gameobjects/Player.h"
#include "Gameobjects/SpikedBall.h"
#include "GameplayAudio.h"
#include "GameplayMenu.h"
#include "Gamestate.h"
#include "Level.h"

class Gameplay
{
 public:
  Gameplay();
  ~Gameplay();

  void updateGame(float dt);
  void renderGameplay(sf::RenderWindow* window);
  void keyPressedGameplay(sf::Event event);
  void createLevel();
  void startGame(Level level);

  Gamestate* current_state;
  Level selected_level;
  sf::Vector2i click_pos;
  sf::Vector2i mouse_pos;

 protected:

 private:
  void getFilename();
  void getObjectNumbers();
  void movePlayer(float dt);
  void playerHandler(float dt);
  void moveMushrooms(float dt, int i);
  void mushroomsHandler(float dt);
  void collectibleHandler(float dt);
  void doorHandler(float dt);
  void spikedBallHandler(float dt);
  void spikeHandler();
  void pauseMenuHandler();
  void overMenuHandler();
  void checkGameStatus();
  void writeScore() const;

  bool is_first_game = true;

  std::string filename;
  int score_line;

  GameplayMenu menu;
  GameplayAudio audio;

  int number_of_blocks;
  Block* blocks_array;
  sf::Texture block_texture;

  int number_of_spikes;
  Block* spikes_array;

  int number_of_mushrooms;
  Mushroom* mushrooms_array;
  sf::Texture mushroom_texture;

  int score;
  bool key_collected;
  int number_of_collectibles;
  Collectible* collectible_array;
  sf::Texture collectible_texture;

  int number_of_ball;
  SpikedBall* spiked_ball_array;
  sf::Texture chain_texture;
  sf::Texture ball_texture;

  Player player;

  Door door;
  bool played_door_sound = false;

  GameObject tutorial;
  sf::Texture tutorial_texture;
};

#endif // PLATFORMERSFML_GAMEPLAY_H
