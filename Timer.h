///////////////////////////////////////////////////////////////////////////////
//  Filename       : Timer.h                                                 //
//                   Timer.cpp                                               //
//  Date           : 2009/02/09                                              //
//  Author         : Bak Yeono (bakyeono@gmail.com)                          //
//  Description    : A simple timer class. It uses SDL Timer.                //
///////////////////////////////////////////////////////////////////////////////

#ifndef __TIMER_H__
#define __TIMER_H__

#include <SDL/SDL.h>

///////////
class Timer
///////////
{
    private:
    	bool stateStarted;
    	bool statePaused;
    
    	int startTicks;
    	int pausedTicks;
    
    public:
    	Timer( void );
    	~Timer( void );
    
    	void Start ( void );
    	void Stop ( void );
    	void Pause ( void );
    	void Unpause ( void );
    
    	bool IsStarted( void ) const;
    	bool IsPaused( void ) const;
    
    	int GetTicks( void ) const;
};

#endif

/* end of file */
