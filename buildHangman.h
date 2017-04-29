#ifndef buildHangman_h
#define buildHangman_h
#include "renderLetters.h"
#include "SDL_Plotter.h"
#include "Single_Linked_List.h"
#include "wordStruct.h"
using namespace std;

//draw gallows
void drawGallows(){
    SDL_SetRenderDrawColor(gRender, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderDrawLine();
    SDL_RenderDrawLine();
    SDL_RenderDrawLine();
    SDL_RenderDrawLine();
}

//draw head
void drawHead(){
    SDL_SetRenderDrawColor(gRender, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderDrawLine();
    SDL_RenderDrawLine();
    SDL_RenderDrawLine();
    SDL_RenderDrawLine();
    //topper
    SDL_SetRenderDrawColor(gRender, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderDrawLine();
    SDL_RenderDrawLine();
    SDL_RenderDrawLine();
}
//draw body
void drawBody(){
    //trapezoid body shape
    SDL_SetRenderDrawColor(gRender, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderDrawLine();
    SDL_RenderDrawLine();
    SDL_RenderDrawLine();
    SDL_RenderDrawLine();
    drawHead();
}
//draw larm
void drawLArm(){
    SDL_SetRenderDrawColor(gRender, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderDrawLine();
    SDL_RenderDrawLine();
    SDL_RenderDrawLine();
    SDL_RenderDrawLine();
    drawBody();
    drawHead();
}
//draw rarm
void drawRArm(){
    SDL_SetRenderDrawColor(gRender, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderDrawLine();
    SDL_RenderDrawLine();
    SDL_RenderDrawLine();
    SDL_RenderDrawLine();
    drawLArm():
    drawBody();
    drawHead();
}
//draw lleg
void drawLLeg(){
    SDL_SetRenderDrawColor(gRender, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderDrawLine();
    SDL_RenderDrawLine();
    SDL_RenderDrawLine();
    SDL_RenderDrawLine();
    drawRArm();
    drawLArm();
    drawBody();
    drawHead();
}
//draw rleg
void drawRLeg(){
    SDL_SetRenderDrawColor(gRender, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderDrawLine();
    SDL_RenderDrawLine();
    SDL_RenderDrawLine();
    SDL_RenderDrawLine();
    drawLLeg();
    drawRArm();
    drawLArm();
    drawBody();
    drawHead();
}

//draw face
void drawFace(){
    drawX();
    drawX();
    //draw mouth
    SDL_SetRenderDrawColor(gRender, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderDrawLine();
    SDL_RenderDrawLine();
    SDL_RenderDrawLine();
    
    drawRLeg():
    drawLLeg();
    drawRArm();
    drawLArm();
    drawBody();
   
    drawHead();
}

//draw lhand
void drawLHand(){
    DL_SetRenderDrawColor(gRender, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderDrawLine();
    SDL_RenderDrawLine();
    SDL_RenderDrawLine();
    drawFace();
    drawRLeg():
    drawLLeg();
    drawRArm();
    drawLArm();
    drawBody();
    drawHead();
}

//draw rhand
void drawRHand(){
    DL_SetRenderDrawColor(gRender, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderDrawLine();
    SDL_RenderDrawLine();
    SDL_RenderDrawLine();
    drawLHand();
    drawFace();
    drawRLeg():
    drawLLeg();
    drawRArm();
    drawLArm();
    drawBody();
    drawHead();
}

//draw lfoot
void drawLFoot(){
    DL_SetRenderDrawColor(gRender, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderDrawLine();
    SDL_RenderDrawLine();
    SDL_RenderDrawLine();
    SDL_RenderDrawLine();
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

//draw rfoot
void drawRFoot(){
    DL_SetRenderDrawColor(gRender, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderDrawLine();
    SDL_RenderDrawLine();
    SDL_RenderDrawLine();
    SDL_RenderDrawLine();
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

//draw tie
void drawTie(){
    DL_SetRenderDrawColor(gRender, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderDrawLine();
    SDL_RenderDrawLine();
    SDL_RenderDrawLine();
    SDL_RenderDrawLine();
    SDL_RenderDrawLine();
    SDL_RenderDrawLine();
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
