/*
 * SDL_Plotter.h
 *
 *  Created on: Jun 13, 2016
 *      Author: booth
 */

#ifndef SDL_PLOTTER_H_
#define SDL_PLOTTER_H_

//OSX Library
#include <SDL2/SDL.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <SDL2/SDL_thread.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_image/SDL_image.h>

//Windows Library
//#include <SDL2/SDL.h>
//#include <SDL2/SDL_mixer.h>

#include <string.h>
#include <iostream>
#include <string>
#include <string.h>
#include <map>
using namespace std;

const char UP_ARROW    = 1;
const char DOWN_ARROW  = 2;
const char LEFT_ARROW  = 3;
const char RIGHT_ARROW = 4;
const int RED_SHIFT   = 65536;
const int GREEN_SHIFT = 256;
const int BLUE_SHIFT  = 1;
const int ALPHA_SHIFT = 16777216;
const int WHITE = 255;
const int MAX_THREAD = 100;

#define MUS_PATH "scratch.wav"

//sample threaded sound function
static int Sound(void *data);

struct param{
	bool play;
	bool running;
	bool pause;
	SDL_Thread*  threadID;
	SDL_cond *cond;
	SDL_mutex *mut;
	string name;

	param(){
		play = false;
		running = false;
		pause = false;
	}
};

//#include <SDL2/SDL.h>
//#include <SDL2_image/SDL_image.h>
//#include <SDL2_ttf/SDL_ttf.h>
#include <stdio.h>
//#include <string>
#include <cmath>

using namespace std;

//Screen dimension constants
const int SCREEN_WIDTH = 920;
const int SCREEN_HEIGHT = 640;

//Texture wrapper class
class LTexture
{
public:
    //Initializes variables
    LTexture();
    
    //Deallocates memory
    ~LTexture();
    
    //Loads image at specified path
    bool loadFromFile( std::string path );
    
    //Creates image from font string
    bool loadFromRenderedText( std::string textureText, SDL_Color textColor );
    
    //Deallocates texture
    void free();
    
    //Set color modulation
    void setColor( Uint8 red, Uint8 green, Uint8 blue );
    
    //Set blending
    void setBlendMode( SDL_BlendMode blending );
    
    //Set alpha modulation
    void setAlpha( Uint8 alpha );
    
    //Renders texture at given point
    void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );
    
    //Gets image dimensions
    int getWidth();
    int getHeight();
    
    bool loadMedia(string);
    
    char getKey();
    
private:
    //The actual hardware texture
    SDL_Texture* mTexture;
    
    const Uint8* currentKeyStates;
    
    //Image dimensions
    int mWidth;
    int mHeight;
};

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Globally used font
TTF_Font *gFont = NULL;

//Rendered texture
LTexture gTextTexture;
//LTexture incorrectLetters;


LTexture::LTexture()
{
    //Initialize
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

LTexture::~LTexture()
{
    //Deallocate
    free();
}

bool LTexture::loadFromFile( std::string path )
{
    //Get rid of preexisting texture
    free();
    
    //The final texture
    SDL_Texture* newTexture = NULL;
    
    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        //Color key image
        SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );
        
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }
        else
        {
            //Get image dimensions
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }
        
        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }
    
    //Return success
    mTexture = newTexture;
    return mTexture != NULL;
}

bool LTexture::loadFromRenderedText( std::string textureText, SDL_Color textColor )
{
    //Get rid of preexisting texture
    free();
    
    //Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Blended( gFont, textureText.c_str(), textColor );
    if( textSurface == NULL )
    {
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
        if( mTexture == NULL )
        {
            printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        }
        else
        {
            //Get image dimensions
            mWidth = textSurface->w;
            mHeight = textSurface->h;
        }
        
        //Get rid of old surface
        SDL_FreeSurface( textSurface );
    }
    
    //Return success
    return mTexture != NULL;
}

