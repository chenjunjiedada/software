// devctrl.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <boost/version.hpp>
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <SetupAPI.h>
#include <cfgmgr32.h>   // cfgmgr32.h ��Microsoft Windows 2000 DDK ��.
#include <NewDev.h>
#pragma comment(lib,"setupapi.lib")
#pragma comment(lib,"newdev.lib")

#include <iostream>
#include <string>

BOOL IsDisableable(DWORD dwDevID, HDEVINFO hDevInfo);
BOOL IsDisabled(DWORD dwDevID, HDEVINFO hDevInfo);
BOOL StateChange(DWORD dwNewState, DWORD dwDevID, HDEVINFO hDevInfo);

std::wstring GUIDToWstring(const GUID* guid) 
{
	wchar_t guid_string[37];
	swprintf(
		guid_string, sizeof(guid_string) / sizeof(guid_string[0]),
		L"%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x",
		guid->Data1, guid->Data2, guid->Data3,
		guid->Data4[0], guid->Data4[1], guid->Data4[2],
		guid->Data4[3], guid->Data4[4], guid->Data4[5],
		guid->Data4[6], guid->Data4[7]);
	return guid_string;
}

std::string lasterror()
{
	DWORD errorCode = GetLastError();
	CHAR buf[512] = { 0 };
	if (FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, errorCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&buf[0], sizeof(buf), NULL) == 0)
	{
		// FormatMessage failed, return the last error code
		sprintf_s(buf, "0x%08X", errorCode);
	}

	return buf;
}



//////////////////////////////////////////////////////////////////////////
// ����豸ע����е�����
//////////////////////////////////////////////////////////////////////////
BOOL GetRegistryProperty(HDEVINFO DeviceInfoSet,
	PSP_DEVINFO_DATA DeviceInfoData,
	ULONG Property,
	PVOID Buffer,
	PULONG Length)
{
	while (!SetupDiGetDeviceRegistryProperty(DeviceInfoSet,
		DeviceInfoData,
		Property,
		NULL,
		(BYTE *)*(TCHAR **)Buffer,
		*Length,
		Length))
	{
		// ���Ȳ��������·��仺����
		if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
		{
			if (*(LPTSTR *)Buffer)
				LocalFree(*(LPTSTR *)Buffer);

			*(LPTSTR *)Buffer = static_cast<LPTSTR>(LocalAlloc(LPTR, *Length));
		}
		else
		{
			return false;
		}
	}

	return (BOOL)(*(LPTSTR *)Buffer)[0];
}

BOOL EnableDevice(DWORD dwDevID, HDEVINFO hDevInfo)
{
	return StateChange(DICS_ENABLE, dwDevID, hDevInfo);
}

BOOL DisableDevice(DWORD dwDevID, HDEVINFO hDevInfo)
{
	return StateChange(DICS_DISABLE, dwDevID, hDevInfo);
}

BOOL ControlDevice(DWORD dwDevID, HDEVINFO hDevInfo)
{
	BOOL bCanDisable;
	bCanDisable = (IsDisableable(dwDevID, hDevInfo) && (!IsDisabled(dwDevID, hDevInfo)));
	
	if (bCanDisable) {
		std::cout << "disable device" << std::endl;
		return DisableDevice(dwDevID, hDevInfo);
	}else {
		std::cout << "enable device" << std::endl;
		return EnableDevice(dwDevID, hDevInfo);
	}
		
}



