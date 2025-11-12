#ifndef LOGGER_H
#define LOGGER_H

#include <string>
using namespace std;

/**
 * Simple logger, providing four severity levels - INFO, WARNING, ERROR and DEBUG.
 * DEBUG logs are emitted only in debug builds.
 * Can be muted to suppress all logging output and unmuted to enable logging again.
 */
class Logger{
public:  
    enum Level{
        INFO,
        WARNING,
        ERROR,
        DEBUG
    };
    
    // set minlevel to level
    void setMinimumLoggingLevel(Level level); 
    // write message if minlevel is lower than level of message
    void log(const string &h, Level level) const; 
    // set mute to true
    void mute(); 
    // set mute to false
    void unmute(); 

    private:
    bool m_muted = false;
    Level m_minlevel = INFO;

    //write level to string
    string leveltostring(Level level) const; 

};

#endif // LOGGER_H
