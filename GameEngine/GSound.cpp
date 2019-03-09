#include "GSound.h"

bool GSound::SoundOn = true;

int GSound::master_volume = 50;



GSound::GSound(KString filename)
{

 sound = Mix_LoadWAV(filename.str.c_str());
 if (sound == NULL)
 {
  char e[256];
  sprintf(e, "Could not load sound: \"%s\"!", filename.str.c_str());
  // GameEngine::MessageBox(e);
  std::cout << e;
 }
 sound->volume = GAME_VOLUME;
 playChannel = -1;

 paused = false;
}

GSound::~GSound()
{
 Mix_FreeChunk(sound);
}


void GSound::Play()
{
 if (!GSound::SoundOn){return;}

 sound->volume = GAME_VOLUME;
 playChannel = Mix_PlayChannel(-1, sound, 0);
}

void GSound::Loop()
{
 if (!GSound::SoundOn || IsPlaying()){return;}

 sound->volume = GAME_VOLUME;
 playChannel = Mix_PlayChannel(-1, sound, -1);

}

void GSound::PlayIfNot()
{
 if (!GSound::SoundOn || IsPlaying()){return;}

 sound->volume = GAME_VOLUME;
 playChannel = Mix_PlayChannel(-1, sound, 0);
}

void GSound::Stop()
{
 if (IsPlaying())
 {
  Mix_HaltChannel(playChannel);
 }
}

void GSound::Pause()
{

 Mix_Pause(playChannel);
 paused = true;

}

void GSound::Resume()
{
 if (paused)
 {
  paused = false;
  Mix_Resume(playChannel);
 }
}

bool GSound::IsPlaying()
{
 if (paused || playChannel == -1 || Mix_Playing(playChannel) == 0 || (Mix_GetChunk(playChannel) != sound)){return false;}
 return true;
}
