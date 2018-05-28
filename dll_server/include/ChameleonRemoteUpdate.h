#pragma once
//#include "stdafx.h"

#ifdef CHAMELEONREMOTEUPDATE_EXPORTS
#define ROSEEKUPDATEUTIL_API __declspec(dllexport)
#else
#define ROSEEKUPDATEUTIL_API __declspec(dllimport)
#endif

#define WM_MSG_UPDATE_MESSAGEOUT	(WM_USER+11234)
#define WM_MSG_UPDATE_PROCESS		(WM_USER+11235)
#define WM_MSG_UPDATE_FINISH		(WM_USER+11236)


typedef struct _common_request
{
	DWORD        cmd_id;
	DWORD        append_data_len;
}common_request_t;

const int MAX_STATUS_DESCRIPTION_LEN = 1024;
typedef struct _common_response
{
	DWORD        id;
	INT32        status;
	char         status_description[MAX_STATUS_DESCRIPTION_LEN];
	DWORD        append_data_len;
}common_response_t;

#ifdef __cplusplus
extern "C" {
#endif
	ROSEEKUPDATEUTIL_API int Roseek_CMRemoteUpdate(const char* strFileName,const char* chUserName, const char* chPassword,const char* pszTargetIP, WORD wTargetPort,BOOL bIsNeedVerify, const char* strVerifyCode, HWND hWndMsg,int language);
#ifdef __cplusplus
}
#endif
