///////////////////////////////////////////////////////////////////////////////
//  Filename       : Block.h                                                 //
//                   Block.cpp                                               //
//  Date           : 2009/02/09 ~ 2009/02/12                                 //
//  Author         : Bak Yeono (bakyeono@gmail.com)                          //
//  Description    : This class stores tetris block.                         //
///////////////////////////////////////////////////////////////////////////////

#ifndef __BLOCK_H__
#define __BLOCK_H__

#include "ProgramInfo.h"
#include "Dice.h"

///////////
class Block
///////////
{
    private:
        bool stateSettled;
        int posX;
        int posY;
        int modelNumber;
    
    public:
        static const char blockModel[NUMBER_OF_BLOCK_MODELS][4][4];
        
        GameDataControl(void);
        ~GameDataControl(void);
    
        bool IsSettled( void ) const;
        int GetModelNumber( void ) const;
        void Start( void );
        void Rotate( void );
        void MoveLeft( void );
        void MoveRight( void );
        void MoveDown( void );
};

#endif
/* end of file */
