///////////////////////////////////////////////////////////////////////////////
//  Filename       : GraphicControl.h                                        //
//                   GraphicControl.cpp                                      //
//  Date           : 2009/02/08                                              //
//  Author         : Bak Yeono (bakyeono@gmail.com)                          //
//  Description    : This core class controls most graphic & unicode output  //
//                   by using libraries such as SDL, SDL_image and SLD_ttf.  //
///////////////////////////////////////////////////////////////////////////////

#include "GraphicControl.h"

//////////////////////////////////////
// Constructor                      //
GraphicControl::GraphicControl( void )
//////////////////////////////////////
{
}

///////////////////////////////////////
// Destructor                        //
GraphicControl::~GraphicControl( void )
///////////////////////////////////////
{
}

////////////////////////////////////////////
// Initialize                             //
// it needs to be called by main function,//
// during program initializing time       //
// but, do it only one time!              //
////////////////////////////////////////////
int GraphicControl::Initialize( void )
{
    if( stateInitialized == true )
        return 0;

    //screen= SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_FULLSCREEN );
    screen= SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );
    if( screen == NULL )
        return -1;
    if( LoadImageArray() == -1 )
        return -1;
    if ( LoadFontArray() == -1 )
        return -1;
    stateInitialized= true;
    
    return 0;
}

//////////////////////////////////////////
// Close                                //
// needs to be called by main function, //
// before close the program             //
//////////////////////////////////////////
void GraphicControl::Close( void )
{
    if( stateInitialized == false )
        return;

    UnloadImageArray();
    UnloadFontArray();
    SDL_FreeSurface( screen );
    stateInitialized= false;

    return;
}

//////////////////////////////////////////
// LoadImageArray                       //
// loads images from IMAGE_ARRAY_FILENAME/
// it is called by Initialize()         //
int GraphicControl::LoadImageArray( void )
//////////////////////////////////////////
{
    // variables to read image list (IMAGE_ARRAY_FILENAME)
    FILE* fp;
    int cmd_category= 0;
    int cmd_number= 0;
    char cmd_content[1024];

    LogWriter log;

    // read IMAGE_ARRAY_FILENAME
    fp= fopen( IMAGE_ARRAY_FILENAME, "rt" );
    // check if the list file does exist
    if( fp == NULL )
    {
        if( MAKELOG ) { log << "ERROR! cannot open file : " << IMAGE_ARRAY_FILENAME << "\n"; }
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
            if( cmd_category != EXTERNCMD_IMAGE_FILE )
                continue;
            if( cmd_number >= IMAGE_ARRAY_LENGTH )
            {
                if( MAKELOG ) { log << "ERROR! not enough image array : " << cmd_number << "\n"; }
                return -1;
            }
            if( cmd_number == -1 )
            {
                if( MAKELOG ) { log << "ERROR! missing array number\n"; }
                return -1;
            }
            imageArray[cmd_number]= LoadImage( cmd_content );
            if( imageArray[cmd_number] == NULL )
            {
                if( MAKELOG ) { log << "ERROR! cannot open file : " << cmd_content << "\n"; }
                return -1;
            }
            else
            {
                if( MAKELOG ) { log << "Image " << cmd_number << " Loaded : " << cmd_content << "\n"; }
            }
        }
        fclose( fp );
    }

    return 0;
}

