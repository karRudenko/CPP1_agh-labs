#include "Logger.h"
#include <iostream>
#include <string>
using namespace std;

void Logger::setMinimumLoggingLevel(Level level){
    m_minlevel = level;
}

void Logger::log(const string &message, Level level) const {
    if(m_muted) return;
    if(level < m_minlevel) return;
    
#ifdef NDEBUG
    if (level == DEBUG) return;
#endif

    std::cout << "[" << leveltostring(level) << "] " << message << std::endl;
}

string Logger::leveltostring(Level level) const {
    switch(level){
        case INFO: return "INFO";
        case WARNING: return "WARNING";
        case ERROR: return "ERROR";
        case DEBUG: return "DEBUG";
        default: return "UNKNOWN";
    }
}

void Logger::mute(){
    m_muted = true;
}

void Logger::unmute(){
    m_muted = false;
}
