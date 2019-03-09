
#ifndef GMUSIC_H
#define GMUSIC_H 1

#include <SDL/SDL_mixer.h>

#include "GameEngine.h"

class GMusic
{
 public:
  GMusic(KString sfilename);
  ~GMusic();


  void Play(bool loop = true);
  void Pause();
  void Resume();
  void Stop();
  bool IsPlaying();




  Mix_Music* data;
  KString filename;

  static bool musicOn;
  static GMusic* curMusic;


};


#endif
