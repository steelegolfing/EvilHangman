#ifndef buildHangman_h
#define buildHangman_h
#include "renderLetters.h"
#include "SDL_Plotter.h"
#include "Single_Linked_List.h"
#include "wordStruct.h"
using namespace std;

class renderHangman
{
private:
    SDL_Renderer *gRenderer;
    int SCREEN_WIDTH = 920;
    int SCREEN_HEIGHT = 640;
    /*
     * function: drawGallows
     * description: draws the gallows to hang the hangman
     * precondition: an instance of the plotter class exists
     * postcondition: the gallows have been rendered
     * return: void
     */
    void drawGallows()
    {
        //build gallows
        SDL_SetRenderDrawColor(gRenderer, 0x8B, 0x45, 0x13, 0xFF);
        //Top bar
        SDL_RenderDrawLine(gRenderer, ((SCREEN_WIDTH-40)-340), 40, (SCREEN_WIDTH-40), 40);
        SDL_RenderDrawLine(gRenderer, ((SCREEN_WIDTH-40)-340), 41, (SCREEN_WIDTH-40), 41);
        SDL_RenderDrawLine(gRenderer, ((SCREEN_WIDTH-40)-340), 42, (SCREEN_WIDTH-40), 42);
        //Noose side
        SDL_RenderDrawLine(gRenderer, ((SCREEN_WIDTH-40)-340), 40, ((SCREEN_WIDTH-40)-340), 50);
        SDL_RenderDrawLine(gRenderer, ((SCREEN_WIDTH-40)-339), 40, ((SCREEN_WIDTH-40)-339), 50);
        SDL_RenderDrawLine(gRenderer, ((SCREEN_WIDTH-40)-338), 40, ((SCREEN_WIDTH-40)-338), 50);
        //Support side
        SDL_RenderDrawLine(gRenderer, (SCREEN_WIDTH-42), 40, (SCREEN_WIDTH-42), 440);
        SDL_RenderDrawLine(gRenderer, (SCREEN_WIDTH-41), 40, (SCREEN_WIDTH-41), 440);
        SDL_RenderDrawLine(gRenderer, (SCREEN_WIDTH-40), 40, (SCREEN_WIDTH-40), 440);
        //Base
        SDL_RenderDrawLine(gRenderer, (SCREEN_WIDTH-400), 440, SCREEN_WIDTH, 440);
        SDL_RenderDrawLine(gRenderer, (SCREEN_WIDTH-400), 441, SCREEN_WIDTH, 441);
        SDL_RenderDrawLine(gRenderer, (SCREEN_WIDTH-400), 442, SCREEN_WIDTH, 442);
    }
    
    /*
     * function: drawHead
     * description: draws the head of the hangman
     * precondition: an instance of the plotter class exists
     * postcondition: the hangman's head is rendered
     * return: void
     */
    void drawHead()
    {
        int tempWidth = SCREEN_WIDTH-40;
        drawGallows();
        //draw hair
        SDL_SetRenderDrawColor(gRenderer, 0x00, 0xCC, 0x00, 0xFF);
        SDL_RenderDrawLine(gRenderer, ((tempWidth)-339), 50, ((tempWidth)-319), 65);
        SDL_RenderDrawLine(gRenderer, ((tempWidth)-359), 65, ((tempWidth)-339), 50);
        SDL_RenderDrawLine(gRenderer, ((tempWidth)-364), 60, ((tempWidth)-359), 65);
        SDL_RenderDrawLine(gRenderer, ((tempWidth)-319), 65, ((tempWidth)-314), 60);
        SDL_RenderDrawLine(gRenderer, ((tempWidth)-375), 75, ((tempWidth)-364), 60);
        SDL_RenderDrawLine(gRenderer, ((tempWidth)-314), 60, ((tempWidth)-304), 75);
        SDL_RenderDrawLine(gRenderer, ((tempWidth)-375), 75, ((tempWidth)-370), 100);
        SDL_RenderDrawLine(gRenderer, ((tempWidth)-305), 75, ((tempWidth)-310), 100);
        //draw head
        SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_Rect tempRect;
        tempRect.x = tempWidth-367;
        tempRect.y = 95;
        tempRect.w = 55;
        tempRect.h = 55;
        SDL_RenderDrawRect(gRenderer, &tempRect);
    }
    
