const int EYE_WIDTH = 10;
const int EYE_HEIGHT = 10;
const int EYE_SPACE = 5;

void drawFace(int startX, int startY) {
    SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);

    //draw left eye
    SDL_RenderDrawLine(gRenderer, startX, startY, (startX+EYE_WIDTH), (startY+EYE_HEIGHT));
    SDL_RenderDrawLine(gRenderer, startX, (startY+EYE_HEIGHT), (startX+EYE_WIDTH), startY);

    //draw right eye
    SDL_RenderDrawLine(gRenderer, (startX+EYE_WIDTH+EYE_SPACE), startY, (startX+(2*EYE_WIDTH)+EYE_SPACE), (startY+EYE_HEIGHT));
    SDL_RenderDrawLine(gRenderer, (startX+EYE_WIDTH+EYE_SPACE), (startY+EYE_HEIGHT), (startX+(2*EYE_WIDTH)+EYE_SPACE), startY);

    //draw mouth
    SDL_RenderDrawLine(gRenderer, startX, (startY+(2*EYE_HEIGHT)+EYE_SPACE), (startX+EYE_SPACE), (startY+(1.5*EYE_HEIGHT)+EYE_SPACE));
    SDL_RenderDrawLine(gRenderer, (startX+EYE_SPACE), (startY+(1.5*EYE_HEIGHT)+EYE_SPACE), (startX+EYE_WIDTH), (startY+EYE_HEIGHT+EYE_SPACE));
    SDL_RenderDrawLine(gRenderer, (startX+EYE_WIDTH), (startY+EYE_HEIGHT+EYE_SPACE), (startX+EYE_WIDTH+EYE_SPACE), (startY+EYE_HEIGHT+EYE_SPACE));
    SDL_RenderDrawLine(gRenderer, (startX+EYE_WIDTH+EYE_SPACE), (startY+EYE_HEIGHT+EYE_SPACE), (startX+EYE_WIDTH+(2*EYE_SPACE)),(startY+(1.5*EYE_HEIGHT)+EYE_SPACE));
    SDL_RenderDrawLine(gRenderer, (startX+EYE_WIDTH+(2*EYE_SPACE)), (startY+(1.5*EYE_HEIGHT)+EYE_SPACE), (startX+(2*EYE_WIDTH)+EYE_SPACE), (startY+(2*EYE_HEIGHT)+EYE_SPACE));
}