/////////////////////////////////////////
// LoadFontArray                       //
// loads fonts from FONT_ARRAY_FILENAME//
// it is called by Initialize()        //
int GraphicControl::LoadFontArray( void )
/////////////////////////////////////////
{
    // variables to read font list (FONT_ARRAY_FILENAME)
    FILE* fp;
    int cmd_category= 0;
    int cmd_number= 0;
    char cmd_content[1024];

    LogWriter log;

    // read FONT_ARRAY_FILENAME
    fp= fopen( FONT_ARRAY_FILENAME, "rt" );
    // check if the list does exist
    if( fp == NULL )
    {
        if( MAKELOG ) { log << "ERROR! cannot open file : " << FONT_ARRAY_FILENAME << "\n"; }
        return -1;
    }
    else
    {
        Parser parser;
        // a temporary array to remember the filenames and sizes of fonts
        char tempArrForFontNames[ FONT_ARRAY_LENGTH ][ 1024 ]= { "" };
        int tempArrForFontSizes[ FONT_ARRAY_LENGTH ]= { 0 };

        // save datas to the temp array
        while(1)
        {
            if( feof( fp ) != 0 )
                break;
            parser.DecodeLine( fp, &cmd_category, &cmd_number, cmd_content );
            if( cmd_category != EXTERNCMD_FONT_FILE && cmd_category !=  EXTERNCMD_FONT_SIZE )
                continue;
            if( cmd_number >= FONT_ARRAY_LENGTH )
            {
                if( MAKELOG ) { log << "ERROR! not enough font array : " << cmd_number << "\n"; }
                return -1;
            }
            if( cmd_number == -1 )
            {
                if( MAKELOG ) { log << "ERROR! missing array number\n"; }
                return -1;
            }
            if( cmd_category == EXTERNCMD_FONT_FILE )
            {
                strcpy( tempArrForFontNames[cmd_number], cmd_content );
            }
            else if( cmd_category == EXTERNCMD_FONT_SIZE )
                tempArrForFontSizes[cmd_number]= atoi( cmd_content );
        }
        fclose( fp );
        
        // load fonts following the datas in temp array
        for( int i= 0 ; i < FONT_ARRAY_LENGTH ; i++ )
        {
            if( tempArrForFontNames[i][0] == '\0' || tempArrForFontSizes[i] == 0 )
                continue;

            fontArray[i]= TTF_OpenFont( tempArrForFontNames[i], tempArrForFontSizes[i] );
            if( fontArray[i] == NULL )
            {
                if( MAKELOG ) { log << "ERROR! cannot open file : " << tempArrForFontNames[i] << "\n"; }
                return -1;
            }
            else
            {
                if( MAKELOG ) { log << "Font " << i << " Loaded : " << tempArrForFontNames[i] << "\n"; }
            }
        }
    }

    return 0;
}

/////////////////////////////////////////////
// UnloadImageArray                        //
// it is called by Close()                 //
void GraphicControl::UnloadImageArray( void )
/////////////////////////////////////////////
{
    for( int i= 0 ; i < IMAGE_ARRAY_LENGTH ; i++ )
    {
        if( imageArray[i] != NULL )
            SDL_FreeSurface( imageArray[i] );
    }
    return;
}

////////////////////////////////////////////
// UnloadFontArray                        //
// it is called by Close()                //
void GraphicControl::UnloadFontArray( void )
////////////////////////////////////////////
{
    for( int i= 0 ; i < FONT_ARRAY_LENGTH ; i++ )
    {
        if( fontArray[i] != NULL )
            TTF_CloseFont( fontArray[i] );
    }
    return;
}

//////////////////////////////////////////////////////////////
// LoadImage                                                //
// load an image and adapts its format to the screen        //
// not allowed to use by hands                              //
SDL_Surface* GraphicControl::LoadImage( const char* filename )
//////////////////////////////////////////////////////////////
{
    SDL_Surface* imageLoaded= NULL;
    SDL_Surface* imageOptimized= NULL;

    imageLoaded= IMG_Load( filename );
    if( imageLoaded == NULL )
        return NULL;
    imageOptimized= SDL_DisplayFormatAlpha( imageLoaded );
    SDL_FreeSurface( imageLoaded );

    return imageOptimized;
}

////////////////////////////////////////////////////////////////
// PrintImage                                                 //
// take an image from the array,                              //
// and print it at ( x, y ) of the screen                     //
void GraphicControl::PrintImage( int imageNumber, int x, int y )
////////////////////////////////////////////////////////////////
{
    SDL_Rect offset;

    offset.x= x;
    offset.y= y;
    SDL_BlitSurface( imageArray[ imageNumber ], NULL, screen, &offset );

    return;
}

///////////////////////////////////////////////////////////////////////
// PrintText                                                         //
// it prints texts                                                   //
void GraphicControl::PrintText
    ( const char* text, int fontNumber, SDL_Color color, int x, int y )