    /*
     * function: drawBody
     * description: draws the body and head of the hangman
     * precondition: an instance of the plotter class exists
     * postcondition: the hangman's body is rendered along with the head
     * return: void
     */
    void drawBody()
    {
        int tempWidth = SCREEN_WIDTH - 40;
        //draws rest of body parts
        drawHead();
        //trapezoid body shape
        SDL_SetRenderDrawColor(gRenderer, 0x00, 0xCC, 0x00, 0xFF);
        SDL_Rect tempRect;
        tempRect.x = tempWidth-377;
        tempRect.y = 150;
        tempRect.w = 75;
        tempRect.h = 90;
        SDL_Surface *tempSurface;
        tempSurface = SDL_CreateRGBSurface(0, 75, 90, 32, 0, 0, 0, 0xFF);
        SDL_FillRect(tempSurface, &tempRect, SDL_MapRGB( tempSurface->format, 0x00, 0xCC, 0x00));
        SDL_RenderFillRect(gRenderer, &tempRect);
        
        //Draw cape
        SDL_SetRenderDrawColor(gRenderer, 0x99, 0x00, 0xCC, 0xFF);
        for (int i = 0; i < 55; i++)
        {
            SDL_RenderDrawLine(gRenderer, ((tempWidth)-(377+i)), 150+(1.636*i), ((tempWidth)-(377+i)), 239);
            SDL_RenderDrawLine(gRenderer, ((tempWidth)-(303-i)), 150+(1.636*i), ((tempWidth)-(303-i)), 239);
        }
    }
    
    /*
     * function: drawLArm
     * description: draws the hangman's left arm, along with the body and head
     * precondition: an instance of the plotter class exists
     * postcondition: the hangman's left arm is rendered along with the body and head
     * return: void
     */
    void drawLArm()
    {
        int tempWidth = SCREEN_WIDTH - 40;
        //draws rest of body parts
        drawBody();
        //draw left shoulder
        SDL_SetRenderDrawColor(gRenderer, 0xD2, 0x4D, 0xFF, 0xFF);
        SDL_Rect tempRect;
        tempRect.x = tempWidth-401;
        tempRect.y = 155;
        tempRect.w = 25;
        tempRect.h = 20;
        SDL_Surface *tempSurface;
        tempSurface = SDL_CreateRGBSurface(0, 25, 20, 32, 0, 0, 0, 0);
        SDL_FillRect(tempSurface, &tempRect, SDL_MapRGB(tempSurface->format, 0xD2, 0x4D, 0xFF));
        SDL_RenderFillRect(gRenderer, &tempRect);
        //draw left arm
        SDL_Rect tempRect2;
        tempRect2.x = tempWidth-402;
        tempRect2.y = 155;
        tempRect2.w = 20;
        tempRect2.h = 80;
        SDL_Surface *tempSurface2;
        tempSurface2 = SDL_CreateRGBSurface(0, 20, 80, 32, 0, 0, 0, 0);
        SDL_FillRect(tempSurface2, &tempRect2, SDL_MapRGB(tempSurface2->format, 0xD2, 0x4D, 0xFF));
        SDL_RenderFillRect(gRenderer, &tempRect2);
    }
    
    /*
     * function: drawRArm
     * description: draws the hangman's right arm, along with the body, head, and left arm
     * precondition: an instance of the plotter class exists
     * postcondition: the hangman's right arm is rendered along with the body, head, and left arm
     * return: void
     */
    void drawRArm()
    {
        int tempWidth = SCREEN_WIDTH - 40;
        //draws rest of body parts
        drawLArm();
        //draw right shoulder
        SDL_SetRenderDrawColor(gRenderer, 0xD2, 0x4D, 0xFF, 0xFF);
        SDL_Rect tempRect;
        tempRect.x = tempWidth-303;
        tempRect.y = 155;
        tempRect.w = 25;
        tempRect.h = 20;
        SDL_Surface *tempSurface;
        tempSurface = SDL_CreateRGBSurface(0, 25, 20, 32, 0, 0, 0, 0);
        SDL_FillRect(tempSurface, &tempRect, SDL_MapRGB(tempSurface->format, 0xD2, 0x4D, 0xFF));
        SDL_RenderFillRect(gRenderer, &tempRect);
        
        //draw right arm
        SDL_Rect tempRect2;
        tempRect2.x = tempWidth-298;
        tempRect2.y = 155;
        tempRect2.w = 20;
        tempRect2.h = 80;
        SDL_Surface *tempSurface2;
        tempSurface2 = SDL_CreateRGBSurface(0, 20, 80, 32, 0, 0, 0, 0);
        SDL_FillRect(tempSurface2, &tempRect2, SDL_MapRGB(tempSurface2->format, 0xD2, 0x4D, 0xFF));
        SDL_RenderFillRect(gRenderer, &tempRect2);
    }
    /*
     * function: drawLLeg
     * description: draws the hangman's left leg, along with the rest of the body parts
     * precondition: an instance of the plotter class exists
     * postcondition: the hangman's left leg is rendered along with the rest of the body parts
     * return: void
     */
    void drawLLeg()
    {
        int tempWidth = SCREEN_WIDTH - 40;
        //draws rest of body parts
        drawRArm();
        //draw left leg
        SDL_SetRenderDrawColor(gRenderer, 0x99, 0x00, 0xCC, 0xFF);
        SDL_Rect tempRect;
        tempRect.x = tempWidth-376;
        tempRect.y = 240;
        tempRect.w = 36;
        tempRect.h = 80;
        SDL_Surface *tempSurface;
        tempSurface = SDL_CreateRGBSurface(0, 36, 80, 32, 0, 0, 0, 0xFF);
        SDL_FillRect(tempSurface, &tempRect, SDL_MapRGB( tempSurface->format, 0x99, 0x00, 0xCC));
        SDL_RenderFillRect(gRenderer, &tempRect);
    }
    
