///////////////////////////////////////////////////////////////////////////////
//  Filename       : ProgramInfo.h                                           //
//  Date           : 2009/02/08 ~ 2009/09/12                                 //
//  Author         : Bak Yeono (bakyeono@gmail.com)                          //
//  Description    : Program Information and Options                         //
//                   and other Shared Constants and Macros etc.              //
///////////////////////////////////////////////////////////////////////////////

#ifndef __PROGRAMINFO_H__
#define __PROGRAMINFO_H__

#include <time.h>

/////////////////////////
// Program Information //
/////////////////////////
#define PROGRAM_TITLE "Tetris"
#define PROGRAM_CAPTION "Tetris (Bak Yeono 2009/02/12)"
#define PROGRAM_AUTHOR "Bak Yeono"
#define PROGRAM_VERSION "2.0"
#define PROGRAM_LANGUAGE "Korean"

////////////////////////
// System Information //
////////////////////////
const time_t RUNNING_TIME= time( 0 );

///////////////////////
// Log Writer Option //
///////////////////////
const bool MAKELOG= false;

////////////////////////
// Screen Information //
////////////////////////
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define SCREEN_BPP 32

////////////////////////////
// Data Array Information //
////////////////////////////
#define IMAGE_ARRAY_FILENAME "datalist.txt"
#define IMAGE_ARRAY_LENGTH 100

#define FONT_ARRAY_FILENAME "datalist.txt"
#define FONT_ARRAY_LENGTH 10

#define MUSIC_ARRAY_FILENAME "datalist.txt"
#define MUSIC_ARRAY_LENGTH 100

#define CHUNK_ARRAY_FILENAME "datalist.txt"
#define CHUNK_ARRAY_LENGTH 100

/////////////////////////////////////
// Gameboard and Block Information //
/////////////////////////////////////
#define MAX_STAGE 20

#define NUMBER_OF_BLOCK_MODELS 28

#define TILE_WIDTH 20
#define TILE_HEIGHT 20

#define GAMEBOARD_WIDTH 16
#define GAMEBOARD_HEIGHT 23

#define GAMEBOARD_BLOCKSTARTPOS_X 7
#define GAMEBOARD_BLOCKSTARTPOS_Y 0

#define GAMEBOARD_POSX 440
#define GAMEBOARD_POSY 123

#endif
/* end of file */