///////////////////////////////////////////////////////////////////////
{
    SDL_Surface* shadeSurface= NULL;
    SDL_Surface* textSurface= NULL;
    SDL_Rect shadeOffset;
    SDL_Rect offset;
    shadeOffset.x= x+1;
    shadeOffset.y= y+1;
    offset.x= x;
    offset.y= y;

    shadeSurface= TTF_RenderText_Blended( fontArray[ fontNumber ], text, colorBlack );
    SDL_BlitSurface( shadeSurface, NULL, screen, &shadeOffset );
    SDL_FreeSurface( shadeSurface );
    textSurface= TTF_RenderText_Blended( fontArray[ fontNumber ], text, color );
    SDL_BlitSurface( textSurface, NULL, screen, &offset );
    SDL_FreeSurface( textSurface );

    return;
}

////////////////////////////////////////////////////////////////////////
// PrintUTF8                                                          //
// it prints unicode(UTF-8) texts                                     //
void GraphicControl::PrintUTF8
    ( const Uint8* text, int fontNumber, SDL_Color color, int x, int y )
////////////////////////////////////////////////////////////////////////
{
    SDL_Surface* shadeSurface= NULL;
    SDL_Surface* textSurface= NULL;
    SDL_Rect shadeOffset;
    SDL_Rect offset;
    shadeOffset.x= x+1;
    shadeOffset.y= y+1;
    offset.x= x;
    offset.y= y;

    shadeSurface= TTF_RenderUTF8_Blended( fontArray[ fontNumber ], (char*) text, colorBlack );
    SDL_BlitSurface( shadeSurface, NULL, screen, &shadeOffset );
    SDL_FreeSurface( shadeSurface );
    textSurface= TTF_RenderUTF8_Blended( fontArray[ fontNumber ], (char*) text, color );
    SDL_BlitSurface( textSurface, NULL, screen, &offset );
    SDL_FreeSurface( textSurface );

    return;
}

//////////////////////////////////////////////////////////////////////////
// PrintUNICODE                                                         //
// it prints unicode(UTF-16) texts                                      //
void GraphicControl::PrintUNICODE
    ( const wchar_t* text, int fontNumber, SDL_Color color, int x, int y )
//////////////////////////////////////////////////////////////////////////
{
    SDL_Surface* shadeSurface= NULL;
    SDL_Surface* textSurface= NULL;
    SDL_Rect shadeOffset;
    SDL_Rect offset;
    shadeOffset.x= x+1;
    shadeOffset.y= y+1;
    offset.x= x;
    offset.y= y;

    shadeSurface= TTF_RenderUNICODE_Blended( fontArray[ fontNumber ], (Uint16*) text, colorBlack );
    SDL_BlitSurface( shadeSurface, NULL, screen, &shadeOffset );
    SDL_FreeSurface( shadeSurface );
    textSurface= TTF_RenderUNICODE_Blended( fontArray[ fontNumber ], (Uint16*) text, color );
    SDL_BlitSurface( textSurface, NULL, screen, &offset );
    SDL_FreeSurface( textSurface );

    return;
}

/////////////////////////////////
// Flip                        //
// refreshs the screen         //
void GraphicControl::Flip( void )
/////////////////////////////////
{
    SDL_Flip( screen );
    return;
}

//////////////////////////////////////////////////////////////
// PrintTile                                                //
// it prints a tile                                         //
void GraphicControl::PrintTile( int tileNumber, int x, int y )
//////////////////////////////////////////////////////////////
{
    SDL_Rect tileRect, offset;

    tileRect.x= ( tileNumber * TILE_WIDTH );
    tileRect.y= 0;
    tileRect.w= TILE_WIDTH;
    tileRect.h= TILE_HEIGHT;
    offset.x= GAMEBOARD_POSX + ( x * TILE_WIDTH );
    offset.y= GAMEBOARD_POSY + ( y * TILE_HEIGHT );
    offset.w= TILE_WIDTH;
    offset.h= TILE_HEIGHT;
    SDL_BlitSurface( imageArray[ IMAGE_TILESET0 ], &tileRect, screen, &offset );

    return;
}

////////////////////////////////
// Initialize Class Variables //
////////////////////////////////
bool GraphicControl::stateInitialized= false;
SDL_Surface* GraphicControl::imageArray[IMAGE_ARRAY_LENGTH]= { NULL, };
TTF_Font* GraphicControl::fontArray[FONT_ARRAY_LENGTH]= { NULL, };
SDL_Surface* GraphicControl::screen= NULL;

/* end of file */
