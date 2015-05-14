///////////////////////////////////////////////////////////////////////////////
//  Filename       : MainMenu.h                                              //
//                   MainMenu.cpp                                            //
//  Date           : 2009/02/12                                              //
//  Author         : Bak Yeono (bakyeono@gmail.com)                          //
//  Description    : This global function controls the Main Menu loop        //
///////////////////////////////////////////////////////////////////////////////

#include "MainMenu.h"

int MainMenu( void )
{
    // classes used here
    GraphicControl graphic;
    SoundControl sound;
    TextResource text;
    
    // variable to get event
    SDL_Event event;

    // variables to select stage
    int reachedStage= 0;
    int startStage= 0;
    
    // set default gameboard
    board.SetStage( startStage );
    
    // load player's reached stage from the saved file
    {
        FILE* fp= NULL;
        fp= fopen( "user.dat", "rb" );
        if( fp != NULL )
        {
            fread( &reachedStage, sizeof( int ), 1, fp );
            fclose( fp );
        }
    }
    
    // play Main Menu music
    sound.PlayMusic( 0 );
    
    // Main Menu Loop
    while( 1 )
    {
        while( SDL_PollEvent( &event ) )
        {
            // Take User Control and Process Data
            switch( event.type )
            {
                case SDL_QUIT:
                    return -2;
                    break;
                
                case SDL_KEYDOWN:
                    switch( event.key.keysym.sym )
                    {
                        case SDLK_ESCAPE:
                            return -2;
                            break;
                            
                        case SDLK_LEFT:
                            startStage--;
                            if( startStage < -1 )
                                startStage= -1;
                                
                            else if( startStage == -1 )
                                board.SetStage( 0 );
                                
                            else
                                board.SetStage( startStage );
                            break;
                            
                        case SDLK_RIGHT:
                            startStage++;
                            if( startStage >= MAX_STAGE )
                                startStage= MAX_STAGE - 1;
                            board.SetStage( startStage );
                            break;
                            
                        case SDLK_SPACE:
                            if( startStage <= reachedStage )
                                return startStage;
                            break;
                    }
                    break;
            }

            // Print
            {
                // print background
                graphic.PrintImage( IMAGE_BACKGROUND0 + ( ( startStage + 1 ) % 8 ), 0, 0 );
                graphic.PrintImage( IMAGE_GAMEBOARD0, 425, 10 );
                
                // print gameboard
                gamedata.PrintBoard();
                if( startStage <= reachedStage )
                {
                    graphic.PrintUNICODE( text.GetUTF16(4), 0, colorGreen, 20, 420 );
                }
                else
                {
                    graphic.PrintImage( IMAGE_GAMEBOARD1, 425, 10 );
                    graphic.PrintUNICODE( text.GetUTF16(5), 0, colorRed, 20, 420 );
                }
                
                // print text
                {
                    std::stringstream textStage, textScore, textCleared, textLeft;
                    
                    textStage << startStage + 1;
                    
                    graphic.PrintUNICODE( text.GetUTF16(2), 0, colorGreen, 20, 300 );
                    graphic.PrintUNICODE( text.GetUTF16(3), 0, colorGreen, 20, 340 );
                    graphic.PrintUNICODE( text.GetUTF16(6), 0, colorGreen, 20, 380 );
                    
                    if( startStage == -1 )
                        graphic.PrintUNICODE( text.GetUTF16(10), 0, colorRed, 100, 380 );
                    else
                        graphic.PrintText( textStage.str().c_str(), 0, colorGreen, 100, 380 );
                }
                
                graphic.PrintUNICODE( text.GetUTF16(0), 1, colorGreen, 20, 550 );
                graphic.PrintUNICODE( text.GetUTF16(1), 1, colorGreen, 20, 570 );
                
                // flip
                graphic.Flip();
            }
        }
    }
}

/* end of file */