void LTexture::free()
{
    //Free texture if it exists
    if( mTexture != NULL )
    {
        SDL_DestroyTexture( mTexture );
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
    //Modulate texture rgb
    SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void LTexture::setBlendMode( SDL_BlendMode blending )
{
    //Set blending function
    SDL_SetTextureBlendMode( mTexture, blending );
}

void LTexture::setAlpha( Uint8 alpha )
{
    //Modulate texture alpha
    SDL_SetTextureAlphaMod( mTexture, alpha );
}

void LTexture::render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
    //Set rendering space and render to screen
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };
    
    //Set clip rendering dimensions
    if( clip != NULL )
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    
    //Render to screen
    SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, angle, center, flip );
}

int LTexture::getWidth()
{
    return mWidth;
}

int LTexture::getHeight()
{
    return mHeight;
}

bool init()
{
    //Initialization flag
    bool success = true;
    
    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        //Set texture filtering to linear
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        {
            printf( "Warning: Linear texture filtering not enabled!" );
        }
        
        //Create window
        gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            //Create vsynced renderer for window
            gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
            if( gRenderer == NULL )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            else
            {
                //Initialize renderer color
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                
                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                    success = false;
                }
                
                //Initialize SDL_ttf
                if( TTF_Init() == -1 )
                {
                    printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
                    success = false;
                }
            }
        }
    }
    
    return success;
}

bool LTexture::loadMedia(string tempString)
{
    //Loading success flag
    bool success = true;
    
    //Open the font
    gFont = TTF_OpenFont( "precious.ttf", 28 );
    if( gFont == NULL )
    {
        printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }
    else
    {
        //Render text
        SDL_Color textColor = { 0x00, 0x00, 0x00 };
        if( !loadFromRenderedText( tempString, textColor ) )
        {
            printf( "Failed to render text texture!\n" );
            success = false;
        }
    }
    
    return success;
}

char LTexture::getKey(){
    
    char key = '\0';
    
    
    currentKeyStates = SDL_GetKeyboardState( NULL );
    if(currentKeyStates[SDL_SCANCODE_A]) key = 'A';
    if(currentKeyStates[SDL_SCANCODE_B]) key = 'B';
    if(currentKeyStates[SDL_SCANCODE_C]) key = 'C';
    if(currentKeyStates[SDL_SCANCODE_D]) key = 'D';
    if(currentKeyStates[SDL_SCANCODE_E]) key = 'E';
    if(currentKeyStates[SDL_SCANCODE_F]) key = 'F';
    if(currentKeyStates[SDL_SCANCODE_G]) key = 'G';
    if(currentKeyStates[SDL_SCANCODE_H]) key = 'H';
    if(currentKeyStates[SDL_SCANCODE_I]) key = 'I';
    if(currentKeyStates[SDL_SCANCODE_J]) key = 'J';
    if(currentKeyStates[SDL_SCANCODE_K]) key = 'K';
    if(currentKeyStates[SDL_SCANCODE_L]) key = 'L';
    if(currentKeyStates[SDL_SCANCODE_M]) key = 'M';
    if(currentKeyStates[SDL_SCANCODE_N]) key = 'N';
    if(currentKeyStates[SDL_SCANCODE_O]) key = 'O';
    if(currentKeyStates[SDL_SCANCODE_P]) key = 'P';
    if(currentKeyStates[SDL_SCANCODE_Q]) key = 'Q';
    if(currentKeyStates[SDL_SCANCODE_R]) key = 'R';
    if(currentKeyStates[SDL_SCANCODE_S]) key = 'S';
    if(currentKeyStates[SDL_SCANCODE_T]) key = 'T';
    if(currentKeyStates[SDL_SCANCODE_U]) key = 'U';
    if(currentKeyStates[SDL_SCANCODE_V]) key = 'V';
    if(currentKeyStates[SDL_SCANCODE_W]) key = 'W';
    if(currentKeyStates[SDL_SCANCODE_X]) key = 'X';
    if(currentKeyStates[SDL_SCANCODE_Y]) key = 'Y';
    if(currentKeyStates[SDL_SCANCODE_Z]) key = 'Z';
    if(currentKeyStates[SDL_SCANCODE_1]) key = '1';
    if(currentKeyStates[SDL_SCANCODE_2]) key = '2';
    if(currentKeyStates[SDL_SCANCODE_3]) key = '3';
    if(currentKeyStates[SDL_SCANCODE_4]) key = '4';
    if(currentKeyStates[SDL_SCANCODE_5]) key = '5';
    if(currentKeyStates[SDL_SCANCODE_6]) key = '6';
    if(currentKeyStates[SDL_SCANCODE_7]) key = '7';
    if(currentKeyStates[SDL_SCANCODE_8]) key = '8';
    if(currentKeyStates[SDL_SCANCODE_9]) key = '9';
    if(currentKeyStates[SDL_SCANCODE_0]) key = '0';
    if(currentKeyStates[SDL_SCANCODE_SPACE]) key = ' ';
    //if(currentKeyStates[SDL_SCANCODE_DOWN])  key = DOWN_ARROW;
    //if(currentKeyStates[SDL_SCANCODE_UP])    key = UP_ARROW;
    //if(currentKeyStates[SDL_SCANCODE_LEFT])  key = LEFT_ARROW;
    //if(currentKeyStates[SDL_SCANCODE_RIGHT]) key = RIGHT_ARROW;
    //if(currentKeyStates[SDL_SCANCODE_RETURN]) key = SDL_SCANCODE_RETURN;
    //if(currentKeyStates[SDL_SCANCODE_ESCAPE]) quit = true;
    
    return key;
}

