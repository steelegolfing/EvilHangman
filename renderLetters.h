//
//  renderLetters.h
//  3334 - Group Project
//
//  Created by Travis Cox on 4/29/17.
//  Copyright © 2017 Travis Cox. All rights reserved.
//

#ifndef renderLetters_h
#define renderLetters_h

class renderLetters
{
private:
    string word;
    SDL_Renderer *gRenderer;
    int WIDTH = 15, HEIGHT = 20, SPACE_BETWEEN_LETTERS = 5, wordLength;
    
    void drawB(int startX, int startY)
    {
        //Draw b
        SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderDrawLine(gRenderer, startX, (startY-HEIGHT), startX, (startY+HEIGHT));
        SDL_RenderDrawLine(gRenderer, (startX+WIDTH), startY, (startX+WIDTH), (startY+HEIGHT));
        SDL_RenderDrawLine(gRenderer, startX, startY, (startX+WIDTH), startY);
        SDL_RenderDrawLine(gRenderer, startX, (startY+HEIGHT), (startX+WIDTH), (startY+HEIGHT));
    }
    
    void drawO(int startX, int startY)
    {
        //Draw o
        SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderDrawLine(gRenderer, startX, startY, startX, (startY+HEIGHT));
        SDL_RenderDrawLine(gRenderer, startX, startY, (startX+WIDTH), startY);
        SDL_RenderDrawLine(gRenderer, (startX+WIDTH), startY, (startX+WIDTH), (startY+HEIGHT));
        SDL_RenderDrawLine(gRenderer, startX, (startY+HEIGHT), (startX+WIDTH), (startY+HEIGHT));
    }
    
    void drawM(int startX, int startY)
    {
        //Draw m
        SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderDrawLine(gRenderer, startX, (startY-5), startX, (startY+HEIGHT));
        SDL_RenderDrawLine(gRenderer, startX, startY, (startX+WIDTH), startY);
        SDL_RenderDrawLine(gRenderer, (startX+(WIDTH/2)), startY, (startX+(WIDTH/2)), (startY+HEIGHT));
        SDL_RenderDrawLine(gRenderer, (startX+WIDTH), startY, (startX+WIDTH), (startY+HEIGHT));
    }
    
    void drawE(int startX, int startY)
    {
        //Draw e
        SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderDrawLine(gRenderer, startX, startY, startX, (startY+HEIGHT));
        SDL_RenderDrawLine(gRenderer, startX, startY, (startX+WIDTH), startY);
        SDL_RenderDrawLine(gRenderer, startX, (startY+10),(startX+WIDTH), (startY+10));
        SDL_RenderDrawLine(gRenderer, startX, (startY+HEIGHT), (startX+WIDTH), (startY+HEIGHT));
        SDL_RenderDrawLine(gRenderer, (startX+WIDTH), startY, (startX+WIDTH), (startY+10));
    }
    
    void drawR(int startX, int startY)
    {
        //Draw r
        SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderDrawLine(gRenderer, startX, startY, (startX+WIDTH), startY);
        SDL_RenderDrawLine(gRenderer, startX, (startY-5), startX, (startY+HEIGHT));
        SDL_RenderDrawLine(gRenderer, (startX+WIDTH), startY, (startX+WIDTH), (startY+5));
    }
    
    void drawA(int startX, int startY)
    {
        //Draw a
        SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderDrawLine(gRenderer, startX, (startY+5), startX, (startY+(HEIGHT-3)));
        SDL_RenderDrawLine(gRenderer, startX, startY, (startX+WIDTH), startY);
        SDL_RenderDrawLine(gRenderer, startX, (startY+5), (startX+WIDTH), (startY+5));
        SDL_RenderDrawLine(gRenderer, startX, (startY+(HEIGHT-3)), (startX+WIDTH), (startY+(HEIGHT-3)));
        SDL_RenderDrawLine(gRenderer, (startX+WIDTH), startY, (startX+WIDTH), (startY+HEIGHT));
    }
    
    void drawN(int startX, int startY)
    {
        //Draw n
        SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderDrawLine(gRenderer, startX, (startY-5), startX, (startY+HEIGHT));
        SDL_RenderDrawLine(gRenderer, startX, startY, (startX+WIDTH), startY);
        SDL_RenderDrawLine(gRenderer, (startX+WIDTH), startY, (startX+WIDTH), (startY+HEIGHT));
    }
    
