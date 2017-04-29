/*
*   Author: Hang-In-There
*   File Name: wordStruct.h
*   File Description: wordStruct contains functions that store data 
*   associated with a word read in from the dictionary and stores the location
*   of each letter within the word
*   Date Created: 3/29/2017
*   Date Last Modified: 4/30/2017
*/

#include <string>

using namespace std;

#ifndef wordStruct_h
#define wordStruct_h

struct wordStruct
{
private:
    string word;
    int    length;
    
public:
    wordStruct(string w, int l)
    {
        word = w;
        length = l;
        
        char charArray[length];
        strcpy(charArray,word.c_str());
        int location;
        for(char c = 'a'; c <= 'z'; c++)
        {
            location = (c - 'a');
            for(int i = 0; i < length; i++)
            {
                if (charArray[i] == c)
                {
                    letters[location]++;
                }
            }
        }
    }
    
    int    letters[26] = {0};
};

#endif /* wordStruct_h */
