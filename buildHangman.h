

#ifndef buildHangman_h
#define buildHangman_h
#include "renderLetters.h"
#include "SDL_Plotter.h"
#include "Single_Linked_List.h"
#include "wordStruct.h"
using namespace std;

/*
 * function: drawGallows
 * description: draws the gallows to hang the hangman
 * precondition: an instance of the plotter class exists
 * postcondition: the gallows have been rendered
 * return: void
 */
void drawGallows(){
    //build gallows
    SDL_SetRenderDrawColor(gRender, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderDrawLine();
    SDL_RenderDrawLine();
    SDL_RenderDrawLine();
    SDL_RenderDrawLine();
}

/*
 * function: drawHead
 * description: draws the head of the hangman
 * precondition: an instance of the plotter class exists
 * postcondition: the hangman's head is rendered
 * return: void
 */
void drawHead(){
    //draw major part of head
    SDL_SetRenderDrawColor(gRender, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderDrawLine();
    SDL_RenderDrawLine();
    SDL_RenderDrawLine();
    SDL_RenderDrawLine();
    //draw top piece of head
    SDL_SetRenderDrawColor(gRender, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderDrawLine();
    SDL_RenderDrawLine();
    SDL_RenderDrawLine();
}

/*
 * function: drawBody
 * description: draws the body and head of the hangman
 * precondition: an instance of the plotter class exists
 * postcondition: the hangman's body is rendered along with the head
 * return: void
 */
void drawBody(){
    //trapezoid body shape
    SDL_SetRenderDrawColor(gRender, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderDrawLine();
    SDL_RenderDrawLine();
    SDL_RenderDrawLine();
    SDL_RenderDrawLine();
    //draws rest of body parts
    drawHead();
}

/*
 * function: drawLArm
 * description: draws the hangman's left arm, along with the body and head
 * precondition: an instance of the plotter class exists
 * postcondition: the hangman's left arm is rendered along with the body and head
 * return: void
 */
void drawLArm(){
    //draw left arm
    SDL_SetRenderDrawColor(gRender, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderDrawLine();
    SDL_RenderDrawLine();
    SDL_RenderDrawLine();
    SDL_RenderDrawLine();
    //draws rest of body parts
    drawBody();
    drawHead();
}

/*
 * function: drawRArm
 * description: draws the hangman's right arm, along with the body, head, and left arm
 * precondition: an instance of the plotter class exists
 * postcondition: the hangman's right arm is rendered along with the body, head, and left arm
 * return: void
 */
void drawRArm(){
    //draw right arm
    SDL_SetRenderDrawColor(gRender, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderDrawLine();
    SDL_RenderDrawLine();
    SDL_RenderDrawLine();
    SDL_RenderDrawLine();
    //draws rest of body parts
    drawLArm():
    drawBody();
    drawHead();
}

/*
 * function: drawLLeg
 * description: draws the hangman's left leg, along with the rest of the body parts
 * precondition: an instance of the plotter class exists
 * postcondition: the hangman's left leg is rendered along with the rest of the body parts
 * return: void
 */
void drawLLeg(){
    //draw left leg
    SDL_SetRenderDrawColor(gRender, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderDrawLine();
    SDL_RenderDrawLine();
    SDL_RenderDrawLine();
    SDL_RenderDrawLine();
    //draws rest of body parts
    drawRArm();
    drawLArm();
    drawBody();
    drawHead();
}

/*
 * function: drawRLeg
 * description: draws the hangman's right leg, along with the rest of the body parts
 * precondition: an instance of the plotter class exists
 * postcondition: the hangman's right leg is rendered along with the rest of the body parts
 * return: void
 */
void drawRLeg(){
    //draw right leg
    SDL_SetRenderDrawColor(gRender, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderDrawLine();
    SDL_RenderDrawLine();
    SDL_RenderDrawLine();
    SDL_RenderDrawLine();
    //draws rest of body parts
    drawLLeg();
    drawRArm();
    drawLArm();
    drawBody();
    drawHead();
}

/*
 * function: drawFace
 * description: draws the hangman's face, along with the rest of the body parts
 * precondition: an instance of the plotter class exists
 * postcondition: the hangman's face is rendered along with the rest of the body parts
 * return: void
 */
void drawFace(){
    //draw eyes
    drawX();
    drawX();
    //draw mouth
    SDL_SetRenderDrawColor(gRender, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderDrawLine();
    SDL_RenderDrawLine();
    SDL_RenderDrawLine();
    //draws rest of body parts
    drawRLeg():
    drawLLeg();
    drawRArm();
    drawLArm();
    drawBody();
   
    drawHead();
}

/*
 * function: drawLHand
 * description: draws the hangman's left hand, along with the rest of the body parts
 * precondition: an instance of the plotter class exists
 * postcondition: the hangman's left hand is rendered along with the rest of the body parts
 * return: void
 */
void drawLHand(){
    //draw left hand
    DL_SetRenderDrawColor(gRender, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderDrawLine();
    SDL_RenderDrawLine();
    SDL_RenderDrawLine();
    //draws rest of body parts
    drawFace();
    drawRLeg():
    drawLLeg();
    drawRArm();
    drawLArm();
    drawBody();
    drawHead();
}
/*
 * function: drawRHand
 * description: draws the hangman's right hand, along with the rest of the body parts
 * precondition: an instance of the plotter class exists
 * postcondition: the hangman's right hand is rendered along with the rest of the body parts
 * return: void
 */
void drawRHand(){
    //draw right hand
    DL_SetRenderDrawColor(gRender, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderDrawLine();
    SDL_RenderDrawLine();
    SDL_RenderDrawLine();
    //draws rest of body parts
    drawLHand();
    drawFace();
    drawRLeg():
    drawLLeg();
    drawRArm();
    drawLArm();
    drawBody();
    drawHead();
}
/*
 * function: drawLFoot
 * description: draws the hangman's left foot, along with the rest of the body parts
 * precondition: an instance of the plotter class exists
 * postcondition: the hangman's left foot is rendered along with the rest of the body parts
 * return: void
 */
void drawLFoot(){
    //draw left foot
    DL_SetRenderDrawColor(gRender, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderDrawLine();
    SDL_RenderDrawLine();
    SDL_RenderDrawLine();
    SDL_RenderDrawLine();
    //draws rest of body parts
    drawRHand();
    drawLHand();
    drawFace();
    drawRLeg():
    drawLLeg();
    drawRArm();
    drawLArm();
    drawBody();
    drawHead();
}

/*
 * function: drawRFoot
 * description: draws the hangman's right foot, along with the rest of the body parts
 * precondition: an instance of the plotter class exists
 * postcondition: the hangman's right foot is rendered along with the rest of the body parts
 * return: void
 */
void drawRFoot(){
    //draw right foot
    DL_SetRenderDrawColor(gRender, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderDrawLine();
    SDL_RenderDrawLine();
    SDL_RenderDrawLine();
    SDL_RenderDrawLine();
    //draws rest of body parts
    drawLFoot();
    drawRHand();
    drawLHand();
    drawFace();
    drawRLeg():
    drawLLeg();
    drawRArm();
    drawLArm();
    drawBody();
    drawHead();
}

/*
 * function: drawTie
 * description: draws hangman's tie, along with the rest of the body parts
 * precondition: an instance of the plotter class exists
 * postcondition: hangman's tie is rendered along with the rest of the body parts
 * return: void
 */
void drawTie(){
    //draw hangmans bowtie
    DL_SetRenderDrawColor(gRender, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderDrawLine();
    SDL_RenderDrawLine();
    SDL_RenderDrawLine();
    SDL_RenderDrawLine();
    SDL_RenderDrawLine();
    SDL_RenderDrawLine();
    //draws rest of body parts
    drawRFoot();
    drawLFoot();
    drawRHand();
    drawLHand();
    drawFace();
    drawRLeg():
    drawLLeg();
    drawRArm();
    drawLArm();
    drawBody();
    drawHead();
}



#endif /* buildHangman_h */
