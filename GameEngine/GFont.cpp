

#include "GFont.h"
#include "GImage.h"

#include "GameEngine.h"

GFont::GFont( KString fontR, float sscale)
{
    letterData = NULL;


    tileCountX = 16;
    tileCountY = 6;
    leading = 0;
    mainH = 0;

    scale = sscale;


    // read file

    GameEngine::OpenReadFile(fontR.str, true);
    // sin.useDelimiter(" ");


    KString imFileName = GameEngine::ReadNextString();

    image = GImage::GetImg(KString("data/font/%s", imFileName.str.c_str()));

    // tileCountX = Integer.getInteger(sin.next());
    tileCountX = GameEngine::ReadNextInt();
    tileCountY = GameEngine::ReadNextInt();

   // GameEngine::Message(tileCountX);



    letterData = new Letter[tileCountX*tileCountY];

    leading = GameEngine::ReadNextInt();
    mainH = GameEngine::ReadNextInt();

    for (int i = 0; i < tileCountX * tileCountY; i++)
    {
     int nw = GameEngine::ReadNextInt();
     int nh = GameEngine::ReadNextInt();
        letterData[i] = Letter(nw, nh);
    }

    GameEngine::CloseReadFile();




    tileW = image->w/tileCountX;
    tileH = image->h/tileCountY;

    GameEngine::Message("SIZE:");
    GameEngine::Message(image->w);
    GameEngine::Message(image->h);

    //tileW = 24;
    //tileH = 24;

/*
    for (int i = 0; i < tileCountX * tileCountY; i++)
    {
       if (i > 20){break;}

        GameEngine::Message("LETTER");
        char msg[256];
     sprintf(msg, "%c", (char)(i+STARTING_CHAR));
     GameEngine::Message(msg);
       GameEngine::Message(letterData[i].w);
       GameEngine::Message(letterData[i].h);

    }*/





}

GFont::~GFont()
{
    delete letterData;
}

int GFont::GetHeight()
{
 return tileH*scale;
}

int GFont::GetWSpace(char c)
{
    if ((int)c-STARTING_CHAR < 0 || (int)c-STARTING_CHAR >= tileCountX*tileCountY) { return 0;}
    if (c == ' ')
    {
        return tileW/4;
    }
    return letterData[(int)c-STARTING_CHAR].w;
}


int GFont::CalculateWidth(KString line)
{
    int textW = 0;
    std::string text = std::string(line.c_str());
    for (int i = 0; i < line.GetSize(); i++)
    {
        // calculate special characters
        if (text.c_str()[i] == '^')
        {
            int endB = -1;
            for (int j = i+1; j < line.GetSize(); j++)
            {
             if (text.c_str()[j] == ']')
             {
              endB = j;
              break;
             }
            }
            if (endB != -1)
            {
             KString valStr = text.substr(i+2, (endB-i)-2);
            // GameEngine::MessageBox(valStr);
             i = endB;
             GList<KString> valList = valStr.Split('^');
             int spacing = GameDraw::DrawSpecialCharacter(valList, 0, 0, true);
             textW = textW + spacing;
            }
        }
        else
        {
         textW = (textW + (GetWSpace(line[i]) + GFont::SPACE_BLANKSPACE)* scale);
        }
    }
    textW = textW ;

    return textW;
}
