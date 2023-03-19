
#include "Gameplay.h"

Gameplay::Gameplay()
{
  block_texture.loadFromFile("Data/Images/Pixel Adventure 1/Free/Terrain/Terrain (16x16).png");
  mushroom_texture.loadFromFile("Data/Images/Pixel Adventure 2/Enemies/Mushroom/Run (32x32).png");
  collectible_texture.loadFromFile("Data/Images/Other/Collectible.png");
  chain_texture.loadFromFile("Data/Images/Pixel Adventure 1/Free/Traps/Spiked Ball/Chain.png");
  ball_texture.loadFromFile("Data/Images/Pixel Adventure 1/Free/Traps/Spiked Ball/Spiked Ball.png");

  tutorial.initialiseSprite(tutorial_texture, "Data/Images/Other/Tutorial.png");
}

Gameplay::~Gameplay()
{
  delete[] blocks_array;
  delete[] mushrooms_array;
  delete[] collectible_array;
  delete[] spikes_array;
  delete[] spiked_ball_array;
}

void Gameplay::updateGame(float dt)
{
  if (!menu.paused)
  {
    checkGameStatus();

    playerHandler(dt);

    mushroomsHandler(dt);

    collectibleHandler(dt);

    doorHandler(dt);

    spikedBallHandler(dt);

    spikeHandler();

    audio.audioHandler(menu.music, menu.sfx);
  }
  else
  {
    if (menu.finished)
    {
      overMenuHandler();
    }
    else
    {
      pauseMenuHandler();
    }
  }
}

void Gameplay::renderGameplay(sf::RenderWindow* window)
{
  mouse_pos = sf::Mouse::getPosition(*window);

  // Render blocks
  for (int i = 0; i < number_of_blocks; i++)
  {
    window -> draw(*blocks_array[i].getSprite());
  }

  // Render spikes
  for (int i = 0; i < number_of_spikes; i++)
  {
    window -> draw(*spikes_array[i].getSprite());
  }

  // Render mushrooms
  for (int i = 0; i < number_of_mushrooms; i++)
  {
    window -> draw(*mushrooms_array[i].getSprite());
  }

  // Render collectibles
  for (int i = 0; i < number_of_collectibles; i++)
  {
    if (collectible_array[i].visible)
    {
      window->draw(*collectible_array[i].getSprite());
    }
  }

  // Render tutorial for level 1
  if (selected_level == Level::LEVEL_1)
  {
    window -> draw(*tutorial.getSprite());
  }

  window -> draw(*door.getSprite());
  window -> draw(*player.getSprite());

  // Render spiked balls
  for (int i = 0; i < number_of_ball; i++)
  {
    window -> draw(*spiked_ball_array[i].getSprite());
    window -> draw(*spiked_ball_array[i].ball.getSprite());
  }

  menu.renderMenu(window);
}

void Gameplay::keyPressedGameplay(sf::Event event)
{
  // Wall jump controls
  if (
    event.type == sf::Event::KeyPressed &&
    event.key.code == sf::Keyboard::Space &&
    (player.can_wall_jump_left or player.can_wall_jump_right) &&
    player.is_wall_jump && !menu.paused
    )
  {
    player.is_wall_jump = false;
    player.velocity.y = 2;

    if (player.left_collide)
    {
      player.can_wall_jump_right = false;
      player.can_wall_jump_left = true;
      player.velocity.x = 2;
      player.getSprite() -> move(5, -5);
    }
    else if (player.right_collide)
    {
      player.can_wall_jump_left = false;
      player.can_wall_jump_right = true;
      player.velocity.x = -2;
      player.getSprite() -> move(-5, -5);
    }
    audio.playJump();
  }

  // Jump controls
  if (event.type == sf::Event::KeyPressed &&
      event.key.code == sf::Keyboard::Space && player.can_jump && !menu.paused)
  {
    player.can_jump = false;
    player.velocity.y = 2.2;
    player.getSprite() -> move(0, -5);
    audio.playJump();
  }

  // Pause controls
  if (event.key.code == sf::Keyboard::Escape && !menu.finished)
  {
    menu.paused = !menu.paused;
  }
}