    void drawG(int startX, int startY)
    {
        //Draw g
        SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderDrawLine(gRenderer, startX, (startY+5), (startX+WIDTH), (startY+5));
        SDL_RenderDrawLine(gRenderer, startX, (startY+5), startX, (startY+HEIGHT));
        SDL_RenderDrawLine(gRenderer, startX, (startY+HEIGHT), (startX+WIDTH), (startY+HEIGHT));
        SDL_RenderDrawLine(gRenderer, startX, (startY+(2*HEIGHT)), (startX+WIDTH), (startY+(2*HEIGHT)));
        SDL_RenderDrawLine(gRenderer, (startX+WIDTH), startY, (startX+WIDTH), (startY+(2*HEIGHT)));
    }
    
    void drawF(int startX, int startY)
    {
        //Draw f
        SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderDrawLine(gRenderer, (startX+5), (startY-HEIGHT), (startX+5), (startY+HEIGHT));
        SDL_RenderDrawLine(gRenderer, (startX+WIDTH), (startY-HEIGHT), (startX+WIDTH), (startY-15));
        SDL_RenderDrawLine(gRenderer, startX, startY, (startX+15), startY);
        SDL_RenderDrawLine(gRenderer, (startX+5), (startY-HEIGHT), (startX+WIDTH), (startY-HEIGHT));
    }
    
    void drawU(int startX, int startY)
    {
        //Draw u
        SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderDrawLine(gRenderer, startX, startY, startX, (startY+20));
        SDL_RenderDrawLine(gRenderer, (startX+WIDTH), startY, (startX+WIDTH), (startY+HEIGHT));
        SDL_RenderDrawLine(gRenderer, startX, (startY+20), (startX+WIDTH), (startY+20));
    }
    
    void drawC(int startX, int startY)
    {
        //Draw c
        SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderDrawLine(gRenderer, startX, startY, startX, (startY+HEIGHT));
        SDL_RenderDrawLine(gRenderer, startX, startY, (startX+WIDTH), startY);
        SDL_RenderDrawLine(gRenderer, startX, (startY+HEIGHT), (startX+WIDTH), (startY+HEIGHT));
    }
    
    void drawK(int startX, int startY)
    {
        //Draw k
        SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderDrawLine(gRenderer, startX, (startY-15), startX, (startY+HEIGHT));
        SDL_RenderDrawLine(gRenderer, startX, (startY+10), (startX+WIDTH), startY);
        SDL_RenderDrawLine(gRenderer, startX, (startY+10), (startX+WIDTH), (startY+HEIGHT));
    }
    
    void drawS(int startX, int startY)
    {
        //Draw s
        SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderDrawLine(gRenderer, startX, startY, startX, (startY+12));
        SDL_RenderDrawLine(gRenderer, (startX+WIDTH), (startY+12), (startX+WIDTH), (startY+HEIGHT));
        SDL_RenderDrawLine(gRenderer, startX, startY, (startX+WIDTH), startY);
        SDL_RenderDrawLine(gRenderer, startX, (startY+12), (startX+WIDTH), (startY+12));
        SDL_RenderDrawLine(gRenderer, startX, (startY+HEIGHT), (startX+WIDTH), (startY+HEIGHT));
    }
    
    void drawH(int startX, int startY)
    {
        //Draw h
        SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderDrawLine(gRenderer, startX, (startY-15), startX, (startY+HEIGHT));
        SDL_RenderDrawLine(gRenderer, startX, (startY+5), (startX+WIDTH), (startY+5));
        SDL_RenderDrawLine(gRenderer, (startX+WIDTH), (startY+5), (startX+WIDTH), (startY+HEIGHT));
    }
    
    void drawI(int startX, int startY)
    {
        //Draw i
        SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderDrawLine(gRenderer, (startX+(WIDTH/2)), (startY+5), (startX+(WIDTH/2)), (startY+HEIGHT));
        SDL_RenderDrawLine(gRenderer, (startX+(WIDTH/2)), (startY-5), (startX+(WIDTH/2)), (startY-3));
    }
    
