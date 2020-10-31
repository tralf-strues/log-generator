#include <assert.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include "log_generator.h"

FILE* logFile     = NULL;
bool  initialized = false;

//-----------------------------------------------------------------------------
//! Chacks whether or not color has a supporting color name.
//!
//! @param [in]  color  
//!
//! @return whether or not color is valid.
//-----------------------------------------------------------------------------
bool isValidColor(const char* color)
{
    assert(color != NULL);

    return strcmp(color, LOG_COLOR_BLACK)  == 0 ||
           strcmp(color, LOG_COLOR_BLUE)   == 0 ||
           strcmp(color, LOG_COLOR_GRAY)   == 0 ||
           strcmp(color, LOG_COLOR_GREEN)  == 0 ||
           strcmp(color, LOG_COLOR_PINK)   == 0 ||
           strcmp(color, LOG_COLOR_RED)    == 0 ||
           strcmp(color, LOG_COLOR_YELLOW) == 0;
}

//-----------------------------------------------------------------------------
//! Initializes the log - opens the log file and writes the header.
//!
//! @return whether or not initialization has been successful. Returns false if
//!         log has already been initialized.
//-----------------------------------------------------------------------------
bool initLog()
{
    if (initialized)
        return false;

    logFile = fopen(LOG_FILE_NAME, "w");
    if (logFile == NULL)
        return false;

    fprintf(logFile, "<!DOCTYPE html>\n<html>\n<body>\n");

    initialized = true;
    return true;
}

//-----------------------------------------------------------------------------
//! Closes the log - closes the log file and writes the footer.
//!
//! @return whether or not closing has been successful. Returns false if
//!         log hasn't been initialized yet.
//-----------------------------------------------------------------------------
bool closeLog()
{
    if (!initialized)
        return false;

    fprintf(logFile, "\n</body>\n</html>");

    if (fclose(logFile) == EOF)
        return false;

    initialized = false;
    return true;
}

//-----------------------------------------------------------------------------
//! @return whether or not log has been initialized.
//-----------------------------------------------------------------------------
bool isLogInitialized()
{
    return initialized;
}

//-----------------------------------------------------------------------------
//! Logs message as one paragraph.
//!
//! @param [in]  message
//! @param [in]  color   color of the entire message to be logged
//! @param [in]  ...
//!
//-----------------------------------------------------------------------------
void logMessage(const char* message, const char* color, ...)
{
    assert(message != NULL);
    assert(color   != NULL);

    if (!initialized)
        return;

    va_list valist;
    va_start(valist, color);

    logWriteMessageStart(color);
    vfprintf(logFile, message, valist);
    logWriteMessageEnd();

    va_end(valist);
}

//-----------------------------------------------------------------------------
//! Logs string as a continuation of what has been logged already. Default 
//! color is black.
//!
//! @param [in]  string
//! @param [in]  ...
//-----------------------------------------------------------------------------
void logWrite(const char* string, ...)
{
    assert(string != NULL);

    if (!initialized)
        return;

    va_list valist;
    va_start(valist, string);

    vfprintf(logFile, string, valist);

    va_end(valist);
}

//-----------------------------------------------------------------------------
//! Logs string as a continuation of what has been logged already. 
//!
//! @param [in]  string
//! @param [in]  color   color of the entire string to be logged
//! @param [in]  ...
//-----------------------------------------------------------------------------
void logWrite(const char* string, const char* color, ...)
{
    assert(string != NULL);
    assert(color  != NULL);

    if (!initialized)
        return;

    va_list valist;
    va_start(valist, color);

    if (!isValidColor(color))
        color = LOG_COLOR_BLACK;

    fprintf (logFile, "<span style=\"color:%s;\">", color);
    vfprintf(logFile, string, valist);
    fprintf (logFile, "</span>");

    va_end(valist);
}

//-----------------------------------------------------------------------------
//! Starts a new paragraph inside which to write next. Supposed to be followed 
//! by a sequence of logWrite calls and then by logWriteMessageEnd.
//!
//! @param [in]  color color of the entire paragraph, though can be changed for
//!                    individual paragraph parts by calling logWrite with
//!                    specified color.
//-----------------------------------------------------------------------------
void logWriteMessageStart(const char* color)
{
    if (!initialized)
        return;

    if (!isValidColor(color))
        color = LOG_COLOR_BLACK;

    fprintf (logFile, "\n<pre style=\"color:%s;\">\n", color);
}

//-----------------------------------------------------------------------------
//! Ends the current paragraph. Supposed to be called after 
//! logWriteMessageStart and some sequence of logWrite calls.
//-----------------------------------------------------------------------------
void logWriteMessageEnd()
{
    if (!initialized)
        return;

    fprintf (logFile, "\n</pre>\n");
}

//-----------------------------------------------------------------------------
//! Converts int to string. 
//!
//! @param [in]  value   value to be converted
//! @param [out] str     string to which to write result
//!
//! @return str or NULL on failure.
//-----------------------------------------------------------------------------
char* intToStr (int value, char* str)
{
    if (str == NULL)
        return NULL;

    sprintf(str, "%d", value);

    return str;
}