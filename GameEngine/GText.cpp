#include "GText.h"

#include "GameEngine.h"

GText::GText(KString stext)
{
 ConstructC(stext,1,false,false);
}

GText::GText(KString stext, bool scentered)
{
  ConstructC(stext,1,false,scentered);
}

GText::GText(KString stext, float sw, bool swrap, bool scentered)
{
    ConstructC(stext,sw,swrap,scentered);


}

void GText::ConstructC(KString stext, float sw, bool swrap, bool scentered)
{
    textW = 1;

    w = sw;
    wrap = swrap;
    centered = scentered;

    textWrap.RemoveAll();

    SetText(stext);


}

GText::~GText()
{

    for (int i = 0; i < textWrap.GetSize(); i++)
    {
        delete textWrap[i];
    }
}





KString GText::GetText()
{
    return text;
}

int GText::GetRows()
{
 if (textWrap.GetSize() == 0){return 1;}
 return textWrap.GetSize()+1;
}

void GText::SetText(KString stext)
{
    text = GameEngine::ToUpperCase(stext);
    CalculateWidth();
    if (wrap)
    {
        SetupWrap();
    }
}

bool GText::IsCentered()
{
    return centered;
}

bool GText::IsWrap()
{
    return wrap;
}

void GText::AddLine(KString line)
{
 // if there is no wrap yet, add the first line to it (don't add if there is nothing in it)
 if (!wrap && textWrap.GetSize() == 0 && !(text == ""))
 {textWrap.Add(new GText(text, w, false, centered)); }

 wrap = true;

 textWrap.Add(new GText(line.c_str(), w, false, centered));

/* GList<KString> split = line.Split('\n');

 for (int i = 0; i < split.GetSize(); i++)
 {
  textWrap.Add(new GText(split[i].c_str(), w, false, centered));
 }*/
}


void GText::CalculateWidth()
{
    /*textW = 0;
    for (int i = 0; i < text.GetSize(); i++)
    {
        textW = textW + (GameEngine::curFont->GetWSpace(text[i]) + GFont::SPACE_BLANKSPACE);
    }
    textW = textW * GameEngine::curFont->scale; // change to have its own font (use g engine's if non provided)*/

    textW = GameEngine::curFont->CalculateWidth(text);
}

int GText::GetTextWidth()
{
    return textW;
}

















void GText::SetupWrap()
{
    for (int i = 0; i < textWrap.GetSize(); i++)
    {
        delete textWrap[i];
    }

    textWrap.RemoveAll();

    std::string text = this->text.c_str();

    std::string buffer = "";
    float position = 0;
    int startC = 0;
    unsigned int endC = 0;
    int layer = 0;

    while (endC < text.length())
    {
        position = 0;
        while (position < w && endC < text.length())
        {
            position = position + GameEngine::curFont->GetWSpace(text[endC]) * GameEngine::curFont->scale
            + GFont::SPACE_BLANKSPACE;
            if (position >= w || text[endC] == '\n')
            {
                break;
            }
            endC++;
        }

        while (endC < text.length() && text[endC] != ' ' && text[endC] != '\n')
        {
            endC--;
            if (endC < 0)
            {
                return;
            }
        }

        if (endC < text.length() - 1)
        {
            endC++;
        }

        // can use for centering text later
        std::string dString = text.substr(startC, (endC-startC));
        position = 0;
        for (unsigned int i = 0; i < dString.length(); i++)
        {
            position = position + GameEngine::curFont->GetWSpace(text[i]) * GameEngine::curFont->scale
            + GFont::SPACE_BLANKSPACE;
        }


        AddLine(text.substr(startC, (endC-startC)));
       // textWrap.Add(new GText(text.substr(startC, (endC-startC)), w, false, centered));



        startC = endC;
        layer++;
    }


}