    /*
     * function: drawRLeg
     * description: draws the hangman's right leg, along with the rest of the body parts
     * precondition: an instance of the plotter class exists
     * postcondition: the hangman's right leg is rendered along with the rest of the body parts
     * return: void
     */
    void drawRLeg()
    {
        int tempWidth = SCREEN_WIDTH - 40;
        //draws rest of body parts
        drawLLeg();
        //draw right leg
        SDL_SetRenderDrawColor(gRenderer, 0x99, 0x00, 0xCC, 0xFF);
        SDL_Rect tempRect;
        tempRect.x = tempWidth-339;
        tempRect.y = 240;
        tempRect.w = 36;
        tempRect.h = 80;
        SDL_Surface *tempSurface;
        tempSurface = SDL_CreateRGBSurface(0, 36, 80, 32, 0, 0, 0, 0xFF);
        SDL_FillRect(tempSurface, &tempRect, SDL_MapRGB( tempSurface->format, 0x99, 0x00, 0xCC));
        SDL_RenderFillRect(gRenderer, &tempRect);
    }
    
    /*
     * function: drawFace
     * description: draws the hangman's face, along with the rest of the body parts
     * precondition: an instance of the plotter class exists
     * postcondition: the hangman's face is rendered along with the rest of the body parts
     * return: void
     */
    void drawFace()
    {
        int tempWidth = SCREEN_WIDTH - 40;
        //draws rest of body parts
        drawRLeg();
        //draw eyebrows
        SDL_SetRenderDrawColor(gRenderer, 0x00, 0xCC, 0x00, 0xFF);
        for (int i = 0; i < 6; i++)
        {
            SDL_RenderDrawLine(gRenderer, (tempWidth-324)-(i*2), 101+i, (tempWidth-324)-(i*2), 104+i);
            SDL_RenderDrawLine(gRenderer, (tempWidth-323)-(i*2), 101+i, (tempWidth-323)-(i*2), 104+i);
        }
        for (int i = 0; i < 6; i++)
        {
            SDL_RenderDrawLine(gRenderer, (tempWidth-346)-(i*2), 106-i, (tempWidth-346)-(i*2), 109-i);
            SDL_RenderDrawLine(gRenderer, (tempWidth-345)-(i*2), 106-i, (tempWidth-345)-(i*2), 109-i);
        }
        
        //draw eyes
        SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
        for(int i = 1; i <= 5; i++)
        {
            for(int j = 0; j < i; j++)
            {
                SDL_RenderDrawPoint(gRenderer, (tempWidth-352)+j, 110+i);
                SDL_RenderDrawPoint(gRenderer, (tempWidth-327)+j, 110+i);
                
                SDL_RenderDrawPoint(gRenderer, (tempWidth-352)-j, 110+i);
                SDL_RenderDrawPoint(gRenderer, (tempWidth-327)-j, 110+i);
            }
        }
        for (int i = 5; i >= 0; i--)
        {
            for(int j = i; j >= 0; j--)
            {
                SDL_RenderDrawPoint(gRenderer, (tempWidth-352)+j, 121-i);
                SDL_RenderDrawPoint(gRenderer, (tempWidth-327)+j, 121-i);
                
                SDL_RenderDrawPoint(gRenderer, (tempWidth-352)-j, 121-i);
                SDL_RenderDrawPoint(gRenderer, (tempWidth-327)-j, 121-i);
            }
        }
        
        //draw mouth
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
        SDL_RenderDrawLine(gRenderer, (tempWidth-352), 130, (tempWidth-352), 140);
        SDL_RenderDrawLine(gRenderer, (tempWidth-352), 140, (tempWidth-327), 140);
        SDL_RenderDrawLine(gRenderer, (tempWidth-327), 130, (tempWidth-327), 140);
    }
    
