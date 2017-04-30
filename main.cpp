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
#include "Single_Linked_List.h"
#include "SDL_Plotter.h"

using namespace std;

int difficultyLevel(singleLinkedList<string> [], SDL_Event&, bool&);
int randomizer(int, int, singleLinkedList<string> []);
bool checkResponses(char&, bool[]);
void emptyAndReInsert(singleLinkedList<string>, singleLinkedList<string>**, int);
//int* pascal(int);
void combinations(singleLinkedList<string>&, int, int, int, char, char[]);
void attemptCheck(bool&, int, char[], int, int&, bool&);
bool endGame(bool, bool);

int main(int argc, const char * argv[])
{
    ifstream dictionaryFile;
    int answer, size, selectionLength = 0, attempts, firstDimension, secondDimension;
    singleLinkedList<string> charCount[30], gameTree, **alphaList = nullptr;
    string tempString, letterStr, answerString, incorrectGuesses = " ", evilWordString;
    bool correctAnswer, gameOver = false, responses[26] = {false}, correct[26] = {false}, victory;
    char tempChar, key;
    const Uint8 *currentKeyStates;
    LTexture evilWord, incorrectLetters;
    
    // Reading in the dictionary
    dictionaryFile.open("dictionary.txt");
    while(dictionaryFile >> tempString)
    {
        size = int(tempString.length());
        charCount[size].insert(tempString);
    }
    
    string mehString = " ";
    //Start up SDL and create window
    if( !init() )
    {
        printf( "Failed to initialize!\n" );
    }
    else
    {
        //Load media
        if( !gTextTexture.loadWord("Wub", 0, 0) )
        {
            printf( "Failed to load media1!\n" );
        }
        else if (!incorrectLetters.loadWord(mehString, 0, 0))
        {
            printf("Failed to load media2!\n");
        }
        else
        {
            
            //Main loop flag
            bool quit = false;
            
            //Event handler
            SDL_Event e;
            
            while (!gameOver)
            {
                //gameOver = false;
                victory = false;
                correctAnswer = false;
                attempts = 0;
                selectionLength = difficultyLevel(charCount, e, quit);
                
                //cout << "The word will be length: " << selectionLength << endl;
                singleLinkedList<string> tempTree(charCount[selectionLength]);
                alphaList = new singleLinkedList<string>*[26];
                for (int i = 0; i < 26; i++)
                {
                    alphaList[i] = new singleLinkedList<string>[selectionLength+1];
                }
                emptyAndReInsert(tempTree, alphaList, selectionLength);
                char guessesArray[(selectionLength+1)];
                for (int i = 0; i < selectionLength; i++)
                {
                    guessesArray[i] = '_';
                }
                guessesArray[selectionLength] = '\0';
                //cout << guessesArray << endl;
                for (int i = 0; i < 26; i++)
                {
                    responses[i] = false;
                    correct[i] = false;
                }
                
                evilWordString.clear();
                incorrectGuesses = " ";
                for (int i = 0; i < selectionLength; i++)
                {
                    evilWordString = evilWordString + guessesArray[i];
                    //evilWordString = evilWordString + " ";
                }
                
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(gRenderer);
                evilWord.loadWord(evilWordString, 0, ((SCREEN_HEIGHT/4)*3));
                //evilWord.render((SCREEN_WIDTH-evilWord.getWidth()) / 2, ((SCREEN_HEIGHT-evilWord.getHeight()) / 4) * 3);
                incorrectLetters.loadWord(incorrectGuesses, 50, 50);
                renderHangman(gRenderer, attempts);
                //incorrectLetters.render(50, 50);
                SDL_RenderPresent(gRenderer);
                
                while(!gameOver && !victory)
                {
                    /*do
                    {
                        cout << "Enter a letter: " << endl;
                        cin >> letterStr;
                        tempChar = letterStr[0];
                    }while(!checkResponses(tempChar, responses));*/
                    
                    
                    
                    //cout << "While loop" << endl;
                    do
                    {
                        key = '\0';
                        while (key == '\0')
                        {
                            while( SDL_PollEvent( &e ) != 0 )
                            {
                                //User requests quit
                                if( e.type == SDL_QUIT )
                                {
                                    quit = true;
                                }
                                if (e.type == SDL_KEYDOWN)
                                {
                                    key = '\0';
                                    
                                    currentKeyStates = SDL_GetKeyboardState( NULL );
                                    if(currentKeyStates[SDL_SCANCODE_A]) key = 'a';
                                    if(currentKeyStates[SDL_SCANCODE_B]) key = 'b';
                                    if(currentKeyStates[SDL_SCANCODE_C]) key = 'c';
                                    if(currentKeyStates[SDL_SCANCODE_D]) key = 'd';
                                    if(currentKeyStates[SDL_SCANCODE_E]) key = 'e';
                                    if(currentKeyStates[SDL_SCANCODE_F]) key = 'f';
                                    if(currentKeyStates[SDL_SCANCODE_G]) key = 'g';
                                    if(currentKeyStates[SDL_SCANCODE_H]) key = 'h';
                                    if(currentKeyStates[SDL_SCANCODE_I]) key = 'i';
                                    if(currentKeyStates[SDL_SCANCODE_J]) key = 'j';
                                    if(currentKeyStates[SDL_SCANCODE_K]) key = 'k';
                                    if(currentKeyStates[SDL_SCANCODE_L]) key = 'l';
                                    if(currentKeyStates[SDL_SCANCODE_M]) key = 'm';
                                    if(currentKeyStates[SDL_SCANCODE_N]) key = 'n';
                                    if(currentKeyStates[SDL_SCANCODE_O]) key = 'o';
                                    if(currentKeyStates[SDL_SCANCODE_P]) key = 'p';
                                    if(currentKeyStates[SDL_SCANCODE_Q]) key = 'q';
                                    if(currentKeyStates[SDL_SCANCODE_R]) key = 'r';
                                    if(currentKeyStates[SDL_SCANCODE_S]) key = 's';
                                    if(currentKeyStates[SDL_SCANCODE_T]) key = 't';
                                    if(currentKeyStates[SDL_SCANCODE_U]) key = 'u';
                                    if(currentKeyStates[SDL_SCANCODE_V]) key = 'v';
                                    if(currentKeyStates[SDL_SCANCODE_W]) key = 'w';
                                    if(currentKeyStates[SDL_SCANCODE_X]) key = 'x';
                                    if(currentKeyStates[SDL_SCANCODE_Y]) key = 'y';
                                    if(currentKeyStates[SDL_SCANCODE_Z]) key = 'z';
                                }
                            }
                        }
                    }while (!checkResponses(key, responses));

                    size = 0;
                    firstDimension = key - 'a';
                    secondDimension = 0;
                    answer = 0;
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
                        correct[(key - 'a')] = true;
                    }
                    else
                    {
                        //responses[(key) - 'a'] = true;
                        incorrectGuesses = incorrectGuesses + key;
                        //incorrectGuesses = incorrectGuesses + " ";
                    }
                    //cout << "Incorrect guesses: " << incorrectGuesses << endl;
                    /*cout << "Incorrect guesses: ";
                    for (int i = 0; i < 26; i++)
                    {
                        if (responses[i] && !correct[i])
                        {
                            //cout << char(i + 'a') << " ";
                        }
                    }
                    cout << endl;*/
                    swap(tempTree, alphaList[firstDimension][answer]);
                    if (tempTree.getSize() == 1)
                    {
                        answerString = tempTree.findHead();
                    }
                    for (int l = 0; l < 26; l++)
                    {
                        for(int k = 0; k < selectionLength; k++)
                        {
                            alphaList[l][k].makeEmpty();
                        }
                    }
                    if (answer > 0)
                    {
                        combinations(tempTree, 0, selectionLength, answer, key, guessesArray);
                    }
                    emptyAndReInsert(tempTree, alphaList, selectionLength);
                    
                    attemptCheck(victory, selectionLength, guessesArray, answer, attempts, gameOver);
                    
                    evilWordString = "";
                    for (int i = 0; i < selectionLength; i++)
                    {
                        evilWordString = evilWordString + guessesArray[i];
                        //evilWordString = evilWordString + " ";
                    }
                    
                    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                    SDL_RenderClear(gRenderer);
                    evilWord.loadWord(evilWordString, 0, ((SCREEN_HEIGHT/4)*3));
                    //evilWord.render((SCREEN_WIDTH-evilWord.getWidth()) / 2, ((SCREEN_HEIGHT-evilWord.getHeight()) / 4) * 3);
                    incorrectLetters.loadWord(incorrectGuesses, 50, 50);
                    
                    renderHangman(gRenderer, attempts);
                    
                    //incorrectLetters.render(50, 50);
                    SDL_RenderPresent(gRenderer);
                }
                
                incorrectLetters.free();
                evilWord.free();
                SDL_RenderClear(gRenderer);
                gameOver = endGame(victory, gameOver);
            }

        }
    }
    
    
    
    
    //Free resources and close SDL
    close();
    
    return 0;
}

