///////////////////////////////////////////////////////////////////////////////
//  Filename       : LogWriter.h                                             //
//                   LogWriter.cpp                                           //
//  Date           : 2009/02/08                                              //
//  Author         : Bak Yeono (bakyeono@gmail.com)                          //
//  Description    : This class writes log.                                  //
///////////////////////////////////////////////////////////////////////////////

#include "LogWriter.h"

////////////////////////////////
// class cunstructor          //
// sets default log filename. //
LogWriter::LogWriter( void )
////////////////////////////////
{
    std::stringstream logFilename;
    logFilename << PROGRAM_TITLE "." << RUNNING_TIME << ".log";
    strcpy( this->logFilename, logFilename.str().c_str() );
}

////////////////////////////////////////////////////
// class cunstructor                              //
// when you want to write another log file,       //
// give the filename's head to this constructor.  //
LogWriter::LogWriter ( const char* logFilenameHead )
////////////////////////////////////////////////////
{
    std::stringstream logFilename;
    logFilename << PROGRAM_TITLE "." << logFilenameHead << "." << RUNNING_TIME << ".log";
    strcpy( this->logFilename, logFilename.str().c_str() );
}

//////////////////////////////////////////////////////////////////
// operator <<                                                  //
// writes parameter in log file.                                //
const LogWriter& LogWriter::operator << ( const char* data ) const
//////////////////////////////////////////////////////////////////
{
    if( MAKELOG )
    {
        FILE* fp_log;

        fp_log= fopen( logFilename, "at" );
        fprintf(fp_log, "%s", data );
        fclose( fp_log );
    }

    return *this;
}

/////////////////////////////////////////////////////////////////
// operator <<                                                 //
// writes parameter in log file.                               //
const LogWriter& LogWriter::operator << ( const char data ) const
/////////////////////////////////////////////////////////////////
{
    if( MAKELOG )
    {
        FILE* fp_log;
    
        fp_log= fopen( logFilename, "at" );
        fprintf(fp_log, "%c", data );
        fclose( fp_log );
    }

    return *this;
}

////////////////////////////////////////////////////////////////
// operator <<                                                //
// writes parameter in log file.                              //
const LogWriter& LogWriter::operator << ( const int data ) const
////////////////////////////////////////////////////////////////
{
    if( MAKELOG )
    {
        FILE* fp_log;
    
        fp_log= fopen( logFilename, "at" );
        fprintf(fp_log, "%d", data );
        fclose( fp_log );
    }

    return *this;
}

//////////////////////////////////////////////////////////////////
// operator <<                                                  //
// writes parameter in log file.                                //
const LogWriter& LogWriter::operator << ( const float data ) const
//////////////////////////////////////////////////////////////////
{
    if( MAKELOG )
    {
        FILE* fp_log;

        fp_log= fopen( logFilename, "at" );
        fprintf(fp_log, "%g", data );
        fclose( fp_log );
    }

    return *this;
}

///////////////////////////////////////////////////////////////////
// operator <<                                                   //
// writes parameter in log file.                                 //
const LogWriter& LogWriter::operator << ( const double data ) const
///////////////////////////////////////////////////////////////////
{
    if( MAKELOG )
    {
        FILE* fp_log;

        fp_log= fopen( logFilename, "at" );
        fprintf(fp_log, "%g", data );
        fclose( fp_log );
    }

    return *this;
}

/* end of file */
