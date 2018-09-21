#pragma once

#define WM_IPC_MSG					WM_APP + 1
//#define WM_WP_TEST					WM_USER + 1 
//#define WM_WP_SHAREDMEMORY			WM_USER + 2

enum Msg_Cmd{
	Cmd_Test,
	Cmd_SharedMemory,

};

enum Msg_SubCmd{
	SubCmd_Test,	//µL¥Î
	SubCmd_SM_CString,

};
