///////////////////////////////////////////////////////////////////////////////
//  Filename       : TextResource.h                                          //
//                   TextResource.cpp                                        //
//  Date           : 2009/02/12 ~ 2009/02/12                                 //
//  Author         : Bak Yeono (bakyeono@gmail.com)                          //
//  Description    : This is Korean text resources                           //
///////////////////////////////////////////////////////////////////////////////

#include "TextResource.h"

//////////////////////////////////
// Constructor                  //
TextResource::TextResource( void )
//////////////////////////////////
{
    // initialize the UTF16 pointers
}

//////////////////////////////////////////////////////////////
// Copy Constructor                                         //
TextResource::TextResource( const TextResource& sourceObject )
//////////////////////////////////////////////////////////////
{
}
    
///////////////////////////////////
// Destructor                    //
TextResource::~TextResource( void )
///////////////////////////////////
{
}

/////////////////////////////////////
// ReadyUTF16                      //
void TextResource::ReadyUTF16( void )
/////////////////////////////////////
{
    // set locale to kor-euc;
    //setlocale( LC_ALL, "Korean_Korea.949" ); // -- for windows korean version
    setlocale( LC_ALL, "" );
    
    // allocate an UTF16 array and convert the text to UTF-16
    for( int i= 0; i < NUMBER_OF_TEXT_RESOURCES ; i++ )
    {
        u16res[i]= new wchar_t[strlen( textres[i] ) + 1];
        mbstowcs( u16res[i], textres[i], strlen( textres[i] + 1 ) );
    }
    return;
}

//////////////////////////////////////
// DeleteUTF16                      //
void TextResource::DeleteUTF16( void )
//////////////////////////////////////
{
    for( int i= 0; i < NUMBER_OF_TEXT_RESOURCES ; i++ )
    {
        if( u16res[i] != NULL )
            delete [] u16res[i];
    }
    return;
}

////////////////////////////////////////////////////////////
// GetUTF16                                               //
// by using this fuction, I can get the UTF-16 string     //
const wchar_t* TextResource::GetUTF16( int resNumber ) const
////////////////////////////////////////////////////////////
{
    return u16res[resNumber];
}

/////////////////////////////////////////////
// Constant Text Resource ( kor-euc text ) //
/////////////////////////////////////////////
const char* TextResource::textres[NUMBER_OF_TEXT_RESOURCES]=
{
    "���α׷� / ��������Ʈ ���� : �ڿ���",
    "�� �� ���� �� �׸��� ���۱��� �ش� ���۱��ڿ��� ����",
    "���� �ܰ踦 �����ϼ���",
    "�¿� ����Ű�� ����",
    "�����̽� �ٸ� ������ �����մϴ�",
    "���� �������� ���� �ܰ��Դϴ�",
    "�ܰ� : ",
    "���� : ",
    "���� �� : ",
    "���� �� : ",
    "���� ���",
};

//////////////////////////////////////////////////
// Point Arrays to Store Converted UTF-16 Texts //
//////////////////////////////////////////////////
wchar_t* TextResource::u16res[NUMBER_OF_TEXT_RESOURCES]=
{
    NULL,
};

/* end of file */
