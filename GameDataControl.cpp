///////////////////////////////////////////////////////////////////////////////
//  Filename       : GameDataControl.h                                       //
//                   GameDataControl.cpp                                     //
//  Date           : 2009/02/09                                              //
//  Author         : Bak Yeono (bakyeono@gmail.com)                          //
//  Description    : This class controls game board and block datas.         //
///////////////////////////////////////////////////////////////////////////////

#include "GameDataControl.h"

//////////////////////////////////////
// Constructor                      //
GameDataControl::GameDataControl(void)
//////////////////////////////////////
{
    this->stateBoardFull= false;
    this->stateBlockSettled= false;
    this->blockX= 0;
    this->blockY= 0;
    this->blockModelNumber= 0;
}

///////////////////////////////////////
// Destructor                        //
GameDataControl::~GameDataControl(void)
///////////////////////////////////////
{
}

/////////////////////////////////////////
// IsBoardFull                         //
bool GameDataControl::IsBoardFull( void )
/////////////////////////////////////////
{
    return stateBoardFull;
}

////////////////////////////////////////////
// IsBlockSettled                         //
bool GameDataControl::IsBlockSettled( void )
////////////////////////////////////////////
{
    return stateBlockSettled;
}

/////////////////////////////////////////
// CreateBlock                         //
void GameDataControl::CreateBlock( void )
/////////////////////////////////////////
{
    Dice dice( 0, NUMBER_OF_BLOCK_MODELS - 1 );

    this->stateBlockSettled= false;
    this->blockX= 7;
    this->blockY= 0;
    this->blockModelNumber= dice.Roll( 1 );

    if( CheckCollision() == true )
    {
        stateBoardFull= true;
        stateBlockSettled= true;
    }
}

/////////////////////////////////////////////
// MoveBlockRotate                         //
void GameDataControl::MoveBlockRotate( void )
/////////////////////////////////////////////
{
    if( ( blockModelNumber % 4 ) == 3 )
        blockModelNumber-= 3;
    else
        blockModelNumber++;

    // if the block crashed, replace it;
    if( CheckCollision() == true )
    {
        if( ( blockModelNumber % 4 ) == 0 )
            blockModelNumber+= 3;
        else
            blockModelNumber--;
    }
    else
    {
        SoundControl sound;
        sound.PlayChunk( 1 );
    }

    return;
}

///////////////////////////////////////////
// MoveBlockLeft                         //
void GameDataControl::MoveBlockLeft( void )
///////////////////////////////////////////
{
    blockX--;

    // if the block crashed, replace it;
    if( CheckCollision() == true )
    {
        blockX++;
    }
    else
    {
        SoundControl sound;
        sound.PlayChunk( 0 );
    }

    return;
}

////////////////////////////////////////////
// MoveBlockRight                         //
void GameDataControl::MoveBlockRight( void )
////////////////////////////////////////////
{
    blockX++;

    // if the block crashed, replace it;
    if( CheckCollision() == true )
    {
        blockX--;
    }
    else
    {
        SoundControl sound;
        sound.PlayChunk( 0 );
    }

    return;
}

///////////////////////////////////////////
// MoveBlockDown                         //
void GameDataControl::MoveBlockDown( void )
///////////////////////////////////////////
{
    blockY++;

    // if the block crashed, settle it;
    if( CheckCollision() == true )
    {
        blockY--;
        SettleBlock();
    }
    else
    {
        SoundControl sound;
        sound.PlayChunk( 0 );
    }

    return;
}

///////////////////////////////////////////
// MoveBlockFall                         //
void GameDataControl::MoveBlockFall( void )
///////////////////////////////////////////
{
    blockY++;

    // if the block crashed, settle it;
    if( CheckCollision() == true )
    {
        blockY--;
        SettleBlock();
    }

    return;
}

///////////////////////////////////////////
// MoveBlockDrop                         //
void GameDataControl::MoveBlockDrop( void )
///////////////////////////////////////////
{
    while( CheckCollision() == false )
    {
        blockY++;
    }

    blockY--;
    SettleBlock();

    return;
}

/////////////////////////////////////////
// SettleBlock                         //
void GameDataControl::SettleBlock( void )
/////////////////////////////////////////
{
    for( int y= 0 ; y < 4 ; y++ )
    {
        for( int x= 0 ; x < 4 ; x++ )
        {
            if( blockModel[blockModelNumber][y][x] != 0 )
                board[blockY + y][blockX + x]= blockModel[blockModelNumber][y][x];
        }
    }
    SoundControl sound;
    sound.PlayChunk( 2 );
    stateBlockSettled= true;

    return;
}

