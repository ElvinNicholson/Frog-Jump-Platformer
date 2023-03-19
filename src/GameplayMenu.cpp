
#include "GameplayMenu.h"

GameplayMenu::GameplayMenu()
{
  font.loadFromFile("Data/Fonts/ThaleahFat.ttf");

  health_bar.initialiseSprite(health_texture, "Data/Images/Other/Healthbar.png");
  health_texture_rect = sf::IntRect(858, 0, 286, 51);
  health_bar.getSprite()->setTextureRect(health_texture_rect);
  health_bar.setPosition(8, 8);

  grey_overlay_texture.loadFromFile("Data/Images/Other/Grey_Overlay.png");
  grey_overlay_texture.setRepeated(true);
  grey_overlay.setTexture(grey_overlay_texture);
  grey_overlay.setTextureRect(sf::IntRect(0, 0, 1080, 720));

  pause_menu.initialiseSprite(pause_menu_texture, "Data/Images/Other/Pause Menu.png");
  pause_menu.setPosition(540 - pause_menu.getSprite()->getGlobalBounds().width/2, 0);

  sf::Vector2f menu_pos = pause_menu.getPosition();

  button_back.initialiseSprite(button_back_texture, "Data/Images/Other/Button_Back.png");
  button_back.setOriginCentre();
  button_back.setPosition(menu_pos.x + 102, menu_pos.y + 156);

  button_bool_texture.loadFromFile("Data/Images/Other/Button_Bool.png");
  button_bool_sfx.setTexture(button_bool_texture);
  button_bool_rect_sfx = sf::IntRect(42, 0, 42, 42);
  button_bool_sfx.getSprite()->setTextureRect(button_bool_rect_sfx);
  button_bool_sfx.setOriginCentre();
  button_bool_sfx.setPosition(menu_pos.x + 399, menu_pos.y + 285);

  button_bool_music.setTexture(button_bool_texture);
  button_bool_rect_music = sf::IntRect(42, 0, 42, 42);
  button_bool_music.getSprite()->setTextureRect(button_bool_rect_music);
  button_bool_music.setOriginCentre();
  button_bool_music.setPosition(menu_pos.x + 399, menu_pos.y + 234);

  button_restart.initialiseSprite(button_restart_texture, "Data/Images/Other/Button_Restart.png");
  button_restart.setOriginCentre();
  button_restart.setPosition(menu_pos.x + 288, menu_pos.y + 390);

  button_exit.initialiseSprite(button_exit_texture, "Data/Images/Other/Button_Exit.png");
  button_exit.setOriginCentre();
  button_exit.setPosition(menu_pos.x + 288, menu_pos.y + 504);

  over_menu.initialiseSprite(over_menu_texture, "Data/Images/Other/Over Menu.png");
  over_menu.setPosition(540 - over_menu.getSprite()->getGlobalBounds().width/2, 0);

  button_restart_small.initialiseSprite(button_restart_small_texture, "Data/Images/Other/Button_Restart_Small.png");
  button_restart_small.setOriginCentre();
  button_restart_small.setPosition(menu_pos.x + 201, menu_pos.y + 432);

  button_exit_small.initialiseSprite(button_exit_small_texture, "Data/Images/Other/Button_Exit_Small.png");
  button_exit_small.setOriginCentre();
  button_exit_small.setPosition(menu_pos.x + 375, menu_pos.y + 432);

  level_banner.initialiseSprite(level_banner_texture, "Data/Images/Other/Level Banner.png");
  level_banner.setPosition(menu_pos.x + 132, menu_pos.y + 51);

  over_score.setFont(font);
  over_score.setCharacterSize(64);
  over_score.setFillColor(sf::Color(51, 50, 61));
  over_score.setOutlineThickness(3);
  over_score.setOutlineColor(sf::Color(243, 243, 243));

  score_counter.setFont(font);
  score_counter.setCharacterSize(40);
  score_counter.setFillColor(sf::Color(51, 50, 61));
  score_counter.setOutlineThickness(2);
  score_counter.setOutlineColor(sf::Color(243, 243, 243));
  score_counter.setPosition(835, 10);

  scoreboard.initialiseSprite(scoreboard_texture, "Data/Images/Other/Scoreboard.png");
  scoreboard.setPosition(1072 - scoreboard.getSprite()->getGlobalBounds().width, 8);
}

