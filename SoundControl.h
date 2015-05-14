///////////////////////////////////////////////////////////////////////////////
//  Filename       : SoundControl.h                                          //
//                   SoundControl.cpp                                        //
//  Date           : 2009/02/08                                              //
//  Author         : Bak Yeono (bakyeono@gmail.com)                          //
//  Description    : This class controls all musics and sound effects        //
//                   by using SDL_mixer library.                             //
///////////////////////////////////////////////////////////////////////////////

#ifndef __SOUNDCONTROL_H__
#define __SOUNDCONTROL_H__

#include <SDL/SDL_mixer.h>
#include "ProgramInfo.h"
#include "LogWriter.h"
#include "Parser.h"

///////////////////////////////////
// Muisc IDs Used By Music Array //
///////////////////////////////////
enum _MUSIC_ARRAY_ID
{
	MUSIC_MAINMENU= 0,
	MUSIC_STAGE0= 0,
	MUSIC_STAGE1= 0,
	MUSIC_STAGE2= 0,
	MUSIC_STAGE3= 0,
	MUSIC_STAGE4= 0,
	MUSIC_STAGE5= 0,
	MUSIC_STAGE6= 0,
	MUSIC_STAGE7= 0,
	MUSIC_STAGE8= 0,
	MUSIC_STAGE9= 0,
	MUSIC_STAGE10= 0,
	MUSIC_STAGE11= 0,
	MUSIC_STAGE12= 0,
	MUSIC_STAGE13= 0,
	MUSIC_STAGE14= 0,
	MUSIC_STAGE15= 0,
	MUSIC_STAGE16= 0,
	MUSIC_STAGE17= 0,
	MUSIC_STAGE18= 0,
	MUSIC_STAGE19= 0,
};

//////////////////
class SoundControl
//////////////////
{
private:
	static bool stateInitialized;

	static Mix_Music* musicArray[MUSIC_ARRAY_LENGTH];
	static Mix_Chunk* chunkArray[CHUNK_ARRAY_LENGTH];

	bool stateMusicPlaying;
	bool stateMusicPaused;

	int LoadMusicArray ( void );
	int LoadChunkArray ( void );
	void UnloadMusicArray ( void );
	void UnloadChunkArray ( void );

public:
	SoundControl( void );
	~SoundControl( void );

	int Initialize ( void );
	void Close ( void );

	void PlayMusic( const int index );
	void StopMusic( void );
	void PauseMusic( void );
	void ResumeMusic( void );
	void PlayChunk( const int index );
};

#endif
/* end of file */
