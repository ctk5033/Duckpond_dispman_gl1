

#include "TextPrint.h"
#include "../MainSub.h"
#include "GSound.h"



TextPrint::TextPrint(KString stext, float sx, float sy, float sw, int sdelay, MainSub* sSub)
	{
		text = stext;
		buffer = "";
		mainSub = sSub;
		x = sx;
		y = sy;
		w = sw;
		maxDelay = sdelay;
		delay = 0;
		pos = 0;
		gText = new GText(buffer.str, w, true, true);

		typeSound= NULL;



	}

	TextPrint::~TextPrint()
	{
		delete gText;
	}

	int TextPrint::GetRows()
	{
	 return gText->GetRows();
	}


	bool TextPrint::IsFinished()
	{
	 return pos >= text.str.size();
	}

	void TextPrint::ForceFinish()
	{
	 buffer = text.str;
	 pos = text.str.size();
	 gText->SetText(buffer.str);
	}

  void TextPrint::Update()
	{
		if (pos < text.str.size())
		{
			if (delay < maxDelay){delay++;}
			else
			{
			 if (text[pos] == '^') // special chars
    {
            // skip over special character so it all appears at once
            int endB = -1;
            for (int j = pos+1; j < text.GetSize(); j++)
            {
             if (text.c_str()[j] == ']')
             {
              endB = j;
              break;
             }
            }
            if (endB != -1)
            {
             KString valStr = text.str.substr(pos, (endB-pos)+1);
             //GameEngine::MessageBox(valStr);
             pos = endB+1;
             buffer.Add(valStr);
            }
            else
            {
             pos++;
            }
    }
    else // normal chars
    {
     char addC[2];
     addC[0] = text[pos];
     addC[1] = '\0';
     if (text[pos+1] == 'v')
     {
      int i = 0;
      i++;
     }
     buffer.Add(addC);
     if (pos%5 == 0){}
     pos++;

     if (typeSound != NULL){typeSound->Play();}

    }
     delay = 0;
     gText->SetText(buffer.str);

			}
		}
	}

	void TextPrint::Draw()
	{
  float dX = x;
  float dY = y - gText->textWrap.GetSize()*8;
  if (mainSub != NULL){dX = dX + mainSub->x; dY = dY + mainSub->y;}

		GameDraw::DrawText(gText, dX, dY);
	}