int difficultyLevel(singleLinkedList<string> charCount[], SDL_Event &e, bool &quit)
{
    bool correctAnswer = false;
    string letterStr;
    int selectionLength = 0;
    LTexture difficulty;
    const Uint8 *currentKeyStates;
    char key;
    //cout << "difficulty.loadWord" << endl;
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(gRenderer);
    //difficulty.loadWord("Would you like beg(1), int(2), or adv(3)?", 0, (SCREEN_HEIGHT/2));
    while (!correctAnswer)
    {
        
        SDL_RenderPresent(gRenderer);
        while( SDL_PollEvent( &e ) != 0 )
        {
            //User requests quit
            if( e.type == SDL_QUIT )
            {
                quit = true;
            }
            if (e.type == SDL_KEYDOWN)
            {
                key = '\0';
                
                currentKeyStates = SDL_GetKeyboardState( NULL );
                if(currentKeyStates[SDL_SCANCODE_1]) key = '1';
                if(currentKeyStates[SDL_SCANCODE_2]) key = '2';
                if(currentKeyStates[SDL_SCANCODE_3]) key = '3';
                
                switch (key)
                {
                    case '1':
                        //cout << "You have chosen beginner! (words 2-5 letters in length)" << endl;
                        correctAnswer = true;
                        selectionLength = randomizer(2, 5, charCount);
                        break;
                    case '2':
                        //cout << "You have chosen intermediate! (words 6-10 letters in length)" << endl;
                        correctAnswer = true;
                        selectionLength = randomizer(6, 10, charCount);
                        break;
                    case '3':
                        //cout << "You have chosen advanced! (words 11+ letters in length)" << endl;
                        correctAnswer = true;
                        selectionLength = randomizer(11, 29, charCount);
                        break;
                    default:
                        //cout << "Incorrect response!" << endl;
                        break;
                }

            }
        }
        
        //difficulty.loadWord("Would you like beg(1), int(2), or adv(3)?", 0, (SCREEN_HEIGHT/2));
        //SDL_RenderPresent(gRenderer);
        
        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( gRenderer );
        difficulty.loadWord("would you like beg(1), int(2), or adv(3)?", 0, (SCREEN_HEIGHT/2));
        //SDL_RenderPresent(gRenderer);
    }

    difficulty.free();
    
    return selectionLength;
}

