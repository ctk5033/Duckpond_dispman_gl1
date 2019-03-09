

#include "GameEngine.h"


// ---------------------------------
//  FILES
// -----------------------------------------------


std::ofstream GameEngine::writeFile;
std::ifstream GameEngine::readFile[10];
int GameEngine::curReadFile = -1;


void GameEngine::CopyFile(std::string source, std::string dest)
{
    GameEngine::OpenReadFile(source, false);
    GameEngine::OpenWriteFile(dest, false);

    while(GameEngine::HasNextLine())
    {
        KString line;
        line = GameEngine::ReadNextLine();
        GameEngine::WriteFile(line.str.c_str());
        GameEngine::WriteFile("\n");
    }

    GameEngine::CloseReadFile();
    GameEngine::CloseWriteFile();
}



// - write file
void GameEngine::OpenWriteFile(KString filename, bool append)
{
    filename = KString("%s/%s",outDir.c_str(),filename.c_str());

    if (append)
    {
     writeFile.open(filename.c_str(), std::ios::out | std::ios::app);
    }
    else
    {
        writeFile.open(filename.c_str(), std::ios::out | std::ios::trunc);
    }
    if (!writeFile.is_open()){Message(KString("Could not open write file: %s!",filename.c_str()));}

}



void GameEngine::WriteFile(int d)
{
    writeFile << d;
}
void GameEngine::WriteFile(KString str)
{
    writeFile << str.c_str();
}
void GameEngine::CloseWriteFile()
{
    writeFile.close();
}




// - read files




bool GameEngine::OpenReadFile(KString filename, bool resourceFile)
{


/*
    if (resourceFile)
    {
     filename = mainDir + "/" + filename;
    }
    else
    {
        filename = outDir + "/" + filename;
    }*/
    if (curReadFile+1 >= GAMEENGINE_READ_FILE_MAX)
    {
     MessageBox(KString("Could not open read file: %s! Too many files already open!",filename.c_str()));
     return false;
    }
    curReadFile++;
    readFile[curReadFile].open(filename.c_str(), std::ios::in);

    if (!readFile[curReadFile].is_open())
    {
        curReadFile--;
       // MessageBox(KString("Could not open read file: %s!",filename.c_str()));
      //  ForceClose();
        return false;
    }

    return true;

}

void GameEngine::CloseReadFile()
{
    if (curReadFile < 0){return;}
    readFile[curReadFile].close();
    curReadFile--;

}

KString GameEngine::ReadNextString()
{
    if (curReadFile < 0){return "";}
    std::string out;
    readFile[curReadFile] >> out;
    return KString(out.c_str());
}

KString GameEngine::ReadNextLine()
{
    if (curReadFile < 0){return "";}
    std::string ret = "";

    while (ret.size() == 0 && !readFile[curReadFile].eof())
    {
        ret = std::string("");
        if (!std::getline(readFile[curReadFile], ret)){break;}

    if (ret.size() > 0 && ret[ret.size()-1] == '\r')
    {
        ret.erase(ret.begin()+ret.size()-1);
    }


    }
    return KString(ret.c_str());
}

GList<KString> GameEngine::ReadNextLineSplit(char splitChar)
{
 KString line = ReadNextLine();
 GList<KString> retList = line.Split(splitChar);


 return retList;
}




int GameEngine::ReadNextInt()
{
    if (curReadFile < 0){return 0;}
    int out;
    readFile[curReadFile] >> out;
    return out;
}

KString GameEngine::ToLowerCase(KString data)
{
 return KString(ToLowerCase(std::string(data.c_str())));
}

KString GameEngine::ToUpperCase(KString data)
{
 return KString(ToUpperCase(std::string(data.c_str())));
}


std::string GameEngine::ToLowerCase(std::string data)
{
   /* std::transform(data.begin(), data.end(), data.begin(), ::tolower);
    return data;*/

    char text[4096];

    strcpy(text, data.c_str());

    for (unsigned int i = 0; i < data.size(); i++)
    {
        if (text[i] > 64 && text[i] < 91)
        {
            text[i] = text[i] + 32;
        }
    }


    return std::string(text);
}

std::string GameEngine::ToUpperCase(std::string data)
{
   /*std::transform(data.begin(), data.end(), data.begin(), ::toupper);
    return data;*/

    char text[4096];

    strcpy(text, data.c_str());

    for (unsigned int i = 0; i < data.size(); i++)
    {
     if (text[i] > 96 && text[i] < 123)
     {
         text[i] = text[i] - 32;
     }
    }


    return std::string(text);

}


GList<std::string> GameEngine::Split(std::string split, char c)
{
    GList<std::string> list;

    int last = -1;
    for (unsigned int i = 0; i < split.size(); i++)
    {
        if (split[i] == c)
        {
            list.Add(split.substr(last+1,(i-last-1)));
            last = i;
        }
    }

    list.Add(split.substr(last+1,(split.size()-last-1)));

    return list;
}

bool GameEngine::HasNextLine()
{
    if (curReadFile < 0){return false;}
    return !readFile[curReadFile].eof();
}




