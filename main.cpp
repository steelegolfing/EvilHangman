/*
 * Author: Hang-In-There
 * File Name: main.cpp
 * File Description: 
 * Date Created: 3/29/2017
 * Date Last Modified: 4/30/2017
 */

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

int difficultyLevel(singleLinkedList<string> [], SDL_Event&, bool&, int&);
int randomizer(int, int, singleLinkedList<string> []);
bool checkResponses(char&, bool[]);
void emptyAndReInsert(singleLinkedList<string>, singleLinkedList<string>**, int);
void combinations(singleLinkedList<string>&, int, int, int, char, char[]);
void attemptCheck(bool&, int, char[], int, int&, bool&, int&);
bool endGame(bool, bool, bool&);

int main(int argc, const char * argv[])
{
    ifstream dictionaryFile;
    int answer, size, selectionLength = 0, attempts, firstDimension, secondDimension, MAX_ATTEMPTS;
    singleLinkedList<string> charCount[30], gameTree, **alphaList = nullptr;
    string tempString, letterStr, answerString, incorrectGuesses = " ", evilWordString;
    bool correctAnswer, gameOver = false, responses[26] = {false}, correct[26] = {false}, victory;
    char tempChar, key;
    const Uint8 *currentKeyStates;
    LTexture evilWord, incorrectLetters;
    
    
    
    string mehString = " ";
    //Start up SDL and create window
    if( !init() )
    {
        printf( "Failed to initialize!\n" );
    }
    else
    {
        //Load media
        dictionaryFile.open("dictionary.txt") ;
        if( !dictionaryFile.is_open())
        {
            printf( "Failed to load dictionary!!\n" );
        }
        else
        {
            // Reading in the dictionary
            while(dictionaryFile >> tempString)
            {
                size = int(tempString.length());
                charCount[size].insert(tempString);
            }
            
            //Main loop flag
            bool quit = false;
            
            //Event handler
            SDL_Event e;
            
            while (!gameOver && !quit)
            {
                //gameOver = false;
                victory = false;
                correctAnswer = false;
                attempts = 0;
                selectionLength = difficultyLevel(charCount, e, quit, MAX_ATTEMPTS);
                
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
                }
                
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(gRenderer);
                evilWord.loadWord(evilWordString, 0, ((SCREEN_HEIGHT/4)*3));
                incorrectLetters.loadWord(incorrectGuesses, 50, 50);
                renderHangman(gRenderer, attempts);
                SDL_RenderPresent(gRenderer);
                
                while(!gameOver && !victory)
                {
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
                    }
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
                    
                    attemptCheck(victory, selectionLength, guessesArray, answer, attempts, gameOver, MAX_ATTEMPTS);
                    
                    evilWordString = "";
                    for (int i = 0; i < selectionLength; i++)
                    {
                        evilWordString = evilWordString + guessesArray[i];
                    }
                    
                    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                    SDL_RenderClear(gRenderer);
                    evilWord.loadWord(evilWordString, 0, ((SCREEN_HEIGHT/4)*3));
                    incorrectLetters.loadWord(incorrectGuesses, 50, 50);
                    
                    renderHangman(gRenderer, attempts);
                    SDL_RenderPresent(gRenderer);
                    if (attempts == MAX_ATTEMPTS)
                    {
                        SDL_Delay(1500);
                    }
                }
                
                incorrectLetters.free();
                evilWord.free();
                SDL_RenderClear(gRenderer);
                gameOver = endGame(victory, gameOver, quit);
            }

        }
    }
    
  
    //Free resources and close SDL
    close();
    
    return 0;
}

/*
*   function: difficultyLevel
*   description: draws prompt for user to decide difficulty/ randomly decides word length based 
*   on user input for difficulty 
*   precondition: an SDL instance exists and game mode has begun
*   postcondition: a word length has been decided
*   return: int-word length
*/