void close()
{
    //Free loaded images
    gTextTexture.free();
    //incorrectLetters.free();
    
    //Free global font
    TTF_CloseFont( gFont );
    gFont = NULL;
    
    //Destroy window
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;
    
    //Quit SDL subsystems
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

class SDL_Plotter{
private:
	SDL_Texture * texture;
	SDL_Renderer * renderer;
	SDL_Window * window;

	bool leftMouseButtonDown;
    Uint32 * pixels;
    const Uint8* currentKeyStates;

    int row, col;
    bool quit;
    SDL_Event event;

    //Sound Stuff
    bool SOUND;
    int soundCount;
    map<string, param> soundMap;

public:



    SDL_Plotter(int r=480, int c=640, bool WITH_SOUND = true){
    	row = r;
    	col = c;
    	leftMouseButtonDown = false;
    	quit = false;
    	SOUND = WITH_SOUND;

    	SDL_Init(SDL_INIT_AUDIO);

        window   = SDL_CreateWindow("SDL2 Pixel Drawing",
        		                     SDL_WINDOWPOS_UNDEFINED,
        		                     SDL_WINDOWPOS_UNDEFINED, col, row, 0);

        renderer = SDL_CreateRenderer(window, -1, 0);

        texture  = SDL_CreateTexture(renderer,
        		                     SDL_PIXELFORMAT_ARGB8888,
        		                     SDL_TEXTUREACCESS_STATIC, col, row);

        pixels   = new Uint32[col * row];

        memset(pixels, WHITE, col * row * sizeof(Uint32));

        //SOUND Thread Pool
        Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 );
        soundCount = 0;

      }


    ~SDL_Plotter(){
        delete[] pixels;
        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();

    }

    void update(){
        SDL_UpdateTexture(texture, NULL, pixels, col * sizeof(Uint32));
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    bool getQuit(){
    	return quit;
    }

    bool kbhit(){
    	bool flag = false;
    	if(SDL_PollEvent(&event)){
    		if(event.type == SDL_KEYDOWN){
    			flag = true;
    		}
    		if( event.type == SDL_QUIT )
			{
				quit = true;
			}
    	}
    	return flag;
    }

    char getKey(){

    	char key = '\0';


		currentKeyStates = SDL_GetKeyboardState( NULL );
		if(currentKeyStates[SDL_SCANCODE_A]) key = 'A';
		if(currentKeyStates[SDL_SCANCODE_B]) key = 'B';
		if(currentKeyStates[SDL_SCANCODE_C]) key = 'C';
		if(currentKeyStates[SDL_SCANCODE_D]) key = 'D';
		if(currentKeyStates[SDL_SCANCODE_E]) key = 'E';
		if(currentKeyStates[SDL_SCANCODE_F]) key = 'F';
		if(currentKeyStates[SDL_SCANCODE_G]) key = 'G';
		if(currentKeyStates[SDL_SCANCODE_H]) key = 'H';
		if(currentKeyStates[SDL_SCANCODE_I]) key = 'I';
		if(currentKeyStates[SDL_SCANCODE_J]) key = 'J';
		if(currentKeyStates[SDL_SCANCODE_K]) key = 'K';
		if(currentKeyStates[SDL_SCANCODE_L]) key = 'L';
		if(currentKeyStates[SDL_SCANCODE_M]) key = 'M';
		if(currentKeyStates[SDL_SCANCODE_N]) key = 'N';
		if(currentKeyStates[SDL_SCANCODE_O]) key = 'O';
		if(currentKeyStates[SDL_SCANCODE_P]) key = 'P';
		if(currentKeyStates[SDL_SCANCODE_Q]) key = 'Q';
		if(currentKeyStates[SDL_SCANCODE_R]) key = 'R';
		if(currentKeyStates[SDL_SCANCODE_S]) key = 'S';
		if(currentKeyStates[SDL_SCANCODE_T]) key = 'T';
		if(currentKeyStates[SDL_SCANCODE_U]) key = 'U';
		if(currentKeyStates[SDL_SCANCODE_V]) key = 'V';
		if(currentKeyStates[SDL_SCANCODE_W]) key = 'W';
		if(currentKeyStates[SDL_SCANCODE_X]) key = 'X';
		if(currentKeyStates[SDL_SCANCODE_Y]) key = 'Y';
		if(currentKeyStates[SDL_SCANCODE_Z]) key = 'Z';
		if(currentKeyStates[SDL_SCANCODE_1]) key = '1';
		if(currentKeyStates[SDL_SCANCODE_2]) key = '2';
		if(currentKeyStates[SDL_SCANCODE_3]) key = '3';
		if(currentKeyStates[SDL_SCANCODE_4]) key = '4';
		if(currentKeyStates[SDL_SCANCODE_5]) key = '5';
		if(currentKeyStates[SDL_SCANCODE_6]) key = '6';
		if(currentKeyStates[SDL_SCANCODE_7]) key = '7';
		if(currentKeyStates[SDL_SCANCODE_8]) key = '8';
		if(currentKeyStates[SDL_SCANCODE_9]) key = '9';
		if(currentKeyStates[SDL_SCANCODE_0]) key = '0';
		if(currentKeyStates[SDL_SCANCODE_SPACE]) key = ' ';
		if(currentKeyStates[SDL_SCANCODE_DOWN])  key = DOWN_ARROW;
		if(currentKeyStates[SDL_SCANCODE_UP])    key = UP_ARROW;
		if(currentKeyStates[SDL_SCANCODE_LEFT])  key = LEFT_ARROW;
		if(currentKeyStates[SDL_SCANCODE_RIGHT]) key = RIGHT_ARROW;
		if(currentKeyStates[SDL_SCANCODE_RETURN]) key = SDL_SCANCODE_RETURN;
		if(currentKeyStates[SDL_SCANCODE_ESCAPE]) quit = true;

    	return key;
    }

    void plotPixel(int x, int y, int r, int g, int b){
    	pixels[y * col + x] = RED_SHIFT*r + GREEN_SHIFT*g + BLUE_SHIFT*b;
    }

    void clear(){
    	memset(pixels, WHITE, col * row * sizeof(Uint32));
    }

    int getRow(){
    	return row;
    }

    int getCol(){
    	return col;
    }

    void initSound(string sound){
    	//int  *threadReturnValue;

		if(!soundMap[sound].running){
				param* p = &soundMap[sound];
				p->name = sound;
				p->cond = SDL_CreateCond();
				p->mut = SDL_CreateMutex();

				p->threadID = SDL_CreateThread( Sound, sound.c_str(), (void*)p );
				//p->threadID = SDL_CreateThread( Sound, "SoundThread", (void*)p );
				//SDL_DetachThread(p->threadID);
		}
    }

    void setQuit(bool flag){
    	this->quit = flag;
    }

    void playSound(string sound){
    	if(soundMap[sound].running){
    		SDL_CondSignal(soundMap[sound].cond);
    	}
    }

    void quitSound(string sound){
    	soundMap[sound].running = false;
    	SDL_CondSignal(soundMap[sound].cond);
    }

    void Sleep(int ms){
    	SDL_Delay(ms);
    }
};



//Threaded Function

static int Sound(void *data){
	param *p = (param*)data;
	p->running = true;
	Mix_Chunk *gScratch = NULL;
	gScratch = Mix_LoadWAV( p->name.c_str() );


	while(p->running){
		SDL_mutexP( p->mut );
		  SDL_CondWait(p->cond, p->mut);
		  Mix_PlayChannel( -1, gScratch, 0 );
		  p->play = false;
		SDL_mutexV(p->mut);
	}

	Mix_FreeChunk( gScratch );
	p->running = false;
	return 0;
}



#endif /* SDL_PLOTTER_H_ */


//Draw b
SDL_SetRenderDrawColor(gRenderer, 0x80, 0xFF, 0xFF, 0xFF);
SDL_RenderDrawLine(gRenderer, 500, 300, 500, 350);
SDL_RenderDrawLine(gRenderer, 520, 325, 520, 350);
SDL_RenderDrawLine(gRenderer, 500, 325, 520, 325);
SDL_RenderDrawLine(gRenderer, 500, 350, 520, 350);

//Draw o
SDL_SetRenderDrawColor(gRenderer, 0x80, 0xFF, 0xFF, 0xFF);
SDL_RenderDrawLine(gRenderer, 530, 325, 530, 350);
SDL_RenderDrawLine(gRenderer, 530, 325, 550, 325);
SDL_RenderDrawLine(gRenderer, 550, 325, 550, 350);
SDL_RenderDrawLine(gRenderer, 530, 350, 550, 350);

//Draw o
SDL_SetRenderDrawColor(gRenderer, 0x80, 0xFF, 0xFF, 0xFF);
SDL_RenderDrawLine(gRenderer, 560, 325, 560, 350);
SDL_RenderDrawLine(gRenderer, 560, 325, 580, 325);
SDL_RenderDrawLine(gRenderer, 580, 325, 580, 350);
SDL_RenderDrawLine(gRenderer, 560, 350, 580, 350);

//Draw m
SDL_SetRenderDrawColor(gRenderer, 0x80, 0xFF, 0xFF, 0xFF);
SDL_RenderDrawLine(gRenderer, 590, 320, 590, 350);
SDL_RenderDrawLine(gRenderer, 590, 325, 610, 325);
SDL_RenderDrawLine(gRenderer, 600, 325, 600, 350);
SDL_RenderDrawLine(gRenderer, 610, 325, 610, 350);

//Draw e
SDL_SetRenderDrawColor(gRenderer, 0x80, 0xFF, 0xFF, 0xFF);
SDL_RenderDrawLine(gRenderer, 620, 325, 620, 350);
SDL_RenderDrawLine(gRenderer, 620, 325, 640, 325);
SDL_RenderDrawLine(gRenderer, 620, 335, 640, 335);
SDL_RenderDrawLine(gRenderer, 620, 350, 640, 350);
SDL_RenderDrawLine(gRenderer, 640, 325, 640, 335);

//Draw r
SDL_SetRenderDrawColor(gRenderer, 0x80, 0xFF, 0xFF, 0xFF);
SDL_RenderDrawLine(gRenderer, 650, 325, 670, 325);
SDL_RenderDrawLine(gRenderer, 650, 320, 650, 350);
SDL_RenderDrawLine(gRenderer, 670, 325, 670, 330);

//Draw a
SDL_SetRenderDrawColor(gRenderer, 0x80, 0xFF, 0xFF, 0xFF);
SDL_RenderDrawLine(gRenderer, 680, 330, 680, 347);
SDL_RenderDrawLine(gRenderer, 680, 325, 700, 325);
SDL_RenderDrawLine(gRenderer, 680, 330, 700, 330);
SDL_RenderDrawLine(gRenderer, 680, 347, 700, 347);
SDL_RenderDrawLine(gRenderer, 700, 325, 700, 350);

//Draw n
SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0xFF, 0xFF);
SDL_RenderDrawLine(gRenderer, 710, 320, 710, 350);
SDL_RenderDrawLine(gRenderer, 710, 325, 730, 325);
SDL_RenderDrawLine(gRenderer, 730, 325, 730, 350);

//Draw g
SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0x00, 0xFF);
SDL_RenderDrawLine(gRenderer, 740, 330, 760, 330);
SDL_RenderDrawLine(gRenderer, 740, 330, 740, 350);
SDL_RenderDrawLine(gRenderer, 740, 350, 760, 350);
SDL_RenderDrawLine(gRenderer, 740, 375, 760, 375);
SDL_RenderDrawLine(gRenderer, 760, 325, 760, 375);*/


 //Draw f
 SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0xFF, 0xFF);
 SDL_RenderDrawLine(gRenderer, 505, 300, 505, 350);
 SDL_RenderDrawLine(gRenderer, 520, 300, 520, 310);
 SDL_RenderDrawLine(gRenderer, 500, 325, 515, 325);
 SDL_RenderDrawLine(gRenderer, 505, 300, 520, 300);
 
 //Draw u
 SDL_SetRenderDrawColor(gRenderer, 0x80, 0xFF, 0xFF, 0xFF);
 SDL_RenderDrawLine(gRenderer, 530, 325, 530, 345);
 SDL_RenderDrawLine(gRenderer, 550, 325, 550, 350);
 SDL_RenderDrawLine(gRenderer, 530, 345, 550, 345);
 
 //Draw c
 SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
 SDL_RenderDrawLine(gRenderer, 560, 325, 560, 350);
 SDL_RenderDrawLine(gRenderer, 560, 325, 580, 325);
 SDL_RenderDrawLine(gRenderer, 560, 350, 580, 350);
 
 //Draw k
 SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
 SDL_RenderDrawLine(gRenderer, 590, 310, 590, 350);
 SDL_RenderDrawLine(gRenderer, 590, 335, 610, 325);
 SDL_RenderDrawLine(gRenderer, 590, 335, 610, 350);

 //Draw s
 SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
 SDL_RenderDrawLine(gRenderer, 500, 325, 500, 337);
 SDL_RenderDrawLine(gRenderer, 520, 337, 520, 350);
 SDL_RenderDrawLine(gRenderer, 500, 325, 520, 325);
 SDL_RenderDrawLine(gRenderer, 500, 337, 520, 337);
 SDL_RenderDrawLine(gRenderer, 500, 350, 520, 350);
 
 //Draw h
 SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
 SDL_RenderDrawLine(gRenderer, 530, 310, 530, 350);
 SDL_RenderDrawLine(gRenderer, 530, 330, 550, 330);
 SDL_RenderDrawLine(gRenderer, 550, 330, 550, 350);
 
 //Draw i
 SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
 SDL_RenderDrawLine(gRenderer, 560, 330, 560, 350);
 SDL_RenderDrawLine(gRenderer, 560, 320, 560, 322);
 
 //Draw t
 SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
 SDL_RenderDrawLine(gRenderer, 570, 330, 590, 330);
 SDL_RenderDrawLine(gRenderer, 580, 320, 580, 350);

