
#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow& game_window)
  : window(game_window)
{
  srand(time(NULL));
  init();
}

Game::~Game()
{

}

bool Game::init()
{
  current_state = Gamestate::TITTLE;
  last_state = current_state;
  tittle.current_state = &current_state;
  gameplay.current_state = &current_state;


  background_texture.loadFromFile("Data/Images/Pixel Adventure 1/Free/Background/Brown.png");
  background_texture.setRepeated(true);
  background_sprite.setTexture(background_texture);
  background_rect = sf::IntRect(0, 0, 1080, 720);
  background_sprite.setTextureRect(background_rect);

  return true;
}

void Game::update(float dt)
{
  checkNewState();
  scrollingBackground(dt);

  switch(current_state)
  {
    case Gamestate::TITTLE:
      tittle.updateTittle(dt);
      break;

    case Gamestate::IN_GAME:
      gameplay.updateGame(dt);
      break;
  }
}

void Game::render()
{
  window.draw(background_sprite);
  switch(current_state)
  {
    case Gamestate::TITTLE:
      tittle.renderTittle(&window);
      break;

    case Gamestate::IN_GAME:
      gameplay.renderGameplay(&window);
      break;
  }
}

void Game::mouseClicked(sf::Event event)
{
  // Get the click position
  sf::Vector2i click = sf::Mouse::getPosition(window);
  gameplay.click_pos = click;
  tittle.click_pos = click;

}

void Game::keyPressed(sf::Event event)
{
  switch(current_state)
  {
    case Gamestate::TITTLE:
      break;

    case Gamestate::IN_GAME:
      gameplay.keyPressedGameplay(event);
      break;
  }
}

void Game::scrollingBackground(float dt)
{
  if (background_rect.top < 64)
  {
    background_rect.top += dt * 100;
  }
  else
  {
    background_rect.top = 0;
  }
  background_sprite.setTextureRect(background_rect);
}

void Game::checkNewState()
{
  if (last_state != current_state)
  {
    last_state = current_state;
    switch(current_state)
    {
      case Gamestate::TITTLE:
        tittle.restartTittle();
        break;

      case Gamestate::IN_GAME:
        gameplay.startGame(tittle.level_selected);
        break;
    }
  }
}
