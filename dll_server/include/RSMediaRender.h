// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 RSMEDIARENDER_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// RSMEDIARENDER_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#ifdef RSMEDIARENDER_EXPORTS
#define RSMEDIARENDER_API __declspec(dllexport)
#else
#define RSMEDIARENDER_API __declspec(dllimport)
#endif

#define ROSEEK_RENDER_BY_GDI	1
#define ROSEEK_RENDER_BY_DDRAW	2

#define ROSEEK_VIDEO_RGB24	1
#define ROSEEK_VIDEO_RGB32	2
#define ROSEEK_VIDEO_YV12	3
#define ROSEEK_VIDEO_YUY2	4

#ifdef __cplusplus
extern "C" {
#endif
RSMEDIARENDER_API PVOID ROSEEK_MRCreateOne(int nMediaMode);//创建一个显示模块
RSMEDIARENDER_API void	ROSEEK_MRClose(PVOID dest);//销毁一个显示模块

RSMEDIARENDER_API BOOL	ROSEEK_MRSetVideoFormat(PVOID dest, int nType, int nWidth, int nHeight);//设置显示模块要接收的图像数据格式
RSMEDIARENDER_API BOOL	ROSEEK_MRActiveVideoRender(PVOID dest);//激活显示模块，创建显示所要的资源
RSMEDIARENDER_API void	ROSEEK_MRDeactiveVideoRender(PVOID dest);//停止显示模块，关闭显示所要的资源
RSMEDIARENDER_API BOOL	ROSEEK_MRLockVideoBuffer(PVOID dest, void **ppBuf, int *pnPitch);//获取显示模块显存指针，同时锁定此块内存
RSMEDIARENDER_API BOOL	ROSEEK_MRUnlockVideoBuffer(PVOID dest);//解锁上次锁定的显存
RSMEDIARENDER_API BOOL	ROSEEK_MRDisplayVideo(PVOID dest);//显示显存中的图像
RSMEDIARENDER_API void	ROSEEK_MRSetVideoWndCaption(PVOID dest, const char *pCaption);//设置显示窗口的标题
RSMEDIARENDER_API void	ROSEEK_MRResizeVideoWnd(PVOID dest);//当显示窗口尺寸变化时，调整显示图像尺寸以适应新窗口大小
RSMEDIARENDER_API BOOL	ROSEEK_MRPutVideoWndOwner(PVOID dest, HWND hWnd);//设置显示窗口的父窗口，如果为NULL，则显示窗口会独立显示
RSMEDIARENDER_API BOOL  ROSEEK_MRInvalidateWnd(PVOID dest);//用白色刷新背景
RSMEDIARENDER_API void	ROSEEK_MRBeginSetVideoMask(PVOID dest);
RSMEDIARENDER_API void	ROSEEK_MRStopSetVideoMask(PVOID dest);
RSMEDIARENDER_API void	ROSEEK_MRSetVideoMask(PVOID dest, const char *pszMask);
RSMEDIARENDER_API void	ROSEEK_MRGetVideoMask(PVOID dest, char *pszMask);
RSMEDIARENDER_API void	ROSEEK_MRClickVideoMask(PVOID dest, POINT pt);
RSMEDIARENDER_API BOOL	ROSEEK_MRConvertBayerToYUV420(char *pBufDest, char *pBufSrc, BOOL bHasExtendedLine, int nWidth, int nHeight);//将图像从Bayer格式转换成YUV420格式
RSMEDIARENDER_API BOOL	ROSEEK_MRConvertBayerToRGB24(char *pBufDest, char *pBufSrc, int nWidth, int nHeight, int nType);//将图像从Bayer格式转换成RGB24格式

RSMEDIARENDER_API BOOL  ROSEEK_MRSetAudioFormat(PVOID dest, int nChannels, int nFrequency, int nBitsPerSample);
RSMEDIARENDER_API BOOL  ROSEEK_MRActiveAudioRender(PVOID dest, HWND hWnd, DWORD dwBufferSize);
RSMEDIARENDER_API void  ROSEEK_MRDeactiveAudioRender(PVOID dest);
RSMEDIARENDER_API BOOL  ROSEEK_MRLockAudioBuffer(PVOID dest, void **ppBuf, DWORD *pBufSize);
RSMEDIARENDER_API BOOL  ROSEEK_MRUnlockAudioBuffer(PVOID dest);
RSMEDIARENDER_API BOOL  ROSEEK_MRPlayAudio(PVOID dest);
RSMEDIARENDER_API BOOL  ROSEEK_MRStopAudio(PVOID dest);

#ifdef __cplusplus
}
#endif