int randomizer(int begin, int end, singleLinkedList<string> array[])
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

void emptyAndReInsert(singleLinkedList<string> oldTree, singleLinkedList<string> **array, int length)
{
    string tempString;
    int temp;
    while(oldTree.getSize() > 0)
    {
        oldTree.remove(tempString);
        wordStruct tempWord(tempString, length);
        for (int l = 0; l < 26; l++)
        {
            temp = tempWord.letters[l];
            array[l][temp].insert(tempString);
        }
    }
}

/*int* pascal(int row)
{
    int *triangleRow = new int[row+1];
    triangleRow[0] = 1;
    if (row <= 0)
    {
        return triangleRow;
    }
    triangleRow[row] = 1;
    int* triangleRow2 = pascal(row-1);
    
    for (int i = 1; i < row; i++)
    {
        triangleRow[i] = (triangleRow2[i] + triangleRow2[i-1]);
    }
    
    delete triangleRow2;
    
    return triangleRow;
}*/

void combinations(singleLinkedList<string> &gameTree, int beginning, int stringLength, int numberOfLetters, char c, char guessesArray[])
{
    singleLinkedList<string> combos[stringLength];
    int i, biggest = -1, answer = 0;
    string tempString;
    
    while(!gameTree.isEmpty())
    {
        gameTree.remove(tempString);
        i = beginning;
        while(i < (stringLength-numberOfLetters) && tempString[i] != c)
        {
            i++;
        }
        combos[i].insert(tempString);
    }
    
    for (int j = beginning; j < stringLength; j++)
    {
        //cout << "Location: " << j << "\t" << combos[j].getSize() << endl;
        if (combos[j].getSize() > biggest)
        {
            answer = j;
            biggest = combos[j].getSize();
        }
    }
    
    guessesArray[answer] = c;
    
    swap(gameTree, combos[answer]);
    numberOfLetters--;
    if (numberOfLetters > 0)
    {
        combinations(gameTree, (answer+1), stringLength, numberOfLetters, c, guessesArray);
    }
}

