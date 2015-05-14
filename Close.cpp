///////////////////////////////////////////////////////////////////////////////
//  Filename       : Close.h                                                 //
//                   Close.cpp                                               //
//  Date           : 2009/02/10                                              //
//  Author         : Bak Yeono (bakyeono@gmail.com)                          //
//  Description    : This global function prepares to close the program.     //
///////////////////////////////////////////////////////////////////////////////

#include "Close.h"

//////////////////
// Close        //
void Close( void )
//////////////////
{
    GraphicControl graphic;
    SoundControl sound;
    TextResource text;
    
    // close UTF-16 text resource
    text.DeleteUTF16();
    
    // close graphic and sound resource
    graphic.Close();
    sound.Close();
    
    // close SDL_mixer
    Mix_CloseAudio();
    
    // close SDL_ttf
    TTF_Quit();
    
    // close SDL
    SDL_Quit();
    
    return;
}

/* end of file */