int difficultyLevel(singleLinkedList<string> charCount[], SDL_Event &e, bool &quit, int& MAX_ATTEMPTS)
{
    bool correctAnswer = false;
    string letterStr;
    int selectionLength = 0;
    LTexture difficulty;
    const Uint8 *currentKeyStates;
    char key;
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(gRenderer);
    while (!correctAnswer && !quit)
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
                if(currentKeyStates[SDL_SCANCODE_1]) key = '1';
                if(currentKeyStates[SDL_SCANCODE_2]) key = '2';
                if(currentKeyStates[SDL_SCANCODE_3]) key = '3';
                
                switch (key)
                {
                    case '1':
                        correctAnswer = true;
                        selectionLength = randomizer(11,29, charCount);
                        MAX_ATTEMPTS = 7;
                        break;
                    case '2':
                        correctAnswer = true;
                        selectionLength = randomizer(6, 10, charCount);
                        MAX_ATTEMPTS = 9;
                        break;
                    case '3':
                        correctAnswer = true;
                        selectionLength = randomizer(2, 5, charCount);
                        MAX_ATTEMPTS = 12;
                        break;
                }

            }
        }
        
        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( gRenderer );
        difficulty.loadWord("would you like beg(1), int(2), or adv(3)?", 0, (SCREEN_HEIGHT/2));
        SDL_RenderPresent(gRenderer);
    }

    difficulty.free();
    
    return selectionLength;
}


/*
*   function: randomizer
*   description: determines the length of word based off of a given range
*   precondition: user has selected difficulty level associated with range of word lengths
*   postcondition: a word length has been decided
*   return: int-word length
*/

int randomizer(int begin, int end, singleLinkedList<string> array[])
{
    int selection;

    srand(time(NULL));
    selection = rand() % (end-begin);
    selection += begin;
    while (selection < begin && (array[selection].getSize() == 0))
    {
        selection = (rand() % (end-begin));
        selection += begin;
    }
    
    return selection;
}

/*
*   function: checkResponses
*   description: confirms if guess is a valid entry or if letter has
*   already been guessed
*   precondition: a guess has been entered by the user
*   postcondition: the validity of the guess has been determined
*   return: bool-if guess is valid or not
*/

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

/*
*   function: emptryAndReInsert
*   description: inserts all strings in singlely linked list into a 2d array bassed on
*   number of each letter present in the word
*   precondition: a singely linked list exists containing the largest set
*   postcondition: a 2d array is constructed organized by number of each letter in a word
*   return: void
*/ 

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

/*
*   function: combinations
*   description: determines the largest set of words with more than one of a particular 
*   letter
*   precondition: a linked list exists
*   postcondition: the largest set from the list is determined
*   return: void
*/

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

/*
*   function: attemptCheck
*   description: checks the current number of attempts and determines if game is over
*   precondition: a game instance is in play
*   postcondition: it is determined whether the game should continue
*   return: void
*/

void attemptCheck(bool &victory, int selectionLength, char guessesArray[], int answer, int &attempts, bool &gameOver, int& MAX_ATTEMPTS)
{
    victory = true;
    for (int i = 0; i < selectionLength; i++)
    {
        if (guessesArray[i] == '_')
        {
            victory = false;
        }
    }
    
    if (answer == 0)
    {
        attempts++;
    }
    
    if (attempts >= MAX_ATTEMPTS)
    {
        gameOver = true;
    }
}

/*
*   function: endGame
*   description: finishes current game and ends game based on user input 
*   precondition: a game has been won or lost
*   postcondition: game is restarted or ended
*   return: bool-state of game
*/ 

bool endGame(bool victory, bool gameOver, bool &quit)
{
    string letterStr;
    char key = '\0';
    bool correctAnswer = false;
    const Uint8 *currentKeyStates;
    LTexture endOfGame, question;
    
    while (!correctAnswer && !quit)
    {
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0x00);
        SDL_RenderClear(gRenderer);
        if (victory)
        {
            endOfGame.loadWord("congratulations!!! you saved the hangman!!", 0, (SCREEN_HEIGHT/2));
        }
        else
        {
            endOfGame.loadWord("game over!! murderer!!!!!", 0, (SCREEN_HEIGHT/2));
        }
        question.loadWord("would you like to play again? (y/n)", 0, ((SCREEN_HEIGHT/2)+50));

        SDL_RenderPresent(gRenderer);
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0)
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
                quit = true;
            }
        }
    }
    
    question.free();
    endOfGame.free();
    
    return gameOver;
}