////////////////////////////////////////////
// CheckCollision                         //
bool GameDataControl::CheckCollision( void )
////////////////////////////////////////////
{
    for( int y= 0 ; y < 4 ; y++ )
    {
        for( int x= 0 ; x < 4 ; x++ )
        {
            // check if there is block
            if( blockModel[blockModelNumber][y][x] == 0 )
                continue;
            // check if there is something in the place that the block should be
            if( board[y + blockY][x + blockX] == 0 )
                continue;
            // collision found
            return true;
        }
    }
    // collision not found
    return false;
}

///////////////////////////////////////////////////////////////
// SetBoardByDefaultStage                                    //
void GameDataControl::SetBoardByDefaultStage( int stageNumber )
///////////////////////////////////////////////////////////////
{
    if( stageNumber < 0 )
        stageNumber= 0;

    if( stageNumber >= MAX_STAGE )
        stageNumber= MAX_STAGE -1;

    for( int y= 0 ; y < GAMEBOARD_HEIGHT ; y++ )
    {
        for( int x= 0 ; x < GAMEBOARD_WIDTH ; x++ )
        {
            board[y][x]= boardDefault[stageNumber][y][x];
        }
    }

    return;
}

////////////////////////////////////////
// ControlLine                        //
int GameDataControl::ControlLine( void )
////////////////////////////////////////
{
    int cleared= 0;

    for( int y= 1 ; y < GAMEBOARD_HEIGHT - 1 ; y++ )
    {
        if( CheckLine( y ) )
        {
            cleared++;
            ClearLine( y );
            y--;
        }
    }
    
    return cleared;
}

////////////////////////////////////////
// CheckLine                          //
bool GameDataControl::CheckLine( int y )
////////////////////////////////////////
{
    for( int x= 1 ; x < GAMEBOARD_WIDTH - 1 ; x++ )
    {
        if( board[y][x] == 0 )
            return false;
    }
    return true;
}

////////////////////////////////////////
// ClearLine                          //
void GameDataControl::ClearLine( int y )
////////////////////////////////////////
{
    int cleared= 0;

    for( ; y > 1 ; y-- )
    {
        for( int x = 1 ; x < GAMEBOARD_WIDTH - 1 ; x++ )
        {
            if( ( board[y][x] != 1 ) && ( board[y][x] != 2 ) )
            {
                if( ( board[y-1][x] != 1 ) && ( board[y-1][x] != 2 ) )
                {
                    board[y][x]= board[y-1][x];
                }
            }
        }
    }
}

////////////////////////////////////////
// PrintBlock                         //
void GameDataControl::PrintBlock( void )
////////////////////////////////////////
{
    GraphicControl graphic;
    for( int y= 0 ; y < 4 ; y++ )
    {
        for( int x= 0 ; x < 4 ; x++ )
        {
            graphic.PrintBlock( blockModel[blockModelNumber][y][x], blockX + x, blockY + y );
        }
    }
    
    return;
}

//////////////////////////////////////////////
// PrintBoard                               //
// print entire game board                  //
void GameDataControl::PrintBoard( void ) const
//////////////////////////////////////////////
{
    GraphicControl graphic;
    for( int y= 0 ; y < GAMEBOARD_HEIGHT ; y++ )
    {
        for( int x= 0 ; x < GAMEBOARD_WIDTH ; x++ )
        {
            graphic.PrintBlock( board[y][x], x, y );
        }
    }
    
    return;
}