    void drawT(int startX, int startY)
    {
        //Draw t
        SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderDrawLine(gRenderer, startX, (startY+5), (startX+WIDTH), (startY+5));
        SDL_RenderDrawLine(gRenderer, (startX+(WIDTH/2)), (startY-5), (startX+(WIDTH/2)), (startY+HEIGHT));
    }
    
    void drawD(int startX, int startY)
    {
        //Draw d
        SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderDrawLine(gRenderer, (startX+WIDTH), (startY-HEIGHT), (startX+WIDTH), (startY+HEIGHT));
        SDL_RenderDrawLine(gRenderer, startX, startY, (startX+WIDTH), startY);
        SDL_RenderDrawLine(gRenderer, startX, startY, startX, (startY+HEIGHT));
        SDL_RenderDrawLine(gRenderer, startX, (startY+HEIGHT), (startX+WIDTH), (startY+HEIGHT));
    }
    
    void drawJ(int startX, int startY)
    {
        //Draw j
        SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderDrawLine(gRenderer, startX, (startY+(2*HEIGHT)), (startX+WIDTH), (startY+(2*HEIGHT)));
        SDL_RenderDrawLine(gRenderer, (startX+WIDTH), startY, (startX+WIDTH), (startY+(2*HEIGHT)));
        SDL_RenderDrawLine(gRenderer, (startX+WIDTH), (startY-8), (startX+WIDTH), (startY-5));
        SDL_RenderDrawLine(gRenderer, startX, (startY+((2*HEIGHT)-10)), startX, (startY+(2*HEIGHT)));
    }
    
    void drawL(int startX, int startY)
    {
        //Draw l
        SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderDrawLine(gRenderer, (startX+(WIDTH/2)), (startY-HEIGHT), (startX+(WIDTH/2)), (startY+HEIGHT));
    }
    
    void drawP(int startX, int startY)
    {
        //Draw p
        SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderDrawLine(gRenderer, startX, startY, startX, (startY+(2*HEIGHT)));
        SDL_RenderDrawLine(gRenderer, startX, startY, (startX+WIDTH), startY);
        SDL_RenderDrawLine(gRenderer, startX, (startY+HEIGHT), (startX+WIDTH), (startY+HEIGHT));
        SDL_RenderDrawLine(gRenderer, (startX+WIDTH), startY, (startX+WIDTH), (startY+HEIGHT));
    }
    
    void drawQ(int startX, int startY)
    {
        //Draw q
        SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderDrawLine(gRenderer, (startX+WIDTH), startY, (startX+WIDTH), (startY+(2*HEIGHT)));
        SDL_RenderDrawLine(gRenderer, startX, startY, (startX+WIDTH), startY);
        SDL_RenderDrawLine(gRenderer, startX, (startY+HEIGHT), (startX+WIDTH), (startY+HEIGHT));
        SDL_RenderDrawLine(gRenderer, startX, startY, startX, (startY+HEIGHT));
        SDL_RenderDrawLine(gRenderer, (startX+WIDTH), (startY+(2*HEIGHT)), (startX+WIDTH+5), (startY+(2*HEIGHT)));
        SDL_RenderDrawLine(gRenderer, (startX+WIDTH+5), ((startY+(2*HEIGHT))-5), (startX+WIDTH+5), (startY+(2*HEIGHT)));
    }
    
    void drawV(int startX, int startY)
    {
        //Draw v
        SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderDrawLine(gRenderer, startX, startY, (startX+(WIDTH/2)), (startY+HEIGHT));
        SDL_RenderDrawLine(gRenderer, (startX+(WIDTH/2)), (startY+HEIGHT), (startX+WIDTH), startY);
    }
    
    void drawW(int startX, int startY)
    {
        //Draw w
        SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderDrawLine(gRenderer, startX, startY, startX, (startY+HEIGHT));
        SDL_RenderDrawLine(gRenderer, (startX+(WIDTH/2)), (startY+10), (startX+(WIDTH/2)), (startY+HEIGHT));
        SDL_RenderDrawLine(gRenderer, (startX+WIDTH), startY, (startX+WIDTH), (startY+HEIGHT));
        SDL_RenderDrawLine(gRenderer, startX, (startY+HEIGHT), (startX+WIDTH), (startY+HEIGHT));
    }
    
