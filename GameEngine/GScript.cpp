

#include "GScript.h"


GMap<KString,GScript* > GScript::scriptMap;

GScript::GScript()
{

}

GScript::~GScript()
{
 for (int i = 0; i < blockList.GetSize(); i++)
 {
  delete blockList[i];
 }
 blockList.RemoveAll();
}


GScript* GScript::ReadScript(KString filename, bool store)
{


 if (scriptMap.Contains(filename))
 {
  return scriptMap.Get(filename);
 }


 GScript* rScript = new GScript();

 if (!GameEngine::OpenReadFile(filename))
 {
  GameEngine::MessageBox(KString("Could not read script file %s!", filename.c_str()));
  return rScript;
 }

 KString read = "";
 bool inBlock = false;
 GScriptBlock* curBlock = NULL;

 while (GameEngine::HasNextLine())
 {
  read = GameEngine::ReadNextLine();
  if (!inBlock)
  {
   if (read[0] == '*')
   {
    inBlock = true;
    curBlock = new GScriptBlock(filename);
    rScript->blockList.Add(curBlock);
   }
  }
  else
  {
   if (read[0] == '*'){inBlock = false;}
   else // read data for block
   {
    GList<KString> split = read.Split('=');
    if (split[0] == "id")
    {
     curBlock->id = KString(split[1]);
    }
    else
    {
     GScriptData* scriptData = new GScriptData();
     curBlock->data.Add(scriptData);
     scriptData->name = KString(split[0]);
     for (int i = 1; i < split.GetSize(); i++)
     {
      scriptData->val.Add(KString(split[i]));
     }
    }

   }
  }

 }

 GameEngine::CloseReadFile();


 if (store)
 {scriptMap.Put(filename, rScript);}


 return rScript;
}
