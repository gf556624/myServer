#ifndef _CT1NETCMDPROTOCOL_H
#define _CT1NETCMDPROTOCOL_H

#ifdef WPNETCMDPROTOCOL_EXPORTS
#define ROSEEKNETCMD_API __declspec(dllexport)
#else
#define ROSEEKNETCMD_API __declspec(dllimport)
#endif



typedef int (CALLBACK NetCBProc)(const char* command, char* backmessge, int size);

#ifdef __cplusplus
extern "C" {
#endif
	ROSEEKNETCMD_API const char * Roseek_NetCmd_GetModuleInfo();
	ROSEEKNETCMD_API PVOID Roseek_NetCmd_Open(const char* username, const char* password, int cmdport, int infoport, int updateport, int buffSize, int timeout, NetCBProc *pFunc);
	ROSEEKNETCMD_API int Roseek_NetCmd_Close(PVOID dest);
	ROSEEKNETCMD_API int Roseek_NetCmd_GetConnState(PVOID dest);
#ifdef __cplusplus
}
#endif

#endif






