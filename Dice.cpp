///////////////////////////////////////////////////////////////////////////////
//  Filename       : Dice.h                                                  //
//                   Dice.cpp                                                //
//  Date           : 2009/01/16 ~ 2009/02/09                                 //
//  Author         : Bak Yeono (bakyeono@gmail.com)                          //
//  Description    : Simulates dice rollings.                                //
//                   Used in D&D like RPG games.                             //
///////////////////////////////////////////////////////////////////////////////

#include "Dice.h"

//////////////////////////////////////
// Constructor                      //
// Sets a sideMin ~ sideMax dice    //
Dice::Dice( int sideMin, int sideMax )
//////////////////////////////////////
{
    this->sideMin= sideMin;
    this->sideMax= sideMax;
}
////////////////////////////////////
// Roll                           //
// roll dice for (parameter) times//
int Dice::Roll( int rollTime ) const
////////////////////////////////////
{
    int sum= 0;
    
    for( int i= 0 ; i < rollTime ; i++ )
        sum+= ( ( rand() / ( RAND_MAX / sideMax ) ) + sideMin );
    
    return sum;
}
