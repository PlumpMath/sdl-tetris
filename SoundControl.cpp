///////////////////////////////////////////////////////////////////////////////
//  Filename       : SoundControl.h                                          //
//                   SoundControl.cpp                                        //
//  Date           : 2009/02/08                                              //
//  Author         : Bak Yeono (bakyeono@gmail.com)                          //
//  Description    : This class controls all musics and sound effects        //
//                   by using SDL_mixer library.                             //
///////////////////////////////////////////////////////////////////////////////

#include "SoundControl.h"

//////////////////////////////////
// Constructor                  //
SoundControl::SoundControl( void )
//////////////////////////////////
{
    this->stateMusicPlaying= false;
    this->stateMusicPaused= false;
}

///////////////////////////////////
// Destructor                    //
SoundControl::~SoundControl( void )
///////////////////////////////////
{
    this->StopMusic();
}

////////////////////////////////////////////
// Initialize                             //
// it needs to be called by main function,//
// during program initializing time       //
// But, do it only one time!              //
////////////////////////////////////////////
int SoundControl::Initialize( void )
{
    if ( LoadMusicArray() == -1 )
        return -1;
    if ( LoadChunkArray() == -1 )
        return -1;
    stateInitialized= true;

    return 0;
}

//////////////////////////////////////////
// Close                                //
// needs to be called by main function, //
// before close the program             //
//////////////////////////////////////////
void SoundControl::Close( void )
{
    StopMusic();
    UnloadMusicArray();
    UnloadChunkArray();
    stateInitialized= false;
    return;
}

////////////////////////////////////////////
// LoadMusicArray                         //
// loads musics from MUSIC_ARRAY_FILENAME //
// it is called by Initialize()           //
int SoundControl::LoadMusicArray ( void )
////////////////////////////////////////////
{
    // variables to read image list (MUSIC_ARRAY_FILENAME)
    FILE* fp;
    int cmd_category= 0;
    int cmd_number= 0;
    char cmd_content[1024];

    LogWriter log;

    // read MUSIC_ARRAY_FILENAME
    fp= fopen( MUSIC_ARRAY_FILENAME, "rt" );
    // check if the list file does exist
    if( fp == NULL )
    {
        log << "ERROR! cannot open file : " << MUSIC_ARRAY_FILENAME << "\n";
        return -1;
    }
    else
    {
        Parser parser;
        while(1)
        {
            if( feof( fp ) != 0 )
                break;
            parser.DecodeLine( fp, &cmd_category, &cmd_number, cmd_content );
            if( cmd_category != EXTERNCMD_MUSIC_FILE )
                continue;
            if( cmd_number >= MUSIC_ARRAY_LENGTH )
            {
                if( MAKELOG ) { log << "ERROR! not enough music array : " << cmd_number << "\n"; }
                return -1;
            }
            if( cmd_number == -1 )
            {
                if( MAKELOG ) { log << "ERROR! missing array number\n"; }
                return -1;
            }
            musicArray[cmd_number]= Mix_LoadMUS( cmd_content );
            if( musicArray[cmd_number] == NULL )
            {
                if( MAKELOG ) { log << "ERROR! cannot open file : " << cmd_content << "\n"; }
                return -1;
            }
            else
            {
                if( MAKELOG ) { log << "Music " << cmd_number << " Loaded : " << cmd_content << "\n"; }
            }
        }
        fclose( fp );
    }

    return 0;
}