    /*
     * function: drawLHand
     * description: draws the hangman's left hand, along with the rest of the body parts
     * precondition: an instance of the plotter class exists
     * postcondition: the hangman's left hand is rendered along with the rest of the body parts
     * return: void
     */
    void drawLHand()
    {
        int tempWidth = SCREEN_WIDTH - 40;
        //draws rest of body parts
        drawFace();
        //draw left hand
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderDrawLine(gRenderer, tempWidth-396, 235, tempWidth-388, 235);
        SDL_RenderDrawLine(gRenderer, tempWidth-396, 236, tempWidth-388, 236);
        SDL_RenderDrawLine(gRenderer, tempWidth-396, 237, tempWidth-388, 237);
        SDL_RenderDrawLine(gRenderer, tempWidth-396, 238, tempWidth-388, 238);
        SDL_RenderDrawLine(gRenderer, tempWidth-396, 239, tempWidth-388, 239);
        SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderDrawLine(gRenderer, tempWidth-397, 235, tempWidth-397, 240);
        SDL_RenderDrawLine(gRenderer, tempWidth-387, 235, tempWidth-387, 240);
        SDL_RenderDrawLine(gRenderer, tempWidth-407, 240, tempWidth-397, 240);
        SDL_RenderDrawLine(gRenderer, tempWidth-387, 240, tempWidth-377, 240);
        SDL_RenderDrawLine(gRenderer, tempWidth-407, 240, tempWidth-407, 250);
        SDL_RenderDrawLine(gRenderer, tempWidth-377, 240, tempWidth-377, 250);
        SDL_RenderDrawLine(gRenderer, tempWidth-407, 250, tempWidth-402, 250);
        SDL_RenderDrawLine(gRenderer, tempWidth-382, 250, tempWidth-377, 250);
        SDL_RenderDrawLine(gRenderer, tempWidth-402, 245, tempWidth-402, 250);
        SDL_RenderDrawLine(gRenderer, tempWidth-382, 245, tempWidth-382, 250);
        SDL_RenderDrawLine(gRenderer, tempWidth-402, 245, tempWidth-382, 245);
    }
    /*
     * function: drawRHand
     * description: draws the hangman's right hand, along with the rest of the body parts
     * precondition: an instance of the plotter class exists
     * postcondition: the hangman's right hand is rendered along with the rest of the body parts
     * return: void
     */
    void drawRHand()
    {
        int tempWidth = SCREEN_WIDTH - 40;
        //draws rest of body parts
        drawLHand();
        //draw right hand
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderDrawLine(gRenderer, tempWidth-292, 235, tempWidth-284, 235);
        SDL_RenderDrawLine(gRenderer, tempWidth-292, 236, tempWidth-284, 236);
        SDL_RenderDrawLine(gRenderer, tempWidth-292, 237, tempWidth-284, 237);
        SDL_RenderDrawLine(gRenderer, tempWidth-292, 238, tempWidth-284, 238);
        SDL_RenderDrawLine(gRenderer, tempWidth-292, 239, tempWidth-284, 239);
        SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderDrawLine(gRenderer, tempWidth-293, 235, tempWidth-293, 240);
        SDL_RenderDrawLine(gRenderer, tempWidth-283, 235, tempWidth-283, 240);
        SDL_RenderDrawLine(gRenderer, tempWidth-303, 240, tempWidth-293, 240);
        SDL_RenderDrawLine(gRenderer, tempWidth-283, 240, tempWidth-273, 240);
        SDL_RenderDrawLine(gRenderer, tempWidth-303, 240, tempWidth-303, 250);
        SDL_RenderDrawLine(gRenderer, tempWidth-273, 240, tempWidth-273, 250);
        SDL_RenderDrawLine(gRenderer, tempWidth-303, 250, tempWidth-298, 250);
        SDL_RenderDrawLine(gRenderer, tempWidth-278, 250, tempWidth-273, 250);
        SDL_RenderDrawLine(gRenderer, tempWidth-298, 245, tempWidth-298, 250);
        SDL_RenderDrawLine(gRenderer, tempWidth-278, 245, tempWidth-278, 250);
        SDL_RenderDrawLine(gRenderer, tempWidth-298, 245, tempWidth-278, 245);
    }
    /*
     * function: drawLFoot
     * description: draws the hangman's left foot, along with the rest of the body parts
     * precondition: an instance of the plotter class exists
     * postcondition: the hangman's left foot is rendered along with the rest of the body parts
     * return: void
     */
    void drawLFoot()
    {
        int tempWidth = SCREEN_WIDTH - 40;
        //draws rest of body parts
        drawRHand();
        //draw left foot
        SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_Rect tempRect;
        tempRect.x = tempWidth-376;
        tempRect.y = 320;
        tempRect.w = 36;
        tempRect.h = 20;
        SDL_Surface *tempSurface;
        tempSurface = SDL_CreateRGBSurface(0, 36, 20, 32, 0, 0, 0, 0xFF);
        SDL_FillRect(tempSurface, &tempRect, SDL_MapRGB( tempSurface->format, 0x99, 0x00, 0xCC));
        SDL_RenderFillRect(gRenderer, &tempRect);
    }
    
