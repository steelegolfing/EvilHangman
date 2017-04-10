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
int* pascal(int);
void combinations(AVL_Tree<string>&, int, int);

int main(int argc, const char * argv[])
{
    ifstream dictionaryFile;
    int answer, size, selectionLength = 0, attempts = 0, firstDimension, secondDimension;
    AVL_Tree<string> charCount[30], gameTree, **alphaList = nullptr;
    string tempString, letterStr, answerString;
    bool correctAnswer = false, gameOver = false, responses[26] = {false}, correct[26] = {false};
    char tempChar;
    
    // Reading in the dictionary
    dictionaryFile.open("dictionary.txt");
    while(dictionaryFile >> tempString)
    {
        size = int(tempString.length());
        charCount[size].insert(tempString);
    }
    
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
    alphaList = new AVL_Tree<string>*[26];
    for (int i = 0; i < 26; i++)
    {
        alphaList[i] = new AVL_Tree<string>[selectionLength+1];
    }
    emptyAndReInsert(tempTree, alphaList, selectionLength);
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
        firstDimension = tempChar - 'a';
        secondDimension = 0;
        answer = 0;
        //cout << "2nd Dimension = " << secondDimension << endl;
        while(secondDimension < selectionLength)
        {
            int tempSize = alphaList[firstDimension][secondDimension].getSize();
            if(tempSize > size)
            {
                answer = secondDimension;
                size = tempSize;
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
    }
    else if (selection >= 'A' && selection <= 'Z')
    {
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
            temp = tempWord.letters[l];
            array[l][temp].insert(tempString);
        }
    }
}

int* pascal(int row)
{
    int *triangleRow = new int[row+1];
    triangleRow[0] = 1;
    if (row == 0)
    {
        return triangleRow;
    }
    triangleRow[row] = 1;
    int* triangleRow2 = pascal(row-1);
    
    for (int i = 1; i < row; i++)
    {
        triangleRow[i] = (triangleRow2[i] + triangleRow2[i-1]);
    }
    
    return triangleRow;
}

void combinations(AVL_Tree<string> gameTree, int stringLength, int numberOfLetters)
{
    int* tempArray = pascal(stringLength);
    int array[tempArray[numberOfLetters]];
    string tempString;
    
    for (int i = 0; i < gameTree.getSize(); i++)
    {
        tempString = gameTree.findMin();
        gameTree.remove(tempString);
        
    }
}
