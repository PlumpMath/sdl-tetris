///////////////////////////////////////////////////////////////////////////////
//  Filename       : GameDataControl.h                                       //
//                   GameDataControl.cpp                                     //
//  Date           : 2009/02/09                                              //
//  Author         : Bak Yeono (bakyeono@gmail.com)                          //
//  Description    : This class controls game board and block datas.         //
///////////////////////////////////////////////////////////////////////////////

#ifndef __GAMEDATACONTROL_H__
#define __GAMEDATACONTROL_H__

#include "ProgramInfo.h"
#include "GraphicControl.h"
#include "SoundControl.h"
#include "Dice.h"

/////////////////////
class GameDataControl
/////////////////////
{
    private:
        static const char blockModel[NUMBER_OF_BLOCK_MODELS][4][4];
        static const char boardDefault[MAX_STAGE][GAMEBOARD_HEIGHT][GAMEBOARD_WIDTH];
    
        bool stateBoardFull;
        bool stateBlockSettled;
    
        int blockX;
        int blockY;
        int blockModelNumber;
    
        char board[GAMEBOARD_HEIGHT][GAMEBOARD_WIDTH];
    
        bool CheckCollision( void );
        void SettleBlock( void );
    
        bool CheckLine( int y );
        void ClearLine( int y );
    
    public:
        GameDataControl(void);
        ~GameDataControl(void);
    
        bool IsBoardFull( void );
        bool IsBlockSettled( void );
    
        void CreateBlock( void );
        void MoveBlockRotate( void );
        void MoveBlockLeft( void );
        void MoveBlockRight( void );
        void MoveBlockDown( void );
        void MoveBlockFall( void );
        void MoveBlockDrop( void );
        void SetBoardByDefaultStage( int stageNumber );
        int ControlLine( void );
    
        void PrintBlock( void );
        void PrintBoard( void ) const;
};

#endif
/* end of file */
