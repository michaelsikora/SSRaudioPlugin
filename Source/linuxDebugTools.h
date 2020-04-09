/*
  ==============================================================================

    linuxDebugTools.h
    Created: 8 Apr 2020 7:00:26am
    Author:  michaelsikora

  ==============================================================================
*/

#pragma once

#include <string>
#include <stdlib.h>

inline void printDebugMessage(std::string message, int sleepTime)
{
    std::string dbgCmd = "gnome-terminal -x sh -c 'printf '";
    dbgCmd += message;
    dbgCmd += "'; sleep ";
    dbgCmd += std::to_string(sleepTime);
    dbgCmd += "; exit'";
    int exit_status = system(dbgCmd.c_str());
}
