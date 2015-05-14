///////////////////////////////////////////////////////////////////////////////
//  Filename       : GameBoard.h                                             //
//                   GameBoard.cpp                                           //
//  Date           : 2009/02/09 ~ 2009/02/12                                 //
//  Author         : Bak Yeono (bakyeono@gmail.com)                          //
//  Description    : This class stores the tetris game board state.          //
///////////////////////////////////////////////////////////////////////////////

#ifndef __GAMEBOARD_H__
#define __GAMEBOARD_H__

#include "ProgramInfo.h"

///////////////
class GameBoard
///////////////
{
    private:
        char board[GAMEBOARD_HEIGHT][GAMEBOARD_WIDTH];
        
    public:
        static const char boardDefault[MAX_STAGE][GAMEBOARD_HEIGHT][GAMEBOARD_WIDTH];
        
        GameBoard(void);
        ~GameBoard(void);
    
        void SetStage( int stageNumber );
        bool CheckLine( int y );
        void ClearLine( int y );
};

#endif

/* end of file */
