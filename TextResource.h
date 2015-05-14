///////////////////////////////////////////////////////////////////////////////
//  Filename       : TextResource.h                                          //
//                   TextResource.cpp                                        //
//  Date           : 2009/02/12 ~ 2009/02/12                                 //
//  Author         : Bak Yeono (bakyeono@gmail.com)                          //
//  Description    : This is the text resources                              //
//                   and a converter class that converts texts to utf-16     //
///////////////////////////////////////////////////////////////////////////////

#ifndef __TEXTRESOURCE_H__
#define __TEXTRESOURCE_H__

#include <SDL/SDL.h>
#include <locale.h>

#define NUMBER_OF_TEXT_RESOURCES 11

//////////////////
class TextResource
//////////////////
{
    private:
        static const char* textres[NUMBER_OF_TEXT_RESOURCES];
        static wchar_t* u16res[NUMBER_OF_TEXT_RESOURCES];
    
    public:
        TextResource( void );
        TextResource( const TextResource& sourceObject );
        ~TextResource( void );
        void ReadyUTF16( void );
        void DeleteUTF16( void );
        const wchar_t* GetUTF16( int resNumber ) const;
};

#endif

/* enf of file */
