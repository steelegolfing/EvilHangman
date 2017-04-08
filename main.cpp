//
//  main.cpp
//  3334 - Group Project
//
//  Created by Travis Cox on 3/29/17.
//  Copyright © 2017 Travis Cox. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "stdlib.h"
#include <ctime>
#include "wordStruct.h"
#include "AVL_Tree.h"
#include "SDL_Plotter.h"

using namespace std;

int randomizer(int, int, AVL_Tree<string> []);
bool checkResponses(char&, bool[]);
void emptyAndReInsert(AVL_Tree<string>, AVL_Tree<string>**, int);

int main(int argc, const char * argv[])
{
    ifstream dictionaryFile;
    int answer, size, selectionLength = 0, attempts = 0, temp, firstDimension, secondDimension;
    AVL_Tree<string> charCount[30], gameTree, **alphaList = nullptr;
    //size_t begin, end;
    string tempString, letterStr, answerString;
    bool correctAnswer = false, gameOver = false, responses[26] = {false}, correct[26] = {false};
    char tempChar;
    
    
    //begin = clock();
    dictionaryFile.open("dictionary.txt");
    while(dictionaryFile >> tempString)
    {
        size = int(tempString.length());
        charCount[size].insert(tempString);
        
        //sum++;
    }
    //end = clock();
    
    /*for (int i = 0; i < 30; i++)
    {
        if (charCount[i].getSize() != 0)
        {
            cout << "Words with " << i << " letters: " << charCount[i].getSize() << endl;
        }
    }*/
    
    //cout << "Sum: " << sum << endl;
    //cout << "Time: " << (end - begin) << endl;
    
    while (!correctAnswer)
    {
        cout << "Would you like beginner(1), intermediate(2), or advanced(3)?" << endl;
        cin >> letterStr;
        answer = atoi(letterStr.c_str());
        
        switch (answer)
        {
            case 1:
                cout << "You have chosen beginner! (words 2-5 letters in length)" << endl;
                correctAnswer = true;
                selectionLength = randomizer(2, 5, charCount);
                break;
            case 2:
                cout << "You have chosen intermediate! (words 6-10 letters in length)" << endl;
                correctAnswer = true;
                selectionLength = randomizer(6, 10, charCount);
                break;
            case 3:
                cout << "You have chosen advanced! (words 11+ letters in length)" << endl;
                correctAnswer = true;
                selectionLength = randomizer(11, 29, charCount);
                break;
            default:
                cout << "Incorrect response!" << endl;
                
                break;
        }
    }
    
    cout << "The word will be length: " << selectionLength << endl;
    AVL_Tree<string> tempTree(charCount[selectionLength]);
    //cout << "Tree copied" << endl;
    //gameTree.printLevelTree(cout);
    
    alphaList = new AVL_Tree<string>*[26];
    for (int i = 0; i < 26; i++)
    {
        alphaList[i] = new AVL_Tree<string>[selectionLength+1];
    }
    //cout << "Data structure made" << endl;
    while(tempTree.getSize() > 0)
    {
        //cout << tempTree.getSize() << endl;
        tempString = tempTree.findMin();
        //cout << tempString << endl;
        tempTree.remove(tempString);
        wordStruct tempWord(tempString, selectionLength);
        //cout << tempString << endl;
        for (int i = 0; i < 26; i++)
        {
            temp = tempWord.letters[i];
            //cout << temp << endl;
            alphaList[i][temp].insert(tempString);
            //cout << "Inserted" << endl;
        }
        //cout << "Doing stuff" << endl;
    }
    //cout << "Done" << endl;
    while(!gameOver)
    {
        do
        {
            cout << "Enter a letter: " << endl;
            cin >> letterStr;
            tempChar = letterStr[0];
        }while(!checkResponses(tempChar, responses));
        //cout << "Letter chosen: " << tempChar << endl;
        
        size = 0;
        secondDimension = 0;
        firstDimension = tempChar - 'a';
        answer = 0;
        //cout << "2nd Dimension = " << secondDimension << endl;
        while(secondDimension < selectionLength)
        {
            //cout << "i = " << i << endl;
            int tempSize = alphaList[firstDimension][secondDimension].getSize();
            //cout << "tempSize = " << tempSize << endl;
            if(tempSize > size)
            {
                answer = secondDimension;
                size = tempSize;
                //cout << "New answer: " << answer << endl;
            }
            secondDimension++;
        }
        if (answer > 0)
        {
            correct[(tempChar - 'a')] = true;
        }
        //cout << "Answer is: " << answer << endl;
        //alphaList[firstDimension][answer].printLevelTree(cout);
        cout << "The most words remaining have " << answer << " " << tempChar;
        cout << "'s is " << alphaList[firstDimension][answer].getSize() << endl;
        cout << "Incorrect guesses: ";
        for (int i = 0; i < 26; i++)
        {
            if (responses[i] && !correct[i])
            {
                cout << char(i + 'a') << " ";
            }
        }
        cout << endl;
        swap(tempTree, alphaList[firstDimension][answer]);
        if (tempTree.getSize() == 1)
        {
            answerString = tempTree.findMin();
        }
        //cout << "Swapped" << endl;
        for (int l = 0; l < 26; l++)
        {
            for(int k = 0; k < selectionLength; k++)
            {
                alphaList[l][k].makeEmpty();
            }
        }
        
        emptyAndReInsert(tempTree, alphaList, selectionLength);
        
        attempts++;
        cout << "You have " << (12 - attempts) << " attempts remaining!!!" << endl;
        if (attempts >= 12)
        {
            gameOver = true;
        }
    }
    
    return 0;
}

int randomizer(int begin, int end, AVL_Tree<string> array[])
{
    int selection;

    srand(time(NULL));
    selection = rand() % (end-begin);
    selection += begin;
    while (selection < begin && (array[selection].getSize() > 0))
    {
        selection = (rand() % (end-begin));
        selection += begin;
    }
    
    return selection;
}

bool checkResponses(char& selection, bool responses[])
{
    char temp = 'a';
    // Checks if the character selected is valid
    if (selection >= 'a' && selection <= 'z')
    {
        //temp = 'a';
    }
    else if (selection >= 'A' && selection <= 'Z')
    {
        //temp = 'a';
        selection = ((selection - 'A') + 'a');
    }
    else
    {
        return false;
    }
    
    // Tests the chosen character if it has already been used
    if (!responses[selection - temp])
    {
        responses[selection - temp] = true;
        return responses[selection - temp];
    }
    else
    {
        return !responses[selection - temp];
    }
}

void emptyAndReInsert(AVL_Tree<string> oldTree, AVL_Tree<string> **array, int length)
{
    string tempString;
    int temp;
    while(oldTree.getSize() > 0)
    {
        tempString = oldTree.findMin();
        oldTree.remove(tempString);
        wordStruct tempWord(tempString, length);
        for (int l = 0; l < 26; l++)
        {
            temp = tempWord.letters[l];\
            array[l][temp].insert(tempString);
        }
    }
}