    void drawX(int startX, int startY)
    {
        //Draw x
        SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderDrawLine(gRenderer, startX, startY, (startX+WIDTH), (startY+HEIGHT));
        SDL_RenderDrawLine(gRenderer, startX, (startY+HEIGHT), (startX+WIDTH), startY);
    }
    
    void drawY(int startX, int startY)
    {
        //Draw y
        SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderDrawLine(gRenderer, (startX+WIDTH), startY, (startX+WIDTH), (startY+(2*HEIGHT)));
        SDL_RenderDrawLine(gRenderer, startX, (startY+HEIGHT), (startX+WIDTH), (startY+HEIGHT));
        SDL_RenderDrawLine(gRenderer, startX, startY, startX, (startY+HEIGHT));
        SDL_RenderDrawLine(gRenderer, startX, (startY+(2*HEIGHT)), (startX+WIDTH), (startY+(2*HEIGHT)));
    }
    
    void drawZ(int startX,  int startY)
    {
        //Draw z
        SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderDrawLine(gRenderer, startX, startY, (startX+WIDTH), startY);
        SDL_RenderDrawLine(gRenderer, startX, (startY+HEIGHT), (startX+WIDTH), startY);
        SDL_RenderDrawLine(gRenderer, startX, (startY+HEIGHT), (startX+WIDTH), (startY+HEIGHT));
    }
    
    void draw_(int startX, int startY)
    {
        //Draw _
        SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderDrawLine(gRenderer, startX, (startY+HEIGHT), (startX+WIDTH), (startY+HEIGHT));
    }
    
    void drawExclamation(int startX,  int startY)
    {
        //Draw !
        SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderDrawLine(gRenderer, (startX+(WIDTH/2)), (startY-HEIGHT), (startX+(WIDTH/2)), (startY+10));
        SDL_RenderDrawLine(gRenderer, (startX+(WIDTH/2)), ((startY+HEIGHT)-3), (startX+(WIDTH/2)), (startY+HEIGHT));
    }
    
    void drawBeginBracket(int startX, int startY)
    {
        //Draw [
        SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderDrawLine(gRenderer, startX, (startY-HEIGHT), startX, (startY+HEIGHT));
        SDL_RenderDrawLine(gRenderer, startX, (startY-HEIGHT), (startX+(WIDTH/2)), (startY-HEIGHT));
        SDL_RenderDrawLine(gRenderer, startX, (startY+HEIGHT), (startX+(WIDTH/2)), (startY+HEIGHT));
    }
    
    void drawEndBracket(int startX, int startY)
    {
        //Draw ]
        SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderDrawLine(gRenderer, (startX+WIDTH), (startY-HEIGHT), (startX+WIDTH), (startY+HEIGHT));
        SDL_RenderDrawLine(gRenderer, (startX+(WIDTH/2)), (startY-HEIGHT), (startX+WIDTH), (startY-HEIGHT));
        SDL_RenderDrawLine(gRenderer, (startX+(WIDTH/2)), (startY+HEIGHT), (startX+WIDTH), (startY+HEIGHT));
    }
    
    void draw1(int startX,  int startY)
    {
        //Draw 1
        SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderDrawLine(gRenderer, startX, (startY-15), (startX+(WIDTH/2)), (startY-HEIGHT));
        SDL_RenderDrawLine(gRenderer, (startX+(WIDTH/2)), (startY-HEIGHT), (startX+(WIDTH/2)), (startY+HEIGHT));
        SDL_RenderDrawLine(gRenderer, startX, (startY+HEIGHT), (startX+WIDTH), (startY+HEIGHT));
    }
    
    void draw2(int startX, int startY)
    {
        //Draw 2
        SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderDrawLine(gRenderer, (startX+WIDTH), (startY-HEIGHT), (startX+WIDTH), startY);
        SDL_RenderDrawLine(gRenderer, startX, startY, startX, (startY+HEIGHT));
        SDL_RenderDrawLine(gRenderer, startX, (startY-HEIGHT), (startX+WIDTH), (startY-HEIGHT));
        SDL_RenderDrawLine(gRenderer, startX, startY, (startX+WIDTH), startY);
        SDL_RenderDrawLine(gRenderer, startX, (startY+HEIGHT), (startX+WIDTH), (startY+HEIGHT));
    }
    
