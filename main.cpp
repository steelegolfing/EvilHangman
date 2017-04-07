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

int main(int argc, const char * argv[])
{
    ifstream dictionaryFile;
    int /*charCount[30] = {0}, sum = 0,*/ answer, size, selectionLength = 0, attempts = 0, temp;
    AVL_Tree<string> charCount[30], gameTree, **alphaList = nullptr;
    size_t begin, end;
    string tempString, answerStr;
    bool correctAnswer = false, gameOver = false;
    char tempChar;
    
    
    begin = clock();
    dictionaryFile.open("dictionary.txt");
    while(dictionaryFile >> tempString)
    {
        size = int(tempString.length());
        charCount[size].insert(tempString);
        
        //sum++;
    }
    end = clock();
    
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
        cin >> answerStr;
        answer = atoi(answerStr.c_str());
        
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
        alphaList[i] = new AVL_Tree<string>[selectionLength];
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
            alphaList[i][temp].insert(tempString);
            //cout << temp << endl;
        }
        //cout << "Doing stuff" << endl;
    }
    //cout << "Done" << endl;
    while(!gameOver)
    {
        cout << "Enter a letter: " << endl;
        cin >> answerStr;
        tempChar = answerStr[0];
        //cout << "Letter chosen: " << tempChar << endl;
        size = 0;
        int i = 0;
        int j = tempChar - 'a';
        answer = 0;
        //cout << "J = " << j << endl;
        while(i < selectionLength)
        {
            //cout << "i = " << i << endl;
            int tempSize = alphaList[j][i].getSize();
            //cout << "tempSize = " << tempSize << endl;
            if(tempSize > size)
            {
                answer = i;
                size = tempSize;
                //cout << "New answer: " << answer << endl;
            }
            i++;
        }
        //cout << "Answer is: " << answer << endl;
        alphaList[j][answer].printLevelTree(cout);
        cout << "The most words remaining have " << answer << " " << tempChar;
        cout << "'s is " << alphaList[j][answer].getSize() << endl;
        swap(tempTree, alphaList[j][answer]);
        //cout << "Swapped" << endl;
        for (int l = 0; l < 26; l++)
        {
            for(int k = 0; k < selectionLength; k++)
            {
                alphaList[l][k].makeEmpty();
                //cout << "Letter: " << l << "   selectionLength: " << k << endl;
                //alphaList[l][k].printLevelTree(cout);
            }
        }
        //cout << "Done emptying" << endl;
        /*alphaList = new AVL_Tree<string>*[26];
        for (int l = 0; l < 26; i++)
        {
            alphaList[l] = new AVL_Tree<string>[selectionLength];
        }*/
        
        //cout << "Emptied the data structure" << endl;
        while(tempTree.getSize() > 0)
        {
            //cout << tempTree.getSize() << endl;
            tempString = tempTree.findMin();
            //cout << tempString << endl;
            tempTree.remove(tempString);
            wordStruct tempWord(tempString, selectionLength);
            //cout << tempString << endl;
            for (int l = 0; l < 26; l++)
            {
                temp = tempWord.letters[l];
                //cout << temp << endl;
                //cout << "success!!" << endl;
                //cout << alphaList[i][temp].getSize() << endl;
                alphaList[l][temp].insert(tempString);
                //cout << temp << endl;
            }
            //cout << "Doing stuff" << endl;
        }
        
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
    int /*total = 0,*/ selection;
    //int tempInt = array[begin];
    /*for (int i = begin; i < end+1; i++)
    {
        total += array[i].getSize();
        if (array[i].getSize() != 0)
        {
            cout << "Words with " << i << " letters: " << array[i].getSize() << endl;
            cout << "Total: " << total << endl;
        }
    }*/
    srand(time(NULL));
    //cout << "Random = " << randomInt << endl;
    //cout << "Total = " << total << endl;
    //selection = randomInt % total;
    selection = rand() % (end-begin);
    selection += begin;
    while (selection < begin && (array[selection].getSize() > 0))
    {
        selection = (rand() % (end-begin));
        selection += begin;
    }
    //cout << "Selection = " << selection << endl;
    /*while (tempInt < selection)
    {
        tempInt += array[begin++];
    }*/
    
    return selection;
}
