//
//  wordStruct.h
//  3334 - Group Project
//
//  Created by Travis Cox on 3/29/17.
//  Copyright © 2017 Travis Cox. All rights reserved.
//

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
