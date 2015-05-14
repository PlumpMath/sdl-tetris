///////////////////////////////////////////////////////////////////////////////
//  Filename       : Tetris.cpp                                              //
//  Date           : 2009/02/08 ~ 2009/02/12                                 //
//  Author         : Bak Yeono (bakyeono@gmail.com)                          //
//  Description    : It is my second Tetris game.                            //
//                   This time I used SDL for graphic and sound output.      //
//                   This program uses unicode(UTF-16).                      //
///////////////////////////////////////////////////////////////////////////////

#include "Initialize.h"
#include "MainMenu.h"
#include "Play.h"
#include "Close.h"

/////////////////////////////////
// main fuction                //
int main( int argc, char** argv )
/////////////////////////////////
{
    // Initialize the Program
    if ( Initialize() != 0 )
        return -1;
    
    while( 1 )
    {
        int choice= 0;
        
        // Call Main Menu
        choice= MainMenu();
        
        // choice == -2 : Exit the Program
        if( choice == -2 )
            break;
            
        // choice >=  0 : Start the Chosen Normal Stage
        // choice == -1 : Start the Unlimited Stage
        Play( choice );
    }
    
    // Prepare to Close the Program
    Close();
    
    // Now Successfully Close the Program
    return 0;
}

/* end of file */
