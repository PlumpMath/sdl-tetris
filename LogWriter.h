///////////////////////////////////////////////////////////////////////////////
//  Filename       : LogWriter.h                                             //
//                   LogWriter.cpp                                           //
//  Date           : 2009/02/08                                              //
//  Author         : Bak Yeono (bakyeono@gmail.com)                          //
//  Description    : This class writes log.                                  //
///////////////////////////////////////////////////////////////////////////////

#ifndef __LOGWRITER_H__
#define __LOGWRITER_H__

#include <stdio.h>
#include <sstream>
#include "ProgramInfo.h"

///////////////
class LogWriter
///////////////
{
    private:
        char logFilename[1024];
    
    public:
        LogWriter ( void );
        LogWriter ( const char* logFilename );
        const LogWriter& operator << ( const char* data ) const;
        const LogWriter& operator << ( const char data ) const;
        const LogWriter& operator << ( const int data ) const;
        const LogWriter& operator << ( const float data ) const;
        const LogWriter& operator << ( const double data ) const;
};

#endif
/* end of file */