/////////////////////////
// Constant Block Data //
/////////////////////////
const char GameDataControl::blockModel[NUMBER_OF_BLOCK_MODELS][4][4]=
{
    /* blockModel[0]  -- blockModelType0
       ��
       ���� */ 
    {
        {3,0,0,0},
        {3,3,3,0},
        {0,0,0,0},
        {0,0,0,0} },
    {
        {0,3,0,0},
        {0,3,0,0},
        {3,3,0,0},
        {0,0,0,0} },
    {
        {3,3,3,0},
        {0,0,3,0},
        {0,0,0,0},
        {0,0,0,0} },
    {
        {3,3,0,0},
        {3,0,0,0},
        {3,0,0,0},
        {0,0,0,0} },
    /* blockModel[4]  -- blockModelType1
           �� 
       ���� */ 
    {
        {0,0,4,0},
        {4,4,4,0},
        {0,0,0,0},
        {0,0,0,0} },
    {
        {4,4,0,0},
        {0,4,0,0},
        {0,4,0,0},
        {0,0,0,0} },
    {
        {4,4,4,0},
        {4,0,0,0},
        {0,0,0,0},
        {0,0,0,0} },
    {
        {4,0,0,0},
        {4,0,0,0},
        {4,4,0,0},
        {0,0,0,0} },
    /* blockModel[8]  -- blockModelType2
         ��
       ���� */ 
    {
        {0,5,0,0},
        {5,5,5,0},
        {0,0,0,0},
        {0,0,0,0} },
    {
        {0,5,0,0},
        {5,5,0,0},
        {0,5,0,0},
        {0,0,0,0} },
    {
        {0,0,0,0},
        {5,5,5,0},
        {0,5,0,0},
        {0,0,0,0} },
    {
        {0,5,0,0},
        {0,5,5,0},
        {0,5,0,0},
        {0,0,0,0} },
    /* blockModel[12]  -- blockModelType3
       ��
       ��
       ��
       �� */ 
    {
        {0,6,0,0},
        {0,6,0,0},
        {0,6,0,0},
        {0,6,0,0} },
    {
        {0,0,0,0},
        {6,6,6,6},
        {0,0,0,0},
        {0,0,0,0} },
    {
        {0,6,0,0},
        {0,6,0,0},
        {0,6,0,0},
        {0,6,0,0} },
    {
        {0,0,0,0},
        {6,6,6,6},
        {0,0,0,0},
        {0,0,0,0} },
    /* blockModel[16]  -- blockModelType4
       ���
       ��� */ 
    {
        {7,7,0,0},
        {7,7,0,0},
        {0,0,0,0},
        {0,0,0,0} },
    {
        {7,7,0,0},
        {7,7,0,0},
        {0,0,0,0},
        {0,0,0,0} },
    {
        {7,7,0,0},
        {7,7,0,0},
        {0,0,0,0},
        {0,0,0,0} },
    {
        {7,7,0,0},
        {7,7,0,0},
        {0,0,0,0},
        {0,0,0,0} },
    /* blockModel[20]  -- blockModelType5
         ���
       ��� */ 
    {
        {0,8,8,0},
        {8,8,0,0},
        {0,0,0,0},
        {0,0,0,0} },
    {
        {0,8,0,0},
        {0,8,8,0},
        {0,0,8,0},
        {0,0,0,0} },
    {
        {0,8,8,0},
        {8,8,0,0},
        {0,0,0,0},
        {0,0,0,0} },
    {
        {0,8,0,0},
        {0,8,8,0},
        {0,0,8,0},
        {0,0,0,0} },
    /* blockModel[24]  -- blockModelType6
       ���
         ��� */ 
    {
        {9,9,0,0},
        {0,9,9,0},
        {0,0,0,0},
        {0,0,0,0} },
    {
        {0,0,9,0},
        {0,9,9,0},
        {0,9,0,0},
        {0,0,0,0} },
    {
        {9,9,0,0},
        {0,9,9,0},
        {0,0,0,0},
        {0,0,0,0} },
    {
        {0,0,9,0},
        {0,9,9,0},
        {0,9,0,0},
        {0,0,0,0} }
};