void EnumNetCards()
{

	DWORD Status, Problem;
	LPTSTR Buffer = NULL;
	DWORD BufSize = 0;

	// ���������豸��Ϣ
	HDEVINFO hDevInfo = SetupDiGetClassDevs(NULL, NULL, 0, DIGCF_PRESENT | DIGCF_ALLCLASSES);

	if (INVALID_HANDLE_VALUE == hDevInfo)
		return;


	SP_DEVINFO_DATA DeviceInfoData = { sizeof(SP_DEVINFO_DATA) };




	//////////////////////////////////////////////////////////////////////////
	// ö���豸
	//////////////////////////////////////////////////////////////////////////
	for (DWORD DeviceId = 0;
	SetupDiEnumDeviceInfo(hDevInfo, DeviceId, &DeviceInfoData);
		DeviceId++)
	{

		// ����豸��״̬
		if (CM_Get_DevNode_Status(&Status, &Problem, DeviceInfoData.DevInst, 0) != CR_SUCCESS)
			continue;


		// ��ȡ�豸����
		TCHAR szDevName[MAX_PATH] = _T("");
		if (GetRegistryProperty(hDevInfo, &DeviceInfoData, SPDRP_CLASS, &Buffer, (PULONG)&BufSize))
		{
			lstrcpyn(szDevName, Buffer, MAX_PATH);
		}


		if (lstrcmp(szDevName, _T("Net")) == 0)
		{
			TCHAR szName[MAX_PATH] = _T("");
			if (GetRegistryProperty(hDevInfo, &DeviceInfoData, SPDRP_ENUMERATOR_NAME, &Buffer, (PULONG)&BufSize))
			{
				lstrcpyn(szName, Buffer, MAX_PATH);
			}

			//std::wcout << szName << std::endl;
			if (lstrcmp(szName, _T("ROOT")) != 0)
			{

				if (GetRegistryProperty(hDevInfo, &DeviceInfoData, SPDRP_DRIVER, &Buffer, (PULONG)&BufSize))
				{
					lstrcpyn(szName, Buffer, MAX_PATH);
					std::wcout << szName << std::endl;
					std::wcout << GUIDToWstring(&(DeviceInfoData.ClassGuid)) << std::endl;
					// ��ȡ�豸����
					if (GetRegistryProperty(hDevInfo, &DeviceInfoData, SPDRP_DEVICEDESC, &Buffer, (PULONG)&BufSize))
					{

						lstrcpyn(szName, Buffer, MAX_PATH);
						std::wcout << szName << std::endl;

						if (wcsstr(szName, L"GBE")) {
							std::wcout << L"uninstall device: " << szName << std::endl;

							BOOL needReboot;
							if ( DiUninstallDevice(NULL,
									hDevInfo,
									&DeviceInfoData,
									0,
									&needReboot
									)) 
							{
								std::wcout << L"uninstall successful" << std::endl;
								if (needReboot)
									std::wcout << L"Need reboot" << std::endl;
								int x;
								std::cin >> x;

								SP_DEVINFO_DATA NewDeviceInfoData;
								std::wcout << GUIDToWstring(&(DeviceInfoData.ClassGuid)) << std::endl;
									SetupDiCreateDeviceInfo(hDevInfo,
										szName,
										&(DeviceInfoData.ClassGuid),
										NULL,
										NULL,
										DICD_INHERIT_CLASSDRVS,
										&NewDeviceInfoData
										);
									std::cout << lasterror() << std::endl;

							}
							else {
								DWORD err = GetLastError();
								std::cout << std::hex << err << std::endl;
							}
						}

						

						/*
						if (ControlDevice(DeviceId, hDevInfo))
						{
							printf("Successful\n");
						}
						else
						{
							printf("FAILED\n");
						}
						*/

					}
				}
			}
		}
	}

	SetupDiDestroyDeviceInfoList(hDevInfo);
}