//Draw d
 SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
 SDL_RenderDrawLine(gRenderer, 520, 300, 520, 350);
 SDL_RenderDrawLine(gRenderer, 500, 325, 520, 325);
 SDL_RenderDrawLine(gRenderer, 500, 325, 500, 350);
 SDL_RenderDrawLine(gRenderer, 500, 350, 520, 350);

//Draw j
 SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
 SDL_RenderDrawLine(gRenderer, 500, 375, 520, 375);
 SDL_RenderDrawLine(gRenderer, 520, 325, 520, 375);
 SDL_RenderDrawLine(gRenderer, 520, 317, 520, 320);
 SDL_RenderDrawLine(gRenderer, 500, 365, 500, 375);

//Draw l
 SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
 SDL_RenderDrawLine(gRenderer, 500, 300, 500, 350);

//Draw p
 SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
 SDL_RenderDrawLine(gRenderer, 500, 325, 500, 375);
 SDL_RenderDrawLine(gRenderer, 500, 325, 520, 325);
 SDL_RenderDrawLine(gRenderer, 500, 350, 520, 350);
 SDL_RenderDrawLine(gRenderer, 520, 325, 520, 350);

//Draw q
 SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
 SDL_RenderDrawLine(gRenderer, 520, 325, 520, 375);
 SDL_RenderDrawLine(gRenderer, 500, 325, 520, 325);
 SDL_RenderDrawLine(gRenderer, 500, 350, 520, 350);
 SDL_RenderDrawLine(gRenderer, 500, 325, 500, 350);
 SDL_RenderDrawLine(gRenderer, 520, 375, 525, 375);

