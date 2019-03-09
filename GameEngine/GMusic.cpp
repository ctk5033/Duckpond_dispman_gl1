

#include "GMusic.h"

#include "GSound.h"

// ONLY ONE MUSIC TRACK CAN BE PLAYING AT ONCE!

GMusic* GMusic::curMusic = NULL;
bool GMusic::musicOn = TRUE;

GMusic::GMusic(KString sfilename)
{
// strcpy(filename, sfilename);
 filename = sfilename;
 data = Mix_LoadMUS(filename.str.c_str());
 if (data == NULL)
 {
  char errBox[256];
  sprintf(errBox, "Could not load music file: \"%s\"!", filename.str.c_str());
  GameEngine::MessageBox(errBox);
 }
}

GMusic::~GMusic()
{
 Mix_FreeMusic(data);
}


void GMusic::Play(bool loop)
{
 int times = 0;
 if (!loop){times = 1;}
 Mix_PlayMusic(data,times);
 Mix_VolumeMusic(GAME_VOLUME);
 curMusic = this;
}

void GMusic::Pause()
{
 Mix_PauseMusic();
}

void GMusic::Resume()
{
 Mix_ResumeMusic();
}

void GMusic::Stop()
{
 Mix_HaltMusic();
 if (curMusic == this){curMusic = NULL;}
}

bool GMusic::IsPlaying()
{
 if (curMusic == this){return true;}
 return false;
}
