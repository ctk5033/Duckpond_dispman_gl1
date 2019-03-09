
#ifndef TEXTPRINT_H
#define TEXTPRINT_H 1

#include "GameEngine.h"
#include "GameDraw.h"
#include "GText.h"

class GSound;

class MainSub;

class TextPrint
{

public:
	TextPrint(KString stext, float sx, float sy, float sw, int sdelay, MainSub* sSub = NULL);
	~TextPrint();




 void Update();
	void Draw();

	bool IsFinished();
	void ForceFinish();

	GSound* typeSound;

	KString text;
	KString buffer;
	GText* gText;
	float x;
	float y;
	float w;
	unsigned int pos;
	int delay;
	int maxDelay;

	MainSub* mainSub;

	int GetRows();

};



#endif