//Draw v
 SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
 SDL_RenderDrawLine(gRenderer, 500, 325, 510, 350);
 SDL_RenderDrawLine(gRenderer, 510, 350, 520, 325);

//Draw m
 SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
 SDL_RenderDrawLine(gRenderer, 500, 325, 500, 350);
 SDL_RenderDrawLine(gRenderer, 510, 335, 510, 350);
 SDL_RenderDrawLine(gRenderer, 520, 325, 520, 350);
 SDL_RenderDrawLine(gRenderer, 500, 350, 520, 350);

//Draw x
 SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
 SDL_RenderDrawLine(gRenderer, 500, 325, 520, 350);
 SDL_RenderDrawLine(gRenderer, 500, 350, 520, 325);

//Draw y
 SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
 SDL_RenderDrawLine(gRenderer, 520, 325, 520, 375);
 SDL_RenderDrawLine(gRenderer, 500, 350, 520, 350);
 SDL_RenderDrawLine(gRenderer, 500, 325, 500, 350);
 SDL_RenderDrawLine(gRenderer, 500, 375, 520, 375);

//Draw z
 SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
 SDL_RenderDrawLine(gRenderer, 500, 325, 520, 325);
 SDL_RenderDrawLine(gRenderer, 500, 350, 520, 325);
 SDL_RenderDrawLine(gRenderer, 500, 350, 520, 350);

