///////////////////////////////////////////////////////////////////////////////
//  Filename       : GraphicControl.h                                        //
//                   GraphicControl.cpp                                      //
//  Date           : 2009/02/08                                              //
//  Author         : Bak Yeono (bakyeono@gmail.com)                          //
//  Description    : This core class controls most graphic & unicode output  //
//                   by using libraries such as SDL, SDL_image and SLD_ttf.  //
///////////////////////////////////////////////////////////////////////////////

#ifndef __GRAPHICCONTROL_H__
#define __GRAPHICCONTROL_H__

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "ProgramInfo.h"
#include "LogWriter.h"
#include "Parser.h"

/////////////////////////////////
// Some Frequently Used Colors //
/////////////////////////////////
const SDL_Color colorBlack = { 0x0, 0x0, 0x0 };
const SDL_Color colorDGray = { 0x33, 0x33, 0x33 };
const SDL_Color colorLGray = { 0x99, 0x99, 0x99 };
const SDL_Color colorWhite = { 0xff, 0xff, 0xff };
const SDL_Color colorRed = { 0xff, 0x00, 0x00 };
const SDL_Color colorGreen = { 0x00, 0xff, 0x00 };
const SDL_Color colorBlue = { 0x00, 0x00, 0xff };

///////////////////////////////////
// Image IDs Used By Image Array //
///////////////////////////////////
enum _IMAGE_ARRAY_ID
{
    IMAGE_BACKGROUND0= 0,
    IMAGE_BACKGROUND1= 1,
    IMAGE_BACKGROUND2= 2,
    IMAGE_BACKGROUND3= 3,
    IMAGE_BACKGROUND4= 4,
    IMAGE_BACKGROUND5= 5,
    IMAGE_BACKGROUND6= 6,
    IMAGE_BACKGROUND7= 7,
    IMAGE_TILESET0= 8,
    IMAGE_GAMEBOARD0= 9,
    IMAGE_GAMEBOARD1= 10,
};

////////////////////
class GraphicControl
////////////////////
{
    private:
        static bool stateInitialized;
    
        static SDL_Surface* imageArray[IMAGE_ARRAY_LENGTH];
        static TTF_Font* fontArray[FONT_ARRAY_LENGTH];
    
        static SDL_Surface* screen;
    
        int LoadImageArray( void );
        int LoadFontArray( void );
        void UnloadImageArray ( void );
        void UnloadFontArray ( void );
    
        SDL_Surface* LoadImage( const char* filename );
    
    public:
        GraphicControl( void );
        ~GraphicControl( void );
    
        int Initialize( void );
        void Close( void );
    
        void PrintImage( int imageNumber, int x, int y );
        void PrintText( const char* text, int fontNumber, SDL_Color color, int x, int y );
        void PrintUTF8( const Uint8* text, int fontNumber, SDL_Color color, int x, int y );
        void PrintUNICODE( const wchar_t* text, int fontNumber, SDL_Color color, int x, int y );
        void Flip( void );
    
        void PrintTile( int tileNumber, int x, int y );
};

#endif
/* end of file */
