///////////////////////////////////////////////////////////////////////////////
//  Filename       : GamePlay.h                                              //
//                   GamePlay.cpp                                            //
//  Date           : 2009/02/10                                              //
//  Author         : Bak Yeono (bakyeono@gmail.com)                          //
//  Description    : This class controls the entire game play.               //
///////////////////////////////////////////////////////////////////////////////

#ifndef __GAMEPLAY_H__
#define __GAMEPLAY_H__

#include "SDLEvent.h"
#include "ProgramInfo.h"
#include "GraphicControl.h"
#include "SoundControl.h"
#include "GameDataControl.h"
#include "Timer.h"
#include <sstream>
#include "TextResource.h"

//////////////
class GamePlay
//////////////
{
    private:
        bool stateGameOver;
    
        int score;
        int lineCleared;
        int stage;
        int lineLeft;
    
    public:
        GamePlay(void);
        ~GamePlay(void);
    
        int Play( int startStage= 0 );
};

#endif

/* end of file */
