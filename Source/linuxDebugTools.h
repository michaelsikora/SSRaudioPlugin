/*
  ==============================================================================

    linuxDebugTools.h
    Created: 8 Apr 2020 7:00:26am
    Author:  michaelsikora
    
    Utility functions for debugging on linux.

  ==============================================================================
*/

#pragma once

#include <string>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <ctime>

// opens a new terminal window to display the passed string. closes the window after "sleepTime" seconds.
inline void printDebugMessage(std::string message, int sleepTime)
{
    std::string dbgCmd = "gnome-terminal -x sh -c 'printf '";
    dbgCmd += message;
    dbgCmd += "'; sleep ";
    dbgCmd += std::to_string(sleepTime);
    dbgCmd += "; exit'";
    int exit_status = system(dbgCmd.c_str());
}

// prints the passed string to a new line of the debug log text file. 
inline int printDebugFile(std::string message)
{
    std::time_t systemTime = std::time(nullptr);
    std::string systemTimeString = std::asctime(std::localtime(&systemTime));
    systemTimeString.pop_back();
    
    std::ofstream debugFile;
    debugFile.open("opt/SoundScapeRenderer/debugLog.txt", std::ios_base::app);
    debugFile << systemTimeString << " : " << message << std::endl;
    debugFile.close();
    return 0;
}