////////////////////////////////////////////
// LoadChunkArray                         //
// loads chunks from CHUNK_ARRAY_FILENAME //
// it is called by Initialize()           //
int SoundControl::LoadChunkArray ( void )
////////////////////////////////////////////
{
    // variables to read image list (CHUNK_ARRAY_FILENAME)
    FILE* fp;
    int cmd_category= 0;
    int cmd_number= 0;
    char cmd_content[1024];

    LogWriter log;

    // read CHUNK_ARRAY_FILENAME
    fp= fopen( CHUNK_ARRAY_FILENAME, "rt" );
    // check if the list file does exist
    if( fp == NULL )
    {
        log << "ERROR! cannot open file : " << CHUNK_ARRAY_FILENAME << "\n";
        return -1;
    }
    else
    {
        Parser parser;
        while(1)
        {
            if( feof( fp ) != 0 )
                break;
            parser.DecodeLine( fp, &cmd_category, &cmd_number, cmd_content );
            if( cmd_category != EXTERNCMD_CHUNK_FILE )
                continue;
            if( cmd_number >= CHUNK_ARRAY_LENGTH )
            {
                if( MAKELOG ) { log << "ERROR! not enough chunk array : " << cmd_number << "\n"; }
                return -1;
            }
            if( cmd_number == -1 )
            {
                if( MAKELOG ) { log << "ERROR! missing array number\n"; }
                return -1;
            }
            chunkArray[cmd_number]= Mix_LoadWAV( cmd_content );
            if( chunkArray[cmd_number] == NULL )
            {
                if( MAKELOG ) { log << "ERROR! cannot open file : " << cmd_content << "\n"; }
                return -1;
            }
            else
            {
                if( MAKELOG ) { log << "Chunk " << cmd_number << " Loaded : " << cmd_content << "\n"; }
            }
        }
        fclose( fp );
    }

    return 0;
}

////////////////////////////////////////////
// Unloads music array                    //
// it is called by Close()                //
void SoundControl::UnloadMusicArray ( void )
////////////////////////////////////////////
{
    for( int i= 0 ; i < MUSIC_ARRAY_LENGTH ; i++ )
    {
        if( this->musicArray[i] != NULL )
            Mix_FreeMusic( this->musicArray[i] );
    }
    return;
}

////////////////////////////////////////////
// Unloads chunk array                    //
// it is called by Close()                //
void SoundControl::UnloadChunkArray ( void )
////////////////////////////////////////////
{
    for( int i= 0 ; i < CHUNK_ARRAY_LENGTH ; i++ )
    {
        if( this->chunkArray[i] != NULL )
            Mix_FreeChunk( this->chunkArray[i] );
    }
    return;
}

///////////////////////////////////////////////
// PlayMusic                                 //
// pick a music from the array and play it   //
void SoundControl::PlayMusic( const int index )
///////////////////////////////////////////////
{
    if( index >= MUSIC_ARRAY_LENGTH )
        return;
    if( musicArray[index] == NULL)
        return;

    if( stateMusicPlaying == true )
        Mix_HaltMusic();

    Mix_PlayMusic( musicArray[index], -1 );
    stateMusicPlaying= true;
    stateMusicPaused= false;
    return;
}

////////////////////////////////////
// StopMusic                      //
void SoundControl::StopMusic( void )
////////////////////////////////////
{
    if( stateMusicPlaying == false )
        return;

    Mix_HaltMusic();
    stateMusicPlaying= false;
    return;
}

/////////////////////////////////////
// PauseMusic                      //
void SoundControl::PauseMusic( void )
/////////////////////////////////////
{
    if( stateMusicPlaying == false )
        return;
    if( stateMusicPaused == true )
        return;

    Mix_PauseMusic();
    stateMusicPaused= true;
    return;
}

//////////////////////////////////////
// ResumeMusic                      //
void SoundControl::ResumeMusic( void )
//////////////////////////////////////
{
    if( stateMusicPlaying == false )
        return;
    if( stateMusicPaused == false )
        return;

    Mix_ResumeMusic();
    stateMusicPaused= false;
    return;
}

///////////////////////////////////////////////
// PlayChunk                                 //
// pick a chunk from the array and play it   //
void SoundControl::PlayChunk( const int index )
///////////////////////////////////////////////
{
    if( index >= CHUNK_ARRAY_LENGTH )
        return;
    if( chunkArray[index] == NULL)
        return;

    Mix_PlayChannel( -1, chunkArray[index], 0 );
    return;
}

////////////////////////////////
// Initialize Class Variables //
////////////////////////////////
bool SoundControl::stateInitialized= false;
Mix_Music* SoundControl::musicArray[MUSIC_ARRAY_LENGTH]= { NULL, };
Mix_Chunk* SoundControl::chunkArray[CHUNK_ARRAY_LENGTH]= { NULL, };

/* end of file */
