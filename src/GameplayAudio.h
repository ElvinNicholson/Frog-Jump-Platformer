
#ifndef PLATFORMERSFML_GAMEPLAYAUDIO_H
#define PLATFORMERSFML_GAMEPLAYAUDIO_H

// Game engine
#include <SFML/Audio.hpp>

class GameplayAudio
{
 public:
  GameplayAudio();
  void audioHandler(bool music, bool _sfx);
  void playHit();
  void playDoor();
  void playJump();
  void playCoin();
  void playWin();
  void playLoose();
  void restartAudio();

 protected:

 private:
  bool sfx = true;
  bool is_music_playing = false;

  sf::Music background_music;

  sf::SoundBuffer hit_buffer;
  sf::Sound hit;

  sf::SoundBuffer door_buffer;
  sf::Sound door;

  sf::SoundBuffer jump_buffer;
  sf::Sound jump;

  sf::SoundBuffer coin_buffer;
  sf::Sound coin;

  sf::SoundBuffer win_buffer;
  sf::Sound win;

  sf::SoundBuffer loose_buffer;
  sf::Sound loose;
};

#endif // PLATFORMERSFML_GAMEPLAYAUDIO_H