    void draw3(int startX, int startY)
    {
        //Draw 3
        SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderDrawLine(gRenderer, (startX+WIDTH), (startY-HEIGHT), (startX+WIDTH), (startY+HEIGHT));
        SDL_RenderDrawLine(gRenderer, startX, (startY-HEIGHT), (startX+WIDTH), (startY-HEIGHT));
        SDL_RenderDrawLine(gRenderer, startX, startY, (startX+WIDTH), startY);
        SDL_RenderDrawLine(gRenderer, startX, (startY+HEIGHT), (startX+WIDTH), (startY+HEIGHT));
    }

    
    
public:
    renderLetters(string w = "", int startX = 0, int startY = 0, SDL_Renderer* g = NULL)
    {
        gRenderer = g;
        word = w;
        wordLength = word.length();
        int beginRenderX, beginRenderY;
        if (startX == 0)
        {
            beginRenderX = ((920 - ((wordLength*WIDTH)+((wordLength-1)*SPACE_BETWEEN_LETTERS))) / 2);
        }
        else
        {
            beginRenderX = startX;
        }
        beginRenderY = startY;
        char *c = const_cast<char*>(word.c_str());
        while (*c != '\0')
        {
            switch (*c)
            {
                case 'a':
                    drawA(beginRenderX, beginRenderY);
                    break;
                case 'b':
                    drawB(beginRenderX, beginRenderY);
                    break;
                case 'c':
                    drawC(beginRenderX, beginRenderY);
                    break;
                case 'd':
                    drawD(beginRenderX, beginRenderY);
                    break;
                case 'e':
                    drawE(beginRenderX, beginRenderY);
                    break;
                case 'f':
                    drawF(beginRenderX, beginRenderY);
                    break;
                case 'g':
                    drawG(beginRenderX, beginRenderY);
                    break;
                case 'h':
                    drawH(beginRenderX, beginRenderY);
                    break;
                case 'i':
                    drawI(beginRenderX, beginRenderY);
                    break;
                case 'j':
                    drawJ(beginRenderX, beginRenderY);
                    break;
                case 'k':
                    drawK(beginRenderX, beginRenderY);
                    break;
                case 'l':
                    drawL(beginRenderX, beginRenderY);
                    break;
                case 'm':
                    drawM(beginRenderX, beginRenderY);
                    break;
                case 'n':
                    drawN(beginRenderX, beginRenderY);
                    break;
                case 'o':
                    drawO(beginRenderX, beginRenderY);
                    break;
                case 'p':
                    drawP(beginRenderX, beginRenderY);
                    break;
                case 'q':
                    drawQ(beginRenderX, beginRenderY);
                    break;
                case 'r':
                    drawR(beginRenderX, beginRenderY);
                    break;
                case 's':
                    drawS(beginRenderX, beginRenderY);
                    break;
                case 't':
                    drawT(beginRenderX, beginRenderY);
                    break;
                case 'u':
                    drawU(beginRenderX, beginRenderY);
                    break;
                case 'v':
                    drawV(beginRenderX, beginRenderY);
                    break;
                case 'w':
                    drawW(beginRenderX, beginRenderY);
                    break;
                case 'x':
                    drawX(beginRenderX, beginRenderY);
                    break;
                case 'y':
                    drawY(beginRenderX, beginRenderY);
                    break;
                case 'z':
                    drawZ(beginRenderX, beginRenderY);
                    break;
                case '_':
                    draw_(beginRenderX, beginRenderY);
                    break;
                case '!':
                    drawExclamation(beginRenderX, beginRenderY);
                    break;
                case '(':
                    drawBeginBracket(beginRenderX, beginRenderY);
                    break;
                case ')':
                    drawEndBracket(beginRenderX, beginRenderY);
                    break;
                case '1':
                    draw1(beginRenderX, beginRenderY);
                    break;
                case '2':
                    draw2(beginRenderX, beginRenderY);
                    break;
                case '3':
                    draw3(beginRenderX, beginRenderY);
                    break;
                default:
                    break;
            }
            //SDL_RenderPresent(gRenderer);
            c++;
            beginRenderX = (beginRenderX + WIDTH) + SPACE_BETWEEN_LETTERS;
        }
        //SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    }
    
    
};

#endif /* renderLetters_h */
