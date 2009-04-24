#include "StdAfx.h"
#include "CmdComponent.h"

cmd_component::cmd_component()
{

}

bool cmd_component::Exec()
{
    if (QuietInstall.IsSilent() && command_silent.GetLength() > 0)
    {
		ApplicationLog.Write(TEXT("Executing: "), command_silent);
	    return DVLib::ExecCmd(command_silent, &m_process_info);
    }
    else
    {
		ApplicationLog.Write(TEXT("Executing: "), command);
	    return DVLib::ExecCmd(command, &m_process_info);
    }
};