void Gameplay::createLevel()
{
  getObjectNumbers();

  std::ifstream file(filename);
  std::string line;

  int block_idx = 0;
  int spike_idx = 0;
  int mushroom_idx = 0;
  int col_idx = 0;
  int ball_idx = 0;
  float y_offset = 0;

  mushrooms_array = new Mushroom[number_of_mushrooms];
  blocks_array = new Block[number_of_blocks];
  spikes_array = new Block[number_of_spikes];
  collectible_array = new Collectible[number_of_collectibles];
  spiked_ball_array = new SpikedBall[number_of_ball];

  while (std::getline(file, line))
  {
    float x_offset = 0;

    for (char c : line)
    {
      switch (c)
      {
        // BLOCK GRASS_NW
        case '1':
          blocks_array[block_idx].createBlock(block_texture,
                                                x_offset * 40,
                                                y_offset * 40,
                                                BlockType::GRASS_NW);
          block_idx += 1;
          break;

        // BLOCK GRASS_N
        case '2':
          blocks_array[block_idx].createBlock(block_texture,
                                                x_offset * 40,
                                                y_offset * 40,
                                                BlockType::GRASS_N);
          block_idx += 1;
          break;

        // BLOCK GRASS_NE
        case '3':
          blocks_array[block_idx].createBlock(block_texture,
                                                x_offset * 40,
                                                y_offset * 40,
                                                BlockType::GRASS_NE);
          block_idx += 1;
          break;

        // BLOCK GRASS_W
        case '4':
          blocks_array[block_idx].createBlock(block_texture,
                                                x_offset * 40,
                                                y_offset * 40,
                                                BlockType::GRASS_W);
          block_idx += 1;
          break;

        // BLOCK GRASS_M
        case '5':
          blocks_array[block_idx].createBlock(block_texture,
                                                x_offset * 40,
                                                y_offset * 40,
                                                BlockType::GRASS_M);
          block_idx += 1;
          break;

        // BLOCK GRASS_E
        case '6':
          blocks_array[block_idx].createBlock(block_texture,
                                                x_offset * 40,
                                                y_offset * 40,
                                                BlockType::GRASS_E);
          block_idx += 1;
          break;

        // BLOCK GRASS_SW
        case '7':
          blocks_array[block_idx].createBlock(block_texture,
                                                x_offset * 40,
                                                y_offset * 40,
                                                BlockType::GRASS_SW);
          block_idx += 1;
          break;

        // BLOCK GRASS_S
        case '8':
          blocks_array[block_idx].createBlock(block_texture,
                                                x_offset * 40,
                                                y_offset * 40,
                                                BlockType::GRASS_S);
          block_idx += 1;
          break;

        // BLOCK GRASS_SE
        case '9':
          blocks_array[block_idx].createBlock(block_texture,
                                                x_offset * 40,
                                                y_offset * 40,
                                                BlockType::GRASS_SE);
          block_idx += 1;
          break;

        // BLOCK GRASS_LEFT
        case '[':
          blocks_array[block_idx].createBlock(block_texture,
                                                x_offset * 40,
                                                y_offset * 40,
                                                BlockType::GRASS_LEFT);
          block_idx += 1;
          break;

        // BLOCK GRASS_RIGHT
        case ']':
          blocks_array[block_idx].createBlock(block_texture,
                                                x_offset * 40,
                                                y_offset * 40,
                                                BlockType::GRASS_RIGHT);
          block_idx += 1;
          break;

        // BLOCK BRICK_NW
        case '!':
          blocks_array[block_idx].createBlock(block_texture,
                                                x_offset * 40,
                                                y_offset * 40,
                                                BlockType::BRICK_NW);
          block_idx += 1;
          break;

        // BLOCK BRICK_N
        case '@':
          blocks_array[block_idx].createBlock(block_texture,
                                                x_offset * 40,
                                                y_offset * 40,
                                                BlockType::BRICK_N);
          block_idx += 1;
          break;

        // BLOCK BRICK_NE
        case '#':
          blocks_array[block_idx].createBlock(block_texture,
                                                x_offset * 40,
                                                y_offset * 40,
                                                BlockType::BRICK_NE);
          block_idx += 1;
          break;

        // BLOCK BRICK_W
        case '$':
          blocks_array[block_idx].createBlock(block_texture,
                                                x_offset * 40,
                                                y_offset * 40,
                                                BlockType::BRICK_W);
          block_idx += 1;
          break;

        // BLOCK BRICK_M
        case '%':
          blocks_array[block_idx].createBlock(block_texture,
                                                x_offset * 40,
                                                y_offset * 40,
                                                BlockType::BRICK_M);
          block_idx += 1;
          break;

        // BLOCK BRICK_E
        case '^':
          blocks_array[block_idx].createBlock(block_texture,
                                                x_offset * 40,
                                                y_offset * 40,
                                                BlockType::BRICK_E);
          block_idx += 1;
          break;

        // BLOCK BRICK_SW
        case '&':
          blocks_array[block_idx].createBlock(block_texture,
                                                x_offset * 40,
                                                y_offset * 40,
                                                BlockType::BRICK_SW);
          block_idx += 1;
          break;

        // BLOCK BRICK_S
        case '*':
          blocks_array[block_idx].createBlock(block_texture,
                                                x_offset * 40,
                                                y_offset * 40,
                                                BlockType::BRICK_S);
          block_idx += 1;
          break;

        // BLOCK BRICK_SE
        case '(':
          blocks_array[block_idx].createBlock(block_texture,
                                                x_offset * 40,
                                                y_offset * 40,
                                                BlockType::BRICK_SE);
          block_idx += 1;
          break;

        // BLOCK BLOCK
        case 'X':
          blocks_array[block_idx].createBlock(block_texture,
                                                x_offset * 40,
                                                y_offset * 40,
                                                BlockType::BLOCK);
          block_idx += 1;
          break;

        // PLAYER
        case 'P':
          player.setPosition(x_offset * 40, y_offset * 40);
          break;

        // MUSHROOM
        case 'M':
          mushrooms_array[mushroom_idx].createMushroom(mushroom_texture,
                                                         x_offset * 40,
                                                         y_offset * 40);
          mushroom_idx += 1;
          break;

        // COLLECTIBLE KEY
        case 'K':
          collectible_array[col_idx].createCollectible(collectible_texture,
                                                       x_offset * 40,
                                                       y_offset * 40,
                                                       CollectibleType::KEY);
          col_idx += 1;
          break;

        // COLLECTIBLE DIAMOND
        case 'D':
          collectible_array[col_idx].createCollectible(collectible_texture,
                                                       x_offset * 40,
                                                       y_offset * 40,
                                                       CollectibleType::DIAMOND);
          col_idx += 1;
          break;

        // COLLECTIBLE EMERALD
        case 'E':
          collectible_array[col_idx].createCollectible(collectible_texture,
                                                       x_offset * 40,
                                                       y_offset * 40,
                                                       CollectibleType::EMERALD);
          col_idx += 1;
          break;

        // COLLECTIBLE RUBY
        case 'R':
          collectible_array[col_idx].createCollectible(collectible_texture,
                                                       x_offset * 40,
                                                       y_offset * 40,
                                                       CollectibleType::RUBY);
          col_idx += 1;
          break;

        // DOOR
        case 'G':
          door.setPosition(x_offset * 40, y_offset * 40 - 10);
          break;

        // SPIKES
        case '/':
          spikes_array[spike_idx].createBlock(block_texture,
                                              x_offset * 40,
                                              y_offset * 40 + 20,
                                              BlockType::SPIKE);
          spike_idx += 1;
          break;

        // SPIKED BALLS
        case 'S':
          spiked_ball_array[ball_idx].createSpikedBall(chain_texture,
                                                       ball_texture,
                                                       x_offset * 40,
                                                       y_offset * 40);
          ball_idx += 1;
          break;
      }
      x_offset += 1;
    }
    y_offset += 1;
  }
  file.close();
}

