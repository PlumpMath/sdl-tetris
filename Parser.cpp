///////////////////////////////////////////////////////////////////////////////
//  Filename       : Parser.h                                                //
//                   Parser.cpp                                              //
//  Date           : 2009/02/08                                              //
//  Author         : Bak Yeono (bakyeono@gmail.com)                          //
//  Description    : This class decodes config settings from ASNI text file. //
//                   It also has information about external commands used by //
//                   config files.                                           //
///////////////////////////////////////////////////////////////////////////////

#include "Parser.h"

//////////////////////////////////////////////////////////////////////////////
// DecodeLine                                                               //
// reads a command line from the config file, and decodes its meaning       //
void Parser::DecodeLine( FILE* fp, int* category, int* number, char* content )
//////////////////////////////////////////////////////////////////////////////
{
    // initialize the variables
    this->line[0]= '\0';
    this->lineCategory[0]= '\0';
    this->lineNumber[0]= '\0';
    this->lineContent[0]= '\0';

    // get a line from the file
    fgets( line, sizeof( line ), fp );

    // if thie line is a comment, skip it.
    if( line[0] == '#' || line[0] == ' ' || line[0] == '\n' || line[0] == '\0' )
    {
        *category= EXTERNCMD_COMMENT;
        *number= -1;
        content[0]= '\0';
        return;
    }

    int lineEnd= strlen( line ); // end of the line
    int lineIndex= 0; // indicates how much have we red the line
    int lineCategoryIndex= 0;
    int lineNumberIndex= 0;
    int lineContentIndex= 0;

    // get the command's category
    for( ; lineIndex < lineEnd ; )
    {
        lineCategory[ lineCategoryIndex ]= line[ lineIndex ];
        // if this character is NOT an alphabet or '_', break the loop
        if( ! (    ( 'A' <= line[lineIndex] && line[lineIndex] <= 'Z' )
            || ( 'a' <= line[lineIndex] && line[lineIndex] <= 'z' )
            || ( line[lineIndex] == '_' ) ) )
            break;
        lineIndex++;
        lineCategoryIndex++;
    }
    lineCategory[lineCategoryIndex]= '\0';

    // let find the command's number ( find a number or '=' )
    for( ; lineIndex < lineEnd ; )
    {
        if( '0' <= line[lineIndex] && line[lineIndex] <= '9' )
            break;
        if( line[lineIndex] == '=' )
            break;
        lineIndex++;
    }

    // get the command's number
    for( ; lineIndex < lineEnd ; )
    {
        lineNumber[lineNumberIndex]= line[lineIndex];
        // if this aharacter is NOT a number, break the loop
        if( ! ( '0' <= line[lineIndex] && line[lineIndex] <= '9' ) )
            break;
        lineIndex++;
        lineNumberIndex++;
    }
    lineNumber[lineNumberIndex]= '\0';

    // let's find the command's content ( find '\"' )
    for( ; lineIndex < lineEnd ; )
    {
        if( line[lineIndex] == '\"' )
        {
            lineIndex++;
            break;
        }
        lineIndex++;
    }

    // get the command's content
    for( ; lineIndex < lineEnd ; )
    {
        lineContent[lineContentIndex]= line[lineIndex];
        // if this character IS '\"', break the loop
        if( line[lineIndex] <= '\"' )
            break;
        lineIndex++;
        lineContentIndex++;
    }
    lineContent[lineContentIndex]= '\0';

    // let's make the command's category UPPER CASE in order to decode it
    for( int i= 0 ; i < (int) strlen( lineCategory ) ; i++ )
        toupper( lineCategory[i] );

    // make the command's category into INT and give it to the caller
    if( strcmp( lineCategory, "SCREEN_MODE" ) == 0 )
        *category= EXTERNCMD_SCREEN_MODE;

    else if( strcmp( lineCategory, "SCREEN_WIDTH" ) == 0 )
        *category= EXTERNCMD_SCREEN_WIDTH;

    else if( strcmp( lineCategory, "SCREEN_HEIGHT" ) == 0 )
        *category= EXTERNCMD_SCREEN_HEIGHT;

    else if( strcmp( lineCategory, "SCREEN_BPP" ) == 0 )
        *category= EXTERNCMD_SCREEN_BPP;

    else if( strcmp( lineCategory, "IMAGE_FILE" ) == 0 )
        *category= EXTERNCMD_IMAGE_FILE;

    else if( strcmp( lineCategory, "FONT_FILE" ) == 0 )
        *category= EXTERNCMD_FONT_FILE;

    else if( strcmp( lineCategory, "FONT_SIZE" ) == 0 )
        *category= EXTERNCMD_FONT_SIZE;

    else if( strcmp( lineCategory, "MUSIC_FILE" ) == 0 )
        *category= EXTERNCMD_MUSIC_FILE;

    else if( strcmp( lineCategory, "CHUNK_FILE" ) == 0 )
        *category= EXTERNCMD_CHUNK_FILE;

    else
        *category= EXTERNCMD_ILLEGALCOMMAND;

    // give the command's number to the caller, if there was no number it is -1
    if( lineNumber[0] == '\0' )
        *number= -1;
    else
        *number= atoi( lineNumber );

    // give the command's content to the caller
    strcpy( content, lineContent );

    return;
}

/* end of file */
