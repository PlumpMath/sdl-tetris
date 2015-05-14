///////////////////////////////////////////////////////////////////////////////
//  Filename       : Initialize.h                                            //
//                   Initialize.cpp                                          //
//  Date           : 2009/02/10                                              //
//  Author         : Bak Yeono (bakyeono@gmail.com)                          //
//  Description    : This global function initializes the program.           //
///////////////////////////////////////////////////////////////////////////////

#ifndef __INITIALIZE_H__
#define __INITIALIZE_H__

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <time.h>
#include "ProgramInfo.h"
#include "GraphicControl.h"
#include "SoundControl.h"
#include "LogWriter.h"
#include "TextResource.h"

int Initialize( void );

#endif
/* end of file */
