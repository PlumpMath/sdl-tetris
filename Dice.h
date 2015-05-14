///////////////////////////////////////////////////////////////////////////////
//  Filename       : Dice.h                                                  //
//                   Dice.cpp                                                //
//  Date           : 2009/01/16 ~ 2009/02/09                                 //
//  Author         : Bak Yeono (bakyeono@gmail.com)                          //
//  Description    : Simulates dice rollings.                                //
//                   Used in D&D like RPG games.                             //
///////////////////////////////////////////////////////////////////////////////

#ifndef __ROLLDICE_H__
#define __ROLLDICE_H__

#include <stdlib.h>
#include <time.h>

//////////
class Dice
//////////
{
    private:
        int sideMin;
        int sideMax;
    
    public:
        Dice( const int sideMin= 0, const int sideMax= 1 );
        int Roll( const int rollTime ) const;
};

#endif

/* end of file */