void Gameplay::startGame(Level level)
{
  // Get level info
  selected_level = level;
  getFilename();

  // Restart game
  click_pos = sf::Vector2i (0, 0);
  player.restartPlayer();
  door.resetDoor();
  score = 0;
  key_collected = false;
  played_door_sound = false;

  // Restart menu
  menu.updateScore(score);
  menu.updateHealth(player.health);
  menu.paused = false;
  menu.finished = false;

  if (!is_first_game)
  {
    delete[] blocks_array;
    delete[] mushrooms_array;
    delete[] collectible_array;
    delete[] spikes_array;
  }
  else
  {
    is_first_game = false;
  }

  createLevel();
}

void Gameplay::getFilename()
{
  switch (selected_level)
  {
    case Level::LEVEL_1:
    filename = "Data/Levels/Level 1.txt";
    score_line = 0;
    break;

    case Level::LEVEL_2:
      filename = "Data/Levels/Level 2.txt";
      score_line = 1;
      break;

    case Level::LEVEL_3:
      filename = "Data/Levels/Level 3.txt";
      score_line = 2;
      break;

    case Level::LEVEL_4:
      filename = "Data/Levels/Level 4.txt";
      score_line = 3;
      break;

    case Level::LEVEL_CUSTOM:
      filename = "Data/Levels/Custom.txt";
      score_line = 4;
      break;
  }
}