//Draw _
 SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
 SDL_RenderDrawLine(gRenderer, 500, 350, 520, 350);

//Draw !
 SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
 SDL_RenderDrawLine(gRenderer, 510, 300, 510, 340);
 SDL_RenderDrawLine(gRenderer, 510, 347, 510, 350);

//Draw [
 SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
 SDL_RenderDrawLine(gRenderer, 500, 300, 500, 350);
 SDL_RenderDrawLine(gRenderer, 500, 300, 510, 300);
 SDL_RenderDrawLine(gRenderer, 500, 350, 510, 350);

//Draw ]
 SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
 SDL_RenderDrawLine(gRenderer, 520, 300, 520, 350);
 SDL_RenderDrawLine(gRenderer, 510, 300, 520, 300);
 SDL_RenderDrawLine(gRenderer, 510, 350, 520, 350);

//Draw 1
 SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
 SDL_RenderDrawLine(gRenderer, 500, 310, 510, 300);
 SDL_RenderDrawLine(gRenderer, 510, 300, 510, 350);
 SDL_RenderDrawLine(gRenderer, 500, 350, 520, 350);

//Draw 2
 SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
 SDL_RenderDrawLine(gRenderer, 520, 300, 520, 325);
 SDL_RenderDrawLine(gRenderer, 500, 325, 500, 350);
 SDL_RenderDrawLine(gRenderer, 500, 300, 520, 300);
 SDL_RenderDrawLine(gRenderer, 500, 325, 520, 325);
 SDL_RenderDrawLine(gRenderer, 500, 350, 520, 350);

//Draw 3
SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
SDL_RenderDrawLine(gRenderer, 520, 300, 520, 350);
SDL_RenderDrawLine(gRenderer, 500, 300, 520, 300);
SDL_RenderDrawLine(gRenderer, 500, 325, 520, 325);
SDL_RenderDrawLine(gRenderer, 500, 350, 520, 350);










