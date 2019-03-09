

#ifndef GMAP_H
#define GMAP_H 1

#include "GList.h"


template <class T, class R>
class GMap
{
 public:
	 GList<T> keyList;
	 GList<R> itemList;

	 void Put(T key, R item)
	 {
		 keyList.Add(key);
		 itemList.Add(item);
	 }

	 bool Get(T key, R* item)
	 {
		for (int i = 0; i < keyList.GetSize(); i++)
		{
			if (keyList[i] == key)
            {
                *item = itemList[i];
                return true;
            }
		}

         return false; // does not contain key
	 }


	  bool Contains(T key)
	 {
		for (int i = 0; i < keyList.GetSize(); i++)
		{
			if (keyList[i] == key)
            {

                return true;
            }
		}

         return false; // does not contain key
	 }

  R Get(T key)
	 {
		for (int i = 0; i < keyList.GetSize(); i++)
		{
			if (keyList[i] == key)
            {
                return itemList[i];

            }
		}

         return NULL; // does not contain key
	 }



};



#endif