    /*
     * function: drawRFoot
     * description: draws the hangman's right foot, along with the rest of the body parts
     * precondition: an instance of the plotter class exists
     * postcondition: the hangman's right foot is rendered along with the rest of the body parts
     * return: void
     */
    void drawRFoot()
    {
        int tempWidth = SCREEN_WIDTH - 40;
        //draws rest of body parts
        drawLFoot();
        //draw right foot
        SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_Rect tempRect;
        tempRect.x = tempWidth-339;
        tempRect.y = 320;
        tempRect.w = 36;
        tempRect.h = 20;
        SDL_Surface *tempSurface;
        tempSurface = SDL_CreateRGBSurface(0, 36, 20, 32, 0, 0, 0, 0xFF);
        SDL_FillRect(tempSurface, &tempRect, SDL_MapRGB( tempSurface->format, 0x99, 0x00, 0xCC));
        SDL_RenderFillRect(gRenderer, &tempRect);
    }
    
    /*
     * function: drawTie
     * description: draws hangman's tie, along with the rest of the body parts
     * precondition: an instance of the plotter class exists
     * postcondition: hangman's tie is rendered along with the rest of the body parts
     * return: void
     */
    void drawTie()
    {
        int tempWidth = SCREEN_WIDTH - 40;
        //draws rest of body parts
        drawRFoot();
        //draw hangmans tie
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x99, 0x33, 0xFF);
        for (int i = 5; i >= 0; i--)
        {
            for(int j = i; j >= 0; j--)
            {
                SDL_RenderDrawPoint(gRenderer, (tempWidth-340)+j, 155-i);
                
                SDL_RenderDrawPoint(gRenderer, (tempWidth-340)-j, 155-i);
            }
        }
        
        for(int i = 1; i <= 40; i++)
        {
            for(int j = 0; j < i; j++)
            {
                SDL_RenderDrawPoint(gRenderer, (tempWidth-340)+(j*.25), 155+i);
        
                SDL_RenderDrawPoint(gRenderer, (tempWidth-340)-(j*.25), 155+i);
            }
        }
        
        for (int i = 10; i >= 0; i--)
        {
            for(int j = i; j >= 0; j--)
            {
                SDL_RenderDrawPoint(gRenderer, (tempWidth-340)+j, 205-i);
                
                SDL_RenderDrawPoint(gRenderer, (tempWidth-340)-j, 205-i);
            }
        }
        
        //SDL_Delay(20000);
    }
public:
    renderHangman(SDL_Renderer* g, int attempts)
    {
        gRenderer = g;
        switch (attempts)
        {
            case 0:
                drawGallows();
                break;
            case 1:
                drawHead();
                break;
            case 2:
                drawBody();
                break;
            case 3:
                drawLArm();
                break;
            case 4:
                drawRArm();
                break;
            case 5:
                drawLLeg();
                break;
            case 6:
                drawRLeg();
                break;
            case 7:
                drawFace();
                break;
            case 8:
                drawLHand();
                break;
            case 9:
                drawRHand();
                break;
            case 10:
                drawLFoot();
                break;
            case 11:
                drawRFoot();
                break;
            case 12:
                drawTie();
                break;
        }
    }
};



#endif /* buildHangman_h */
