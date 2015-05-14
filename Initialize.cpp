///////////////////////////////////////////////////////////////////////////////
//  Filename       : Initialize.h                                            //
//                   Initialize.cpp                                          //
//  Date           : 2009/02/10                                              //
//  Author         : Bak Yeono (bakyeono@gmail.com)                          //
//  Description    : This global function initializes the program.           //
///////////////////////////////////////////////////////////////////////////////

#include "Initialize.h"

//////////////////////
// Initialize       //
int Initialize( void )
//////////////////////
{
    // Initialize the Program
    {
        GraphicControl graphic;
        SoundControl sound;
        TextResource text;
        
        // ready to write log file
        LogWriter log;
        
        // seed random seed value
        srand( (int) time( NULL ) );
        {
            int randinitializelooptime= rand() % 1000 + 100;
            for( int i= 0 ; i < randinitializelooptime ; i++ )
                rand();
        }
        
        // initialize SDL's everything
        if ( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
        {
            if( MAKELOG ) { log << "Error! Fail to initialize SDL\n"; }
            return -1;
        }
        
        // initialize SDL_ttf
        if ( TTF_Init() == -1 )
        {
            if( MAKELOG ) { log << "Error! Fail to initialize SDL_ttf\n"; }
            return -1;
        }
    
        // initialize SDL_mixer
        //if ( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
        if ( Mix_OpenAudio( 22050, AUDIO_S16SYS, 2, 1024 ) == -1 )
        {
            if( MAKELOG ) { log << "Error! Fail to initialize SDL_mixer\n"; }
            return -1;
        }
    
        // set the program's caption
        SDL_WM_SetCaption( PROGRAM_CAPTION, NULL );
    
        // prepare utf-16 text resource
        text.ReadyUTF16();
        
        // load image array and font array
        if ( graphic.Initialize() == -1 )
        {
            if( MAKELOG ) { log << "Error! Fail to initialize graphic class\n"; }
            return -1;
        }
    
        // load sound arrays
        if ( sound.Initialize() == -1 )
        {
            if( MAKELOG ) { log << "Error! Fail to initialize sound class\n"; }
            return -1;
        }
    }
    // Initialize Complete
    
    return 0;
}

/* end of file */
