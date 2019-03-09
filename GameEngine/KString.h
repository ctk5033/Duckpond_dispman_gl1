
#ifndef KSTRING_H
#define KSTRING_H 1

#include <string>
#include <cstring>
#include <iostream>
#include <cstdio>
#include <cstdarg>
#include <cstdlib>
#include "GList.h"


class KString
{
  public:

    KString()
    {
      str = "";
    }

    KString(std::string sstr)
    {
      str = std::string(sstr);
    }

    KString(char sstr[256])
    {
      str = std::string(sstr);
    }

    KString(const  KString& sstr)
    {
     str = std::string(sstr.str.c_str());
    }

    KString(const char *fmt, ...)
    {

        char text[4096];
     va_list	ap;

     if (fmt == NULL)
      {return;}

     va_start(ap, fmt);
         vsprintf(text, fmt, ap);
     va_end(ap);


     str = std::string(text);


    }


    const char* c_str()
    {
     return str.c_str();
    }


    std::string str;

    void Set(std::string set)
    {
     str = set;
    }

    void Add(KString otherStr)
    {
        char addStr[256];
        sprintf(addStr, "%s%s", str.c_str(), otherStr.str.c_str());
        str = std::string(addStr);
    }

    void Add(char c)
    {
       char addStr[256];
       sprintf(addStr, "%s%c", str.c_str(), c);
       str = addStr;
    }

    void Add(int i)
    {
       char addStr[256];
       sprintf(addStr, "%s%d", str.c_str(), i);
       str = addStr;
    }

    void Add(float f)
    {
       char addStr[256];
       sprintf(addStr, "%s%f", str.c_str(), f);
       str = addStr;
    }

    KString SubString(int start, int end)
    {
      KString sub = str.substr(start, end-start);
      return sub;
    }

    bool Contains(char c)
    {
     return str.find(c) != std::string::npos;
    }

    int GetInt()
    {
     return std::atoi(str.c_str());
    }




    int GetSize()
    {
     return str.size();
    }

    void Remove(int i)
    {
     str.erase(str.begin()+i);
    }

    bool Equals(KString str)
    {
     if (strcmp(c_str(), str.c_str()) == 0){return true;}
     else {return false;}
    }

    GList<KString> Split(char splitChar)
    {
     GList<KString> retList;

     std::string str = std::string(c_str());

     int lastC = 0;
     unsigned int c = str.find(splitChar);
     while (c != std::string::npos)
     {
      retList.Add(KString(str.substr(lastC, c-lastC).c_str()));
      lastC = c+1;
      c = str.find(splitChar,lastC);
     }
     retList.Add(KString(str.substr(lastC, str.size()-lastC).c_str()));


     return retList;

    }



    int Find(char c, int start = 0)
    {
     int pos = str.find_first_of(c, start);
     // returns -1 if not found
     return pos;
    }

    // replaces every instance of src in the string with rep
    bool Replace(KString src, KString rep) // returns true when a replacement was made
    {
     bool ret = false;
     size_t loc = str.find(src.c_str());
     while (loc != std::string::npos)
     {
      ret = true;
      str.replace(loc, src.GetSize(), rep.c_str());

      loc = str.find(src.c_str(), loc+1);
     }

     return ret;
    }


    void SetChar(int i, char c)
    {

     str.replace(i,1,"A");
    }












     char operator[]( int i )
     {
       return str.c_str()[i];
     }

     bool operator== (KString other)
     {
      return  (std::strcmp(str.c_str(), other.str.c_str()) == 0);
     }

     KString operator+ (KString other)
     {
      Add(other);
      return  KString(str);
     }

     KString operator+ (int i)
     {
      Add(i);
      return  KString(str);
     }





     static bool IsLetter(char c)
     {
      if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z')
      {
       return true;
      }
      return false;
     }







};









#endif // KSTRING_H


