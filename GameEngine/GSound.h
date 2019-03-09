
#ifndef GSOUND_H
#define GSOUND_H 1

#include "GameEngine.h"
#include <SDL/SDL_mixer.h>
#define MAX_SOURCES 8

#define GAME_VOLUME GSound::master_volume

class GSound
{
 public:
  GSound(KString filename);
  ~GSound();

  Mix_Chunk* sound;
  int playChannel;

  void Play();
  void Loop();
  void Stop();
  void Pause();
  void Resume();
  void PlayIfNot();
  bool IsPlaying();

  bool paused;

  static int master_volume;

  static bool SoundOn;
};


#endif