void Gameplay::getObjectNumbers()
{
  std::ifstream file(filename);
  std::string line;
  number_of_blocks = 0;
  number_of_mushrooms = 0;
  number_of_collectibles = 0;
  number_of_spikes = 0;
  number_of_ball         = 0;

  while (std::getline(file, line))
  {
    for (char c : line)
    {
      switch (c)
      {
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '[':
        case ']':
        case '!':
        case '@':
        case '#':
        case '$':
        case '%':
        case '^':
        case '&':
        case '*':
        case '(':
        case 'X':
          number_of_blocks += 1;
          break;

        case 'M':
          number_of_mushrooms += 1;
          break;

        case 'K':
        case 'D':
        case 'E':
        case 'R':
          number_of_collectibles += 1;
          break;

        case '/':
          number_of_spikes += 1;
          break;

        case 'S':
          number_of_ball += 1;
          break;
      }
    }
  }
  file.close();
}

void Gameplay::movePlayer(float dt)
{
  player.gravity(dt);

  sf::Vector2f vel = player.velocity;
  float speed = player.speed;

  sf::Vector2f old_pos = player.getPosition();
  sf::Vector2f new_pos(old_pos.x + (vel.x * speed * dt),
                       old_pos.y + (-vel.y * speed * dt));

  bool horizontal_collision_found = false;
  bool ground_collision_found = false;
  bool ceiling_collision_found = false;

  player.right_collide = false;
  player.left_collide = false;

  // Check player collisions
  for (int i = 0; i < number_of_blocks; i++)
  {
    if (!horizontal_collision_found && vel.x !=0)
    {
      if (player.horizontalCollision(blocks_array[i].getSprite(), new_pos))
      {
        horizontal_collision_found = true;
      }
    }
    if (!ground_collision_found)
    {
      if (player.groundCollision(blocks_array[i].getSprite()))
      {
        ground_collision_found = true;
      }
    }
    if (!ceiling_collision_found)
    {
      if (player.ceilingCollision(blocks_array[i].getSprite()))
      {
        ceiling_collision_found = true;
      }
    }
  }

  vel = player.velocity;

  // Player is mid-air
  if (!ground_collision_found)
  {
    player.is_grounded = false;
    player.can_jump = false;
  }

  // Player is wall sliding
  if (horizontal_collision_found && !ground_collision_found && vel.y < 1)
  {
    player.is_wall_jump = true;
  }
  else
  {
    player.is_wall_jump = false;
  }

  // Move player across Y-axis if player is mid-air
  if (!player.is_grounded)
  {
    player.getSprite() -> move(0, -vel.y * speed * dt);
  }
  // Move player across X-axis if player is not walking into a block
  if (!horizontal_collision_found)
  {
    player.getSprite() -> move(vel.x * speed * dt, 0);
  }
}

