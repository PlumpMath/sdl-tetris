///////////////////////////////////////////////////////////////////////////////
//  Filename       : Play.h                                                  //
//                   Play.cpp                                                //
//  Date           : 2009/02/10                                              //
//  Author         : Bak Yeono (bakyeono@gmail.com)                          //
//  Description    : This class controls the entire game play.               //
///////////////////////////////////////////////////////////////////////////////

#include "GamePlay.h"

//////////////////////////
// Constructor          //
GamePlay::GamePlay( void )
//////////////////////////
{
    this->stateGameOver= false;

    this->score= 0;
    this->lineCleared= 0;
    this->stage= 0;
    this->lineLeft= 0;
}

///////////////////////////
// Destructor            //
GamePlay::~GamePlay( void )
///////////////////////////
{
}

////////////////////////////////////
// Play                           //
// the main game loop             //
int GamePlay::Play( int startStage )
////////////////////////////////////
{
    TextResource text;
    
    GraphicControl graphic;
    SoundControl sound;

    if( startStage < -1 )
        startStage= -1;

    if( startStage >= MAX_STAGE )
        startStage= MAX_STAGE - 1;

    score= 0;
    lineCleared= 0;
    stage= startStage;
    if( stage == -1 )
        lineLeft= 10000000;
    else
        lineLeft= 10 + ( stage / 2 );

    GameDataControl gamedata;

    Timer keyDelayUp, keyDelayDown, keyDelayLeft, keyDelayRight, keyDelaySpace;
    keyDelayUp.Start();
    keyDelayDown.Start();
    keyDelayLeft.Start();
    keyDelayRight.Start();
    keyDelaySpace.Start();

    Timer blockTimer;

    while( 1 )
    {
        if( stateGameOver == true )
            break;

        // new game start
        
        gamedata.SetBoardByDefaultStage( stage );
        if( stage == -1 )
            sound.PlayMusic( 6 );
        else
            sound.PlayMusic( ( stage % 5 ) + 1 );

        // stage loop
        while( 1 )
        {
            // next stage
            if( lineLeft <= 0 )
            {
                score+= ( ( stage + 1 ) * 1000 );
                stage++;
                lineLeft= 10 + ( stage / 2 );

                if( stage >= MAX_STAGE )
                    stateGameOver= true;

                int reachedStage= 0;
                FILE* fp= NULL;
                fp= fopen( "user.dat", "rb" );
                if( fp != NULL )
                {
                    fread( &reachedStage, sizeof( int ), 1, fp );
                    fclose( fp );
                }

                if( stage > reachedStage )
                {
                    fp= NULL;
                    fp= fopen( "user.dat", "wb" );
                    if( fp != NULL )
                    {
                        fwrite( &stage, sizeof( int ), 1, fp );
                        fclose( fp );
                    }
                }

                sound.PlayChunk( 4 );
                break;
            }

            if( gamedata.IsBoardFull() == true )
                stateGameOver= true;

            if( stateGameOver == true )
            {
                Timer gameoverTimer;
                gameoverTimer.Start();
                sound.StopMusic();
                sound.PlayChunk( 3 );
                graphic.PrintImage( IMAGE_GAMEBOARD1, 425, 10 );
                graphic.Flip();
                while( gameoverTimer.GetTicks() <= 1500 )
                {
                    SDL_PollEvent( &event );
                }
                break;
            }

            // new block start
            gamedata.CreateBlock();
            blockTimer.Start();

            // block loop
            while( 1 )
            {
                if( gamedata.IsBlockSettled() == true || stateGameOver == true )
                    break;

                if( blockTimer.GetTicks() >= 500 )
                {
                    gamedata.MoveBlockFall();
                    blockTimer.Start();
                }

                while( SDL_PollEvent( &event ) )
                {
                    switch( event.type )
                    {
                    case SDL_QUIT:
                        stateGameOver = true;
                        return -1;
                    }
                }

                Uint8* keystate= SDL_GetKeyState( NULL );
                if( keystate[ SDLK_ESCAPE ] )
                {
                    stateGameOver= true;
                }
                if( keystate[ SDLK_UP ] )
                {
                    if( keyDelayUp.GetTicks() > 150 )
                    {
                        gamedata.MoveBlockRotate();
                        keyDelayUp.Start();
                    }
                }
                if( keystate[ SDLK_DOWN ] )
                {
                    if( keyDelayDown.GetTicks() > 80 )
                    {
                        gamedata.MoveBlockDown();
                        keyDelayDown.Start();
                    }
                }
                if( keystate[ SDLK_LEFT ] )
                {
                    if( keyDelayLeft.GetTicks() > 120 )
                    {
                        gamedata.MoveBlockLeft();
                        keyDelayLeft.Start();
                    }
                }
                if( keystate[ SDLK_RIGHT ] )
                {
                    if( keyDelayRight.GetTicks() > 120 )
                    {
                        gamedata.MoveBlockRight();
                        keyDelayRight.Start();
                    }
                }

                if( keystate[ SDLK_SPACE ] )
                {
                    if( keyDelaySpace.GetTicks() > 250 )
                    {
                        gamedata.MoveBlockDrop();
                        keyDelaySpace.Start();
                    }
                }

                // From here we print images on the screen
                graphic.PrintImage( IMAGE_BACKGROUND0 + ( ( stage + 1 ) % 8 ), 0, 0 );
                graphic.PrintImage( IMAGE_GAMEBOARD0, 425, 10 );
    
                gamedata.PrintBoard();
                gamedata.PrintBlock();
    
                if( stateGameOver == true )
                    graphic.PrintImage( IMAGE_GAMEBOARD1, 425, 10 );

                // print score
                {
                    std::stringstream textStage, textScore, textCleared, textLeft;

                    textStage << stage + 1;
                    textScore << score;
                    textCleared << lineCleared;
                    textLeft << lineLeft;

                    graphic.PrintUNICODE( text.GetUTF16( 6 ), 0, colorGreen, 50, 300 );
                    graphic.PrintUNICODE( text.GetUTF16( 7 ), 0, colorGreen, 50, 340 );
                    if( stage == -1 )
                        graphic.PrintUNICODE( text.GetUTF16( 8 ), 0, colorGreen, 50, 380 );
                    else
                        graphic.PrintUNICODE( text.GetUTF16( 9 ), 0, colorGreen, 50, 380 );

                    graphic.PrintText( textScore.str().c_str(), 0, colorGreen, 160, 340 );
                    if( stage == -1 )
                    {
                        graphic.PrintUNICODE( text.GetUTF16( 10 ), 0, colorRed, 160, 300 );
                        graphic.PrintText( textCleared.str().c_str(), 0, colorGreen, 200, 380 );
                    }
                    else
                    {
                        graphic.PrintText( textStage.str().c_str(), 0, colorGreen, 160, 300 );
                        graphic.PrintText( textLeft.str().c_str(), 0, colorGreen, 200, 380 );
                    }
                }
                graphic.PrintUNICODE( text.GetUTF16(0), 1, colorGreen, 20, 550 );
                graphic.PrintUNICODE( text.GetUTF16(1), 1, colorGreen, 20, 570 );
    
                graphic.Flip();
            }

            // line clear check
            {
                int cleared= 0;
                cleared= gamedata.ControlLine();
                score+= ( int ) ( ( cleared * 100 ) * ( 1 + ( stage * 0.5 ) ) );
                lineCleared+= cleared;
                lineLeft-= cleared;
            }
        score+= 1;
        }
    }

    return 0;
}

/* end of file */
