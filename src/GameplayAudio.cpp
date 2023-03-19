
#include "GameplayAudio.h"

GameplayAudio::GameplayAudio()
{
  background_music.openFromFile("Data/Audio/8-bit Detective.wav");
  background_music.setLoop(true);
  background_music.setVolume(50);

  hit_buffer.loadFromFile("Data/Audio/sfx_damage_hit10.wav");
  hit.setBuffer(hit_buffer);

  door_buffer.loadFromFile("Data/Audio/sfx_movement_dooropen2.wav");
  door.setBuffer(door_buffer);

  jump_buffer.loadFromFile("Data/Audio/sfx_movement_jump1.wav");
  jump.setBuffer(jump_buffer);
  jump.setVolume(35);

  coin_buffer.loadFromFile("Data/Audio/sfx_coin_double1.wav");
  coin.setBuffer(coin_buffer);

  win_buffer.loadFromFile("Data/Audio/mixkit-video-game-win-2016.wav");
  win.setBuffer(win_buffer);
  win.setVolume(50);

  loose_buffer.loadFromFile("Data/Audio/mixkit-funny-fail-low-tone-2876.wav");
  loose.setBuffer(loose_buffer);
  loose.setVolume(50);
}

void GameplayAudio::audioHandler(bool music, bool _sfx)
{
  sfx = _sfx;
  if (music)
  {
    if (!is_music_playing)
    {
      background_music.play();
      is_music_playing = true;
    }
  }
  else
  {
    is_music_playing = false;
    background_music.stop();
  }
}

void GameplayAudio::playHit()
{
  if (sfx)
  {
    hit.play();
  }
}

void GameplayAudio::playDoor()
{
  if (sfx)
  {
    door.play();
  }
}

void GameplayAudio::playJump()
{
  if (sfx)
  {
    jump.play();
  }
}

void GameplayAudio::playCoin()
{
  if (sfx)
  {
    coin.play();
  }
}

void GameplayAudio::playWin()
{
  if (sfx)
  {
    win.play();
  }
}

void GameplayAudio::playLoose()
{
  if (sfx)
  {
    loose.play();
  }
}

void GameplayAudio::restartAudio()
{
  is_music_playing = false;
  background_music.stop();
}
