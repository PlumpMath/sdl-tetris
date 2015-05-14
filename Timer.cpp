///////////////////////////////////////////////////////////////////////////////
//  Filename       : Timer.h                                                 //
//                   Timer.cpp                                               //
//  Date           : 2009/02/09                                              //
//  Author         : Bak Yeono (bakyeono@gmail.com)                          //
//  Description    : A simple timer class. It uses SDL Timer.                //
///////////////////////////////////////////////////////////////////////////////

#include "Timer.h"

//////////////////
// Constructor  //
Timer::Timer(void)
//////////////////
{
    startTicks= 0;
    pausedTicks= 0;

    stateStarted= false;
    statePaused= false;
}

///////////////////
// Destructor    //
Timer::~Timer(void)
///////////////////
{
}

//////////////////////////
// Start                //
void Timer::Start ( void )
//////////////////////////
{
    stateStarted= true;
    statePaused= false;

    startTicks= SDL_GetTicks();

    return;
}

/////////////////////////
// Stop                //
void Timer::Stop ( void )
/////////////////////////
{
    stateStarted= false;
    statePaused= false;

    return;
}

//////////////////////////
// Pause                //
void Timer::Pause ( void )
//////////////////////////
{
    if( ( stateStarted == true ) && ( statePaused == false ) )
    {
        statePaused= true;
        pausedTicks= SDL_GetTicks() - startTicks;
    }

    return;
}

////////////////////////////
// Unpause                //
void Timer::Unpause ( void )
////////////////////////////
{
    if( statePaused == true )
    {
        statePaused= false;
        startTicks= SDL_GetTicks() - pausedTicks;
        pausedTicks= 0;
    }

    return;
}

///////////////////////////////////
// IsStarted                     //
bool Timer::IsStarted( void ) const
///////////////////////////////////
{
    return stateStarted;
}

//////////////////////////////////
// IsPaused                     //
bool Timer::IsPaused( void ) const
//////////////////////////////////
{
    return statePaused;
}

/////////////////////////////////
// GetTicks                    //
int Timer::GetTicks( void ) const
/////////////////////////////////
{
    if( stateStarted == true )
    {
        if( statePaused == true )
        {
            return pausedTicks;
        }
        else
        {
            return SDL_GetTicks() - startTicks;
        }
    }
    else
    {
        return 0;
    }
}

/* end of file */
