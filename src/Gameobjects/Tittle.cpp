
#include "Tittle.h"

Tittle::Tittle()
{
  font.loadFromFile("Data/Fonts/ThaleahFat.ttf");

  tittle.initialiseSprite(tittle_texture, "Data/Images/Other/Tittle.png");
  tittle.setPosition(50, 360 - tittle.getSprite()->getGlobalBounds().height/2);

  level_menu.initialiseSprite(level_menu_texture, "Data/Images/Other/Level Menu.png");
  level_menu.setPosition(1080 - level_menu.getSprite()->getGlobalBounds().width, 100);

  sf::Vector2f menu_pos = level_menu.getPosition();

  button_level_texture.loadFromFile("Data/Images/Other/Button_Levels.png");
  level_1.setTexture(button_level_texture);
  level_1.getSprite()->setTextureRect(sf::IntRect(0, 0, 42, 42));
  level_1.setOriginCentre();
  level_1.setPosition(menu_pos.x + 216, menu_pos.y + 207);

  level_2.setTexture(button_level_texture);
  level_2.getSprite()->setTextureRect(sf::IntRect(42, 0, 42, 42));
  level_2.setOriginCentre();
  level_2.setPosition(menu_pos.x + 288, menu_pos.y + 207);

  level_3.setTexture(button_level_texture);
  level_3.getSprite()->setTextureRect(sf::IntRect(84, 0, 42, 42));
  level_3.setOriginCentre();
  level_3.setPosition(menu_pos.x + 360, menu_pos.y + 207);

  level_4.setTexture(button_level_texture);
  level_4.getSprite()->setTextureRect(sf::IntRect(126, 0, 42, 42));
  level_4.setOriginCentre();
  level_4.setPosition(menu_pos.x + 216, menu_pos.y + 279);

  level_custom.setTexture(button_level_texture);
  level_custom.getSprite()->setTextureRect(sf::IntRect(0, 42, 126, 42));
  level_custom.setOriginCentre();
  level_custom.setPosition(menu_pos.x + 324, menu_pos.y + 279);

  score_text.setFont(font);
  score_text.setCharacterSize(35);
  score_text.setString("SCORE");
  score_text.setFillColor(sf::Color(51, 50, 61));
  score_text.setOutlineThickness(2);
  score_text.setOutlineColor(sf::Color(243, 243, 243));
  score_text.setPosition(menu_pos.x + 288 - score_text.getGlobalBounds().width/2, menu_pos.y + 352);

  restartTittle();
}

void Tittle::updateTittle(float dt)
{
  buttonHandler();
}

void Tittle::renderTittle(sf::RenderWindow* window)
{
  mouse_pos = sf::Mouse::getPosition(*window);

  window->draw(*tittle.getSprite());
  window -> draw(*level_menu.getSprite());
  window -> draw(*level_1.getSprite());
  window -> draw(*level_2.getSprite());
  window -> draw(*level_3.getSprite());
  window -> draw(*level_4.getSprite());
  window -> draw(*level_custom.getSprite());
  window -> draw(score_text);

  // Putting this anywhere else causes error (0xC0000005)
  if (clicked)
  {
    restartTittle();
    *current_state = Gamestate::IN_GAME;
  }
}

void Tittle::buttonHandler()
{
  buttonLevel1();

  buttonLevel2();

  buttonLevel3();

  buttonLevel4();

  buttonLevelCustom();

  click_pos = sf::Vector2i (0, 0);
}

void Tittle::buttonLevel1()
{
  if (mouseCollision(level_1.getSprite(), click_pos))
  {
    level_1.getSprite()->setScale(0.9, 0.9);
    level_selected = Level::LEVEL_1;
    clicked        = true;
  }
  else if (mouseCollision(level_1.getSprite(), mouse_pos))
  {
    level_1.getSprite()->setScale(1.1, 1.1);
    score_line = 0;
    updateScore();
  }
  else
  {
    level_1.getSprite()->setScale(1, 1);
  }
}

void Tittle::buttonLevel2()
{
  if (mouseCollision(level_2.getSprite(), click_pos))
  {
    level_2.getSprite()->setScale(0.9, 0.9);
    level_selected = Level::LEVEL_2;
    clicked        = true;
  }
  else if (mouseCollision(level_2.getSprite(), mouse_pos))
  {
    level_2.getSprite()->setScale(1.1, 1.1);
    score_line = 1;
    updateScore();
  }
  else
  {
    level_2.getSprite()->setScale(1, 1);
  }
}

void Tittle::buttonLevel3()
{
  if (mouseCollision(level_3.getSprite(), click_pos))
  {
    level_3.getSprite()->setScale(0.9, 0.9);
    level_selected = Level::LEVEL_3;
    clicked        = true;
  }
  else if (mouseCollision(level_3.getSprite(), mouse_pos))
  {
    level_3.getSprite()->setScale(1.1, 1.1);
    score_line = 2;
    updateScore();
  }
  else
  {
    level_3.getSprite()->setScale(1, 1);
  }
}

void Tittle::buttonLevel4()
{
  if (mouseCollision(level_4.getSprite(), click_pos))
  {
    level_4.getSprite()->setScale(0.9, 0.9);
    level_selected = Level::LEVEL_4;
    clicked        = true;
  }
  else if (mouseCollision(level_4.getSprite(), mouse_pos))
  {
    level_4.getSprite()->setScale(1.1, 1.1);
    score_line = 3;
    updateScore();
  }
  else
  {
    level_4.getSprite()->setScale(1, 1);
  }
}

void Tittle::buttonLevelCustom()
{
  if (mouseCollision(level_custom.getSprite(), click_pos))
  {
    level_custom.getSprite()->setScale(0.9, 0.9);
    level_selected = Level::LEVEL_CUSTOM;
    clicked        = true;
  }
  else if (mouseCollision(level_custom.getSprite(), mouse_pos))
  {
    level_custom.getSprite()->setScale(1.1, 1.1);
    score_line = 4;
    updateScore();
  }
  else
  {
    level_custom.getSprite()->setScale(1, 1);
  }
}

void Tittle::updateScore()
{
  std::ifstream file("Data/Levels/Scores.txt");
  std::string line;

  int current_line = 0;

  while (std::getline(file, line))
  {
    if (current_line == score_line)
    {
      score_text.setString("SCORE : " + line);
      score_text.setPosition(level_menu.getPosition().x + 288 - score_text.getGlobalBounds().width/2, level_menu.getPosition().y + 352);
      break;
    }
    current_line += 1;
  }
  file.close();
}

bool Tittle::mouseCollision(sf::Sprite* sprite, sf::Vector2i mouse)
{
  float sprite_width = sprite->getGlobalBounds().width;
  float sprite_height = sprite->getGlobalBounds().height;

  sf::Vector2f sprite_min = sprite -> getPosition();
  sprite_min.x -= sprite_width/2;
  sprite_min.y -= sprite_height/2;
  sf::Vector2f sprite_max(sprite_min.x + sprite_width, sprite_min.y + sprite_height);

  if (
    mouse.x < sprite_max.x &&
    mouse.x > sprite_min.x &&
    mouse.y < sprite_max.y &&
    mouse.y > sprite_min.y)
  {
    return true;
  }
  else
  {
    return false;
  }
}

void Tittle::restartTittle()
{
  clicked = false;
  click_pos = sf::Vector2i(0, 0);
}
