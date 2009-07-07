// dotNetInstaller.cpp : definisce i comportamenti delle classi per l'applicazione.
//

#include "stdafx.h"
#include "ConfigFile.h"
#include "dotNetInstaller.h"
#include "dotNetInstallerDlg.h"
#include "InstallerCommandLineInfo.h"
#include "DniMessageBox.h"
#include <Version/Version.h>

// CdotNetInstallerApp

BEGIN_MESSAGE_MAP(CdotNetInstallerApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// costruzione di CdotNetInstallerApp

CdotNetInstallerApp::CdotNetInstallerApp()
	: m_rc(0)
{
	// Inserire l'inizializzazione significativa in InitInstance.
}


// L'unico e solo oggetto CdotNetInstallerApp

CdotNetInstallerApp theApp;


// Inizializzazione di CdotNetInstallerApp

BOOL CdotNetInstallerApp::InitInstance()
{
	// InitCommonControls() � necessario in Windows XP se nel manifesto
	// di un'applicazione � specificato l'utilizzo di ComCtl32.dll versione 6 o successiva per attivare
	// gli stili visuali. In caso contrario, non sar� possibile creare finestre.
	InitCommonControls();

	CWinApp::InitInstance();

	//AfxEnableControlContainer();

	try
	{
		ParseCommandLine(commandLineInfo);

		ApplicationLog.Write(TEXT("-------------------------------------------------------------------"));
		ApplicationLog.Write(TEXT("dotNetInstaller (DNI) started, version "), TEXT(VERSION_VALUE));
		ApplicationLog.Write(TEXT(VERSION_LEGALCOPYRIGHT_VALUE));
		ApplicationLog.Write(TEXT("Operating system: "), DVLib::GetOperatingSystemVersionString().c_str());
		ApplicationLog.Write(TEXT("-------------------------------------------------------------------"));

		std::map<std::wstring, std::wstring>::iterator arg = commandLineInfo.m_componentCmdArgs.begin();
		while(arg != commandLineInfo.m_componentCmdArgs.end())
		{
			ApplicationLog.Write((TEXT("Component arguments: \"") + arg->first + TEXT("\": ")).c_str(), arg->second.c_str());
			arg ++;
		}

        ConfigFile config;
        m_rc = config.Load();
	}
	catch(std::exception& ex)
	{
        DniSilentMessageBox(DVLib::string2wstring(ex.what()).c_str(), MB_OK|MB_ICONSTOP);
		m_rc = -1;
		return false;
	}
	catch(...)
	{
		DniSilentMessageBox(TEXT("Error loading configuration file"), MB_OK|MB_ICONSTOP);
		m_rc = -1;
		return false;
	}


	// Poich� la finestra di dialogo � stata chiusa, restituisce FALSE in modo che l'applicazione
	//  venga terminata, anzich� avviare la message pump dell'applicazione.
	return FALSE;
}

int CdotNetInstallerApp::ExitInstance() 
{
	// ignore the MFC return code, which is typically the last key pressed
	CWinApp::ExitInstance();
	return m_rc;
}