void GameplayMenu::renderMenu(sf::RenderWindow* window)
{
  window -> draw(*health_bar.getSprite());
  window -> draw(*scoreboard.getSprite());
  window -> draw(score_counter);

  if (paused)
  {
    window -> draw(grey_overlay);
    if (finished)
    {
      window -> draw(*over_menu.getSprite());
      window -> draw(*button_restart_small.getSprite());
      window -> draw(*button_exit_small.getSprite());
      window -> draw(*level_banner.getSprite());
      window -> draw(over_score);
    }
    else
    {
      window -> draw(*pause_menu.getSprite());
      window -> draw(*button_back.getSprite());
      window -> draw(*button_bool_sfx.getSprite());
      window -> draw(*button_bool_music.getSprite());
      window -> draw(*button_restart.getSprite());
      window -> draw(*button_exit.getSprite());
    }
  }
}

bool GameplayMenu::mouseCollision(sf::Sprite* sprite, sf::Vector2i mouse_pos)
{
  float sprite_width = sprite->getGlobalBounds().width;
  float sprite_height = sprite->getGlobalBounds().height;

  sf::Vector2f sprite_min = sprite -> getPosition();
  sprite_min.x -= sprite_width/2;
  sprite_min.y -= sprite_height/2;
  sf::Vector2f sprite_max(sprite_min.x + sprite_width, sprite_min.y + sprite_height);

  if (
    mouse_pos.x < sprite_max.x &&
    mouse_pos.x > sprite_min.x &&
    mouse_pos.y < sprite_max.y &&
    mouse_pos.y > sprite_min.y)
  {
    return true;
  }
  else
  {
    return false;
  }
}

void GameplayMenu::updateHealth(int health)
{
  health_texture_rect.left = health * 286;
  health_bar.getSprite()->setTextureRect(health_texture_rect);
}

void GameplayMenu::updateButtonBool()
{
  if (sfx)
  {
    button_bool_rect_sfx.left = 42;
    button_bool_sfx.getSprite()->setTextureRect(button_bool_rect_sfx);
  }
  else
  {
    button_bool_rect_sfx.left = 0;
    button_bool_sfx.getSprite()->setTextureRect(button_bool_rect_sfx);
  }

  if (music)
  {
    button_bool_rect_music.left = 42;
    button_bool_music.getSprite()->setTextureRect(button_bool_rect_music);
  }
  else
  {
    button_bool_rect_music.left = 0;
    button_bool_music.getSprite()->setTextureRect(button_bool_rect_music);
  }
}

void GameplayMenu::updateScore(int score)
{
  score_counter.setString("SCORE : " + std::to_string(score));
}

void GameplayMenu::setOverMenu(bool result, int score)
{
  finished = true;
  paused = true;

  if (result)
  {
    level_banner_rect = sf::IntRect(321, 0, 321, 66);
    level_banner.getSprite()->setTextureRect(level_banner_rect);
  }
  else
  {
    level_banner_rect = sf::IntRect(0, 0, 321, 66);
    level_banner.getSprite()->setTextureRect(level_banner_rect);
  }

  over_score.setString("SCORE : " + std::to_string(score));
  over_score.setPosition(over_menu.getPosition().x + 288 - over_score.getGlobalBounds().width/2, over_menu.getPosition().y + 200);
}

bool GameplayMenu::buttonHandler(
  sf::Sprite* button, sf::Vector2i click_pos, sf::Vector2i mouse_pos)
{
  if (mouseCollision(button, click_pos))
  {
    button->setScale(0.9, 0.9);
    return true;
  }
  else if (mouseCollision(button, mouse_pos))
  {
    button->setScale(1.1, 1.1);
    return false;
  }
  else
  {
    button->setScale(1, 1);
    return false;
  }
}