BOOL StateChange(DWORD dwNewState, DWORD dwDevID, HDEVINFO hDevInfo)
{
	SP_PROPCHANGE_PARAMS PropChangeParams;
	SP_DEVINFO_DATA        DevInfoData = { sizeof(SP_DEVINFO_DATA) };
	SP_DEVINSTALL_PARAMS devParams;

	//��ѯ�豸��Ϣ
	if (!SetupDiEnumDeviceInfo(hDevInfo, dwDevID, &DevInfoData))
	{
		OutputDebugString(L"SetupDiEnumDeviceInfo FAILED");
		return FALSE;
	}

	//�����豸���Ա仯����
	PropChangeParams.ClassInstallHeader.cbSize = sizeof(SP_CLASSINSTALL_HEADER);
	PropChangeParams.ClassInstallHeader.InstallFunction = DIF_PROPERTYCHANGE;
	PropChangeParams.Scope = DICS_FLAG_GLOBAL; //ʹ�޸ĵ����Ա��������е�Ӳ�������ļ�
	PropChangeParams.StateChange = dwNewState;
	PropChangeParams.HwProfile = 0;


	//�ı��豸����
	if (!SetupDiSetClassInstallParams(hDevInfo,
		&DevInfoData,
		(SP_CLASSINSTALL_HEADER *)&PropChangeParams,
		sizeof(PropChangeParams)))
	{
		OutputDebugString(L"SetupDiSetClassInstallParams FAILED");
		return FALSE;
	}


	PropChangeParams.ClassInstallHeader.cbSize = sizeof(SP_CLASSINSTALL_HEADER);
	PropChangeParams.ClassInstallHeader.InstallFunction = DIF_PROPERTYCHANGE;
	PropChangeParams.Scope = DICS_FLAG_CONFIGSPECIFIC;//ʹ�޸ĵ����Ա�����ָ���������ļ�
	PropChangeParams.StateChange = dwNewState;
	PropChangeParams.HwProfile = 0;

	//�ı��豸���Բ����ð�װ����
	if (!SetupDiSetClassInstallParams(hDevInfo,
		&DevInfoData,
		(SP_CLASSINSTALL_HEADER *)&PropChangeParams,
		sizeof(PropChangeParams)) ||
		!SetupDiCallClassInstaller(DIF_PROPERTYCHANGE, hDevInfo, &DevInfoData))
	{
		OutputDebugString(L"SetupDiSetClassInstallParams or SetupDiCallClassInstaller FAILED");
		return TRUE;
	}
	else
	{
		//�ж��Ƿ���Ҫ��������
		devParams.cbSize = sizeof(devParams);
		if (!SetupDiGetDeviceInstallParams(hDevInfo, &DevInfoData, &devParams))
		{
			OutputDebugString(L"SetupDiGetDeviceInstallParams FAILED");
			return FALSE;
		}

		if (devParams.Flags & (DI_NEEDRESTART | DI_NEEDREBOOT))
		{
			OutputDebugString(L"Need Restart Computer");
			return TRUE;
		}
		return TRUE;
	}
}


BOOL IsDisableable(DWORD dwDevID, HDEVINFO hDevInfo)
{
	SP_DEVINFO_DATA DevInfoData = { sizeof(SP_DEVINFO_DATA) };
	DWORD    dwDevStatus, dwProblem;
	if (!SetupDiEnumDeviceInfo(hDevInfo, dwDevID, &DevInfoData))
	{
		OutputDebugString(L"SetupDiEnumDeviceInfo FAILED");
		return FALSE;
	}
	//��ѯ�豸״̬
	if (CM_Get_DevNode_Status(&dwDevStatus, &dwProblem, DevInfoData.DevInst, 0) != CR_SUCCESS)
	{
		OutputDebugString(L"CM_GET_DevNode_Status FAILED");
		return FALSE;
	}
	return ((dwDevStatus & DN_DISABLEABLE) && (dwProblem != CM_PROB_HARDWARE_DISABLED));
}

BOOL IsDisabled(DWORD dwDevID, HDEVINFO hDevInfo)
{
	SP_DEVINFO_DATA DevInfoData = { sizeof(SP_DEVINFO_DATA) };
	DWORD    dwDevStatus, dwProblem;
	if (!SetupDiEnumDeviceInfo(hDevInfo, dwDevID, &DevInfoData))
	{
		OutputDebugString(L"SetupDiEnumDeviceInfo FAILED");
		return FALSE;
	}

	//��ѯ�豸״̬
	if (CM_Get_DevNode_Status(&dwDevStatus, &dwProblem, DevInfoData.DevInst, 0) != CR_SUCCESS)
	{
		OutputDebugString(L"CM_GET_DevNode_Status FAILED");
		return FALSE;
	}
	return ((dwDevStatus & DN_HAS_PROBLEM) && (dwProblem == CM_PROB_DISABLED));
}

int main(int argc, char* argv[])
{
	std::cout << "Boost version: " << std::hex
		<< ((BOOST_VERSION >> 20) & 0xF)
		<< "."
		<< ((BOOST_VERSION >> 8) & 0xFFF)
		<< "."
		<< (BOOST_VERSION & 0xFF)
		<< std::endl;
	return 0;

	std::locale::global(std::locale(""));
	EnumNetCards();
	system("pause");
	return 0;
}