void attemptCheck(bool &victory, int selectionLength, char guessesArray[], int answer, int &attempts, bool &gameOver)
{
    victory = true;
    for (int i = 0; i < selectionLength; i++)
    {
        //cout << guessesArray[i] << " ";
        if (guessesArray[i] == '_')
        {
            victory = false;
        }
    }
    
    if (answer == 0)
    {
        attempts++;
    }
    
    //cout << endl << "You have " << (12 - attempts) << " attempts remaining!!!" << endl;
    if (attempts >= 12)
    {
        gameOver = true;
    }
}

bool endGame(bool victory, bool gameOver)
{
    string letterStr;
    char key = '\0';
    bool correctAnswer = false;
    const Uint8 *currentKeyStates;
    LTexture endOfGame, question;
    /*SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
    SDL_RenderClear(gRenderer);
    if (victory)
    {
        endOfGame.loadWord("congratulations!!! you saved the hangman!!", 0, (SCREEN_HEIGHT/2));
        //cout << "Congratulations!!! You saved the hangman!!" << endl;
    }
    else
    {
        endOfGame.loadWord("game over!! murderer!!!!!", 0, (SCREEN_HEIGHT/2));
        //cout << "Game over!! Murderer!!!!!" << endl;
    }*/
    
    //endOfGame.render((SCREEN_WIDTH - endOfGame.getWidth()) / 2, (SCREEN_HEIGHT - endOfGame.getHeight()) / 2);
    //SDL_RenderClear(gRenderer);
    //SDL_RenderPresent(gRenderer);
    
    while (!correctAnswer)
    {
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0x00);
        SDL_RenderClear(gRenderer);
        if (victory)
        {
            endOfGame.loadWord("congratulations!!! you saved the hangman!!", 0, (SCREEN_HEIGHT/2));
            //cout << "Congratulations!!! You saved the hangman!!" << endl;
        }
        else
        {
            endOfGame.loadWord("game over!! murderer!!!!!", 0, (SCREEN_HEIGHT/2));
            //cout << "Game over!! Murderer!!!!!" << endl;
        }
        question.loadWord("would you like to play again? (y/n)", 0, ((SCREEN_HEIGHT/2)+50));
        //SDL_RenderClear(gRenderer);
        //endOfGame.render((SCREEN_WIDTH - endOfGame.getWidth()) / 2, (SCREEN_HEIGHT - endOfGame.getHeight()) / 2);
        //question.render((SCREEN_WIDTH - endOfGame.getWidth()) / 2, ((SCREEN_HEIGHT - endOfGame.getHeight()) / 2) + endOfGame.getHeight());
        SDL_RenderPresent(gRenderer);
        //cout << "Would you like to play again? (y/n)" << endl;
        //cin >> letterStr;
        //tempChar = letterStr[0];
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_KEYDOWN)
            {
                key = '\0';
                
                currentKeyStates = SDL_GetKeyboardState( NULL );
                if(currentKeyStates[SDL_SCANCODE_N]) key = 'n';
                if(currentKeyStates[SDL_SCANCODE_Y]) key = 'y';
            }
            
            if (key == 'y')
            {
                gameOver = false;
                correctAnswer = true;
            }
            else if (key == 'n')
            {
                gameOver = true;
                correctAnswer = true;
            }
        }
    }
    
    question.free();
    endOfGame.free();
    
    return gameOver;
}
