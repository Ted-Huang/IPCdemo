#include <StdAfx.h>
#include "Utility.h"

BOOL CUtility::GetIP(CString& strIP)
{
	DWORD dwSize = 0;
	DWORD dwErr;
	dwErr = GetIpAddrTable(NULL, &dwSize, FALSE);
	if (dwErr != ERROR_INSUFFICIENT_BUFFER)
		return FALSE;

	BYTE *pData = new BYTE[dwSize];
	dwErr = GetIpAddrTable((PMIB_IPADDRTABLE)pData, &dwSize, TRUE);
	if (dwErr != NO_ERROR)
		return FALSE;

	MIB_IPADDRTABLE *pTbl = (PMIB_IPADDRTABLE)pData;
	for (int i = 0; i < (int)pTbl->dwNumEntries; i++) {
		MIB_IPADDRROW* pTblEnt = &pTbl->table[i];

		if (pTblEnt->dwAddr == 0)
			continue;	// bypass 0

		if (pTblEnt->dwAddr == 0x0100007f)
			continue;	// bypass 127.0.0.1 (loopback)

		BYTE* pbAddr = (BYTE*)&pTblEnt->dwAddr;
		TCHAR szAddr[128];
		strIP.Format(_T("%d.%d.%d.%d "), pbAddr[0], pbAddr[1], pbAddr[2], pbAddr[3]);
	}
	if (pData) {
		delete[]pData;
		pData = 0;
	}
	return TRUE;
}