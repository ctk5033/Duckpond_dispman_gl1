
#ifndef GSCRIPT_H
#define GSCRIPT_H 1

#include "GameEngine.h"

class GScriptData
{
public:
 GScriptData()
 {
  name = "";
 }

 KString name;
 GList<KString> val;

};

class GScriptBlock // a block of data from the a script
{
 public:

  GScriptBlock(KString sfilename)
  {
   id = "NONE";
   filename = sfilename;

   // strip the end filename and get the dir
   char str[256];
   sprintf(str, "%s", filename.c_str());
   for (int i = filename.GetSize()-1; i >= 0; i--)
   {
    if (str[i] == '/'){str[i] = '\0'; break;}
   }
   dir = KString("%s", str);


  }

  ~GScriptBlock()
  {
   for (int i = 0; i < data.GetSize(); i++)
   {
    delete data[i];
   }
  }

  KString id;
  GList<GScriptData*> data;

  KString filename;
  KString dir;


};


class GScript
{
 public:


 GScript();
 ~GScript();
 GList<GScriptBlock*> blockList;


 static GScript* ReadScript(KString filename, bool store = true);
 static GMap<KString,GScript*> scriptMap;


};




#endif
