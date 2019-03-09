

#include "DuckData.h"




DuckData::DuckData()
{
 player = new Player(0);
 player->SetKeys(KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, 'z', 'x', KEY_ENTER);

 score = 0;




}

DuckData::~DuckData()
{
 delete player;
}



GColor DuckData::colorDuck;
GImage* DuckData::imDuck = NULL;

GSound* DuckData::wavStart = NULL;
GSound* DuckData::wavDie = NULL;
GSound* DuckData::wavPoints = NULL;
GSound* DuckData::wavLosePoints = NULL;
GSound* DuckData::wavStep = NULL;
GSound* DuckData::wavHatch = NULL;
GSound* DuckData::wavBite = NULL;
GSound* DuckData::wavGrab = NULL;
GSound* DuckData::wavDuckGrab = NULL;
GSound* DuckData::wavEat = NULL;
GSound* DuckData::wavLayEgg = NULL;
GSound* DuckData::wavAir = NULL;


void DuckData::InitData()
{
 imDuck = GImage::GetImg("data/duck.png");

 wavStart = new GSound("data/sound/start.wav");

 wavDie = new GSound("data/sound/die.wav");
 wavPoints = new GSound("data/sound/points.wav");
 wavLosePoints = new GSound("data/sound/losepoints.wav");
 wavStep = new GSound("data/sound/step.wav");
 wavHatch = new GSound("data/sound/hatch.wav");
 wavBite = new GSound("data/sound/bite.wav");
 wavGrab = new GSound("data/sound/grab.wav");
 wavDuckGrab = new GSound("data/sound/duckgrab.wav");
 wavEat = new GSound("data/sound/eat.wav");
 wavLayEgg = new GSound("data/sound/layegg.wav");
 wavAir = new GSound("data/sound/air.wav");

 colorDuck = GColor(24,68,196);
}