void Gameplay::playerHandler(float dt)
{
  player.animations(dt);
  player.movementInput(dt);
  movePlayer(dt);

  if (player.is_hit)
  {
    player.hitHandler(dt);
  }
}

void Gameplay::moveMushrooms(float dt, int i)
{
  mushrooms_array[i].animations(dt);
  mushrooms_array[i].movement();

  float vel_x = mushrooms_array[i].velocity.x;
  float speed = mushrooms_array[i].speed;

  sf::Vector2f old_pos = mushrooms_array[i].getPosition();
  sf::Vector2f new_pos(old_pos.x + (vel_x * speed * dt), old_pos.y);

  bool block_collision_found = false;
  bool ground_collision_found = false;

  // Check mushroom collisions
  for (int x = 0; x < number_of_blocks; x++)
  {
    if (!block_collision_found)
    {
      if (mushrooms_array[i].blockCollision(
            blocks_array[x].getSprite(), new_pos))
      {
        block_collision_found = true;
      }
    }
    if (!ground_collision_found)
    {
      if (mushrooms_array[i].groundCollision(
            blocks_array[x].getSprite(), new_pos))
      {
        ground_collision_found = true;
      }
    }
  }

  // Turn mushroom around if it is walking into a ledge
  if (!ground_collision_found)
  {
    mushrooms_array[i].going_right = !mushrooms_array[i].going_right;
    mushrooms_array[i].going_left = !mushrooms_array[i].going_left;
  }

  mushrooms_array[i].getSprite() -> move (vel_x * speed * dt, 0);
}

void Gameplay::mushroomsHandler(float dt)
{
  for (int i = 0; i < number_of_mushrooms; i++)
  {
    moveMushrooms(dt, i);

    // Check if player collides with mushroom
    if (!player.is_hit)
    {
      if (player.normalCollision(mushrooms_array[i].getSprite()))
      {
        player.is_hit = true;
        player.health -= 1;
        menu.updateHealth(player.health);
        audio.playHit();
      }
    }
  }
}

void Gameplay::collectibleHandler(float dt)
{
  for (int i = 0; i < number_of_collectibles; i ++)
  {
    if (collectible_array[i].visible)
    {
      collectible_array[i].animations(dt);

      if (player.normalCollision(collectible_array[i].getSprite()))
      {
        if (collectible_array[i].type == CollectibleType::KEY)
        {
          key_collected = true;
        }

        collectible_array[i].visible = false;
        score += collectible_array[i].value;
        menu.updateScore(score);
        audio.playCoin();
      }
    }
  }
}

void Gameplay::doorHandler(float dt)
{
  if (key_collected)
  {
    if (player.normalCollision(door.getSprite()))
    {
      door.player_is_near = true;

      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
      {
        writeScore();
        audio.playWin();
        menu.setOverMenu(true, score);
      }
    }

    door.animations(dt);

    // Sound controls for door
    if (door.play_anim && !played_door_sound)
    {
      audio.playDoor();
      played_door_sound = true;
    }
  }
}

void Gameplay::spikedBallHandler(float dt)
{
  for (int i = 0; i < number_of_ball; i ++)
  {
    spiked_ball_array[i].rotation(dt);

    if (!player.is_hit)
    {
      if (spiked_ball_array[i].ballCollision(player.getSprite()))
      {
        audio.playHit();
        player.is_hit = true;
        player.health -= 1;
        menu.updateHealth(player.health);
      }
    }
  }
}

void Gameplay::spikeHandler()
{
  for (int i = 0; i < number_of_spikes; i ++)
  {
    if (!player.is_hit)
    {
      if (player.normalCollision(spikes_array[i].getSprite()))
      {
        audio.playHit();
        player.is_hit = true;
        player.health -= 1;
        player.velocity.y = 2;
        menu.updateHealth(player.health);
      }
    }
  }
}

void Gameplay::pauseMenuHandler()
{
  // BACK BUTTON
  if (GameplayMenu::buttonHandler(menu.button_back.getSprite(),
                                  click_pos, mouse_pos))
  {
    menu.paused = false;
  }

  // SFX BUTTON
  if (GameplayMenu::buttonHandler(menu.button_bool_sfx.getSprite(),
                                  click_pos, mouse_pos))
  {
    menu.sfx = !menu.sfx;
    menu.updateButtonBool();
  }

  // MUSIC BUTTON
  if (GameplayMenu::buttonHandler(menu.button_bool_music.getSprite(),
                                  click_pos, mouse_pos))
  {
    menu.music = !menu.music;
    menu.updateButtonBool();
  }

  // RESTART BUTTON
  if (GameplayMenu::buttonHandler(menu.button_restart.getSprite(),
                                  click_pos, mouse_pos))
  {
    startGame(selected_level);
    menu.paused = false;
  }

  // EXIT BUTTON
  if (GameplayMenu::buttonHandler(menu.button_exit.getSprite(),
                                  click_pos, mouse_pos))
  {
    audio.restartAudio();
    *current_state = Gamestate::TITTLE;
    menu.paused = false;
  }

  click_pos = sf::Vector2i (0, 0);
}

void Gameplay::overMenuHandler()
{
  // SMALL RESTART BUTTON
  if (GameplayMenu::buttonHandler(menu.button_restart_small.getSprite(),
                                  click_pos, mouse_pos))
  {
    startGame(selected_level);
    menu.paused = false;
  }

  // SMALL EXIT BUTTON
  if (GameplayMenu::buttonHandler(menu.button_exit_small.getSprite(),
                                  click_pos, mouse_pos))
  {
    audio.restartAudio();
    *current_state = Gamestate::TITTLE;
    menu.paused = false;
  }
}

void Gameplay::checkGameStatus()
{
  if (player.health == 0)
  {
    audio.playLoose();
    menu.setOverMenu(false, score);
  }
}

void Gameplay::writeScore() const
{
  std::ifstream in_file("Data/Levels/Scores.txt");
  std::string in_line;

  std::string score_0;
  std::string score_1;
  std::string score_2;
  std::string score_3;
  std::string score_4;

  int current_in_line = 0;

  // Move scores onto scratch variables
  while (std::getline(in_file, in_line))
  {
    switch(current_in_line)
    {
      case 0:
        score_0 = in_line;
        break;

      case 1:
        score_1 = in_line;
        break;

      case 2:
        score_2 = in_line;
        break;

      case 3:
        score_3 = in_line;
        break;

      case 4:
        score_4 = in_line;
        break;
    }
    current_in_line += 1;
  }

  in_file.close();

  std::ofstream out_file("Data/Levels/Scores.txt");

  switch(score_line)
  {
    case 0:
      if (score > std::stoi(score_0))
      {
        score_0 = std::to_string(score);
      }
      break;

    case 1:
      if (score > std::stoi(score_1))
      {
        score_1 = std::to_string(score);
      }
      break;

    case 2:
      if (score > std::stoi(score_2))
      {
        score_2 = std::to_string(score);
      }
      break;

    case 3:
      if (score > std::stoi(score_3))
      {
        score_3 = std::to_string(score);
      }
      break;

    case 4:
      if (score > std::stoi(score_4))
      {
        score_4 = std::to_string(score);
      }
      break;
  }

  // Rewrite new scores from scratch variables
  out_file << score_0 + "\n";
  out_file << score_1 + "\n";
  out_file << score_2 + "\n";
  out_file << score_3 + "\n";
  out_file << score_4 + "\n";

  out_file.close();
}