const char GameDataControl::boardDefault[MAX_STAGE][GAMEBOARD_HEIGHT][GAMEBOARD_WIDTH]=
{
    { /* Stage 0 */
        { 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
        { 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
        { 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    },
    { /* Stage 1 */
        { 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
        { 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
        { 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    },
    { /* Stage 2 */
        { 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
        { 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
        { 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 1},
        { 1, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 1},
        { 1, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 1},
        { 1, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 1},
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    },
    { /* Stage 3 */
        { 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
        { 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
        { 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 1},
        { 1, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 1},
        { 1, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    },
    { /* Stage 4 */
        { 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
        { 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
        { 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 1},
        { 1, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 1},
        { 1, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 1},
        { 1, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 1},
        { 1, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 1},
        { 1, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 1},
        { 1, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 1},
        { 1, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 1},
        { 1, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 1},
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    },
    { /* Stage 5 */
        { 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
        { 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
        { 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    },
    { /* Stage 6 */
        { 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
        { 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
        { 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 1},
        { 1, 0, 8, 7, 8, 0, 0, 0, 0, 0, 0, 8, 7, 8, 0, 1},
        { 1, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 1},
        { 1, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 8, 0, 0, 8, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 8, 7, 8, 8, 7, 8, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 8, 0, 0, 8, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 0, 1},
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    },
    { /* Stage 7 */
        { 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
        { 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
        { 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 9, 9, 9, 9, 0, 0, 0, 0, 9, 9, 9, 9, 0, 1},
        { 1, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 1},
        { 1, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 1},
        { 1, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 1},
        { 1, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 1},
        { 1, 0, 2, 2, 2, 2, 0, 0, 0, 0, 2, 2, 2, 2, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    },
    { /* Stage 8 */
        { 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
        { 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
        { 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    },
    { /* Stage 9 */
        { 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
        { 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
        { 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 5, 5, 5, 0, 0, 0, 0, 0, 0, 5, 5, 5, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 5, 5, 5, 0, 0, 5, 5, 5, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 5, 5, 5, 0, 0, 0, 0, 0, 0, 5, 5, 5, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    },
    { /* Stage 10 */
        { 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
        { 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
        { 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 1, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 1, 1, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 1, 1, 1, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 1, 1, 1, 1, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 1},
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    },
    { /* Stage 11 */
        { 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
        { 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
        { 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 4, 6, 4, 0, 0, 4, 6, 4, 0, 0, 0, 1},
        { 1, 0, 0, 0, 4, 6, 4, 0, 0, 4, 6, 4, 0, 0, 0, 1},
        { 1, 0, 0, 0, 4, 6, 4, 0, 0, 4, 6, 4, 0, 0, 0, 1},
        { 1, 0, 0, 4, 0, 6, 0, 4, 4, 0, 6, 0, 4, 0, 0, 1},
        { 1, 0, 0, 0, 0, 6, 0, 0, 0, 0, 6, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 4, 6, 4, 0, 0, 4, 6, 4, 0, 0, 0, 1},
        { 1, 0, 0, 0, 4, 6, 4, 0, 0, 4, 6, 4, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 6, 0, 0, 0, 0, 6, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 6, 0, 0, 0, 0, 6, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 6, 0, 0, 0, 0, 6, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 6, 0, 0, 0, 0, 6, 0, 0, 0, 0, 1},
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    },
    { /* Stage 12 */
        { 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
        { 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
        { 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    },
    { /* Stage 13 */
        { 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
        { 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
        { 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 2, 2, 0, 0, 0, 0, 2, 2, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 2, 2, 0, 0, 0, 0, 2, 2, 0, 0, 0, 1},
        { 1, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 1},
        { 1, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    },
    { /* Stage 14 */
        { 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
        { 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
        { 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
        { 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    },
    { /* Stage 15 */
        { 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
        { 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
        { 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 7, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 7, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 7, 0, 0, 0, 0, 0, 7, 0, 0, 7, 0, 1},
        { 1, 0, 0, 0, 7, 0, 0, 0, 0, 0, 7, 0, 0, 7, 0, 1},
        { 1, 0, 0, 0, 7, 0, 0, 0, 0, 0, 7, 0, 0, 2, 2, 1},
        { 1, 0, 0, 0, 7, 0, 0, 0, 0, 0, 7, 0, 2, 2, 0, 1},
        { 1, 0, 0, 0, 7, 0, 0, 7, 0, 0, 2, 2, 2, 7, 0, 1},
        { 1, 0, 2, 0, 7, 0, 0, 7, 0, 2, 2, 0, 0, 7, 0, 1},
        { 1, 0, 2, 2, 2, 0, 2, 2, 2, 2, 7, 0, 0, 7, 0, 1},
        { 1, 0, 0, 0, 2, 2, 2, 7, 0, 0, 7, 0, 0, 7, 0, 1},
        { 1, 0, 0, 0, 7, 0, 0, 7, 0, 0, 7, 0, 0, 7, 0, 1},
        { 1, 0, 0, 0, 7, 0, 0, 7, 0, 0, 7, 0, 0, 7, 0, 1},
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    },
    { /* Stage 16 */
        { 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
        { 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
        { 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 2, 2, 2, 0, 0, 2, 2, 2, 0, 0, 0, 1},
        { 1, 0, 0, 0, 2, 7, 2, 0, 0, 2, 7, 2, 0, 0, 0, 1},
        { 1, 0, 0, 0, 2, 7, 2, 0, 0, 2, 7, 2, 0, 0, 0, 1},
        { 1, 0, 0, 0, 2, 7, 2, 0, 0, 2, 7, 2, 0, 0, 0, 1},
        { 1, 0, 0, 0, 2, 2, 2, 0, 0, 2, 2, 2, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
        { 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
        { 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    },
    { /* Stage 17 */
        { 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
        { 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
        { 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 1},
        { 1, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 1},
        { 1, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 1},
        { 1, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 1},
        { 1, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 1},
        { 1, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 1},
        { 1, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 1},
        { 1, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 1},
        { 1, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    },
    { /* Stage 18 */
        { 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
        { 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
        { 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 2, 2, 2, 2, 0, 0, 2, 2, 2, 2, 0, 0, 1},
        { 1, 0, 0, 2, 0, 0, 2, 0, 0, 2, 0, 0, 2, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 1},
        { 1, 2, 0, 0, 2, 0, 0, 0, 0, 0, 0, 2, 0, 0, 2, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    },
    { /* Stage 19 */
        { 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
        { 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
        { 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 1},
        { 1, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 1},
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    },
};

/* end of file */