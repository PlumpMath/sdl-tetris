///////////////////////////////////////////////////////////////////////////////
//  Filename       : Parser.h                                                //
//                   Parser.cpp                                              //
//  Date           : 2009/02/08                                              //
//  Author         : Bak Yeono (bakyeono@gmail.com)                          //
//  Description    : This class decodes config settings from ASNI text file. //
///////////////////////////////////////////////////////////////////////////////

#ifndef __PARSER_H__
#define __PARSER_H__

#include <stdio.h>
#include <iostream>
#include "LogWriter.h"

///////////////////////////////////////
// Categories of Extern File Command //
///////////////////////////////////////
enum _EXTERNCMD_ID
{
    EXTERNCMD_SCREEN_MODE= 10,    // SCREEN_MODE
    EXTERNCMD_SCREEN_WIDTH= 11,   // SCREEN_WIDTH
    EXTERNCMD_SCREEN_HEIGHT= 12,  // SCREEN_HEIGHT
    EXTERNCMD_SCREEN_BPP= 13,     // SCREEN_BPP
    EXTERNCMD_IMAGE_FILE= 20,     // IMAGE_FILE
    EXTERNCMD_FONT_FILE= 21,      // FONT_FILE
    EXTERNCMD_FONT_SIZE= 22,      // FONT_SIZE
    EXTERNCMD_MUSIC_FILE= 23,     // MUSIC_FILE
    EXTERNCMD_CHUNK_FILE= 24,     // CHUNK_FILE
    EXTERNCMD_COMMENT= -1,        // # COMMENT
    EXTERNCMD_ILLEGALCOMMAND= -2  // etc
};

////////////
class Parser
////////////
{
    private:
        char line[1024];
        char lineCategory[1024];
        char lineNumber[1024];
        char lineContent[1024];
    
    public:
        void Parser::DecodeLine( FILE* fp, int* category, int* number, char* content );
};

#endif
/* end of file */
