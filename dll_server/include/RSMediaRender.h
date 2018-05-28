// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� RSMEDIARENDER_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// RSMEDIARENDER_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
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
RSMEDIARENDER_API PVOID ROSEEK_MRCreateOne(int nMediaMode);//����һ����ʾģ��
RSMEDIARENDER_API void	ROSEEK_MRClose(PVOID dest);//����һ����ʾģ��

RSMEDIARENDER_API BOOL	ROSEEK_MRSetVideoFormat(PVOID dest, int nType, int nWidth, int nHeight);//������ʾģ��Ҫ���յ�ͼ�����ݸ�ʽ
RSMEDIARENDER_API BOOL	ROSEEK_MRActiveVideoRender(PVOID dest);//������ʾģ�飬������ʾ��Ҫ����Դ
RSMEDIARENDER_API void	ROSEEK_MRDeactiveVideoRender(PVOID dest);//ֹͣ��ʾģ�飬�ر���ʾ��Ҫ����Դ
RSMEDIARENDER_API BOOL	ROSEEK_MRLockVideoBuffer(PVOID dest, void **ppBuf, int *pnPitch);//��ȡ��ʾģ���Դ�ָ�룬ͬʱ�����˿��ڴ�
RSMEDIARENDER_API BOOL	ROSEEK_MRUnlockVideoBuffer(PVOID dest);//�����ϴ��������Դ�
RSMEDIARENDER_API BOOL	ROSEEK_MRDisplayVideo(PVOID dest);//��ʾ�Դ��е�ͼ��
RSMEDIARENDER_API void	ROSEEK_MRSetVideoWndCaption(PVOID dest, const char *pCaption);//������ʾ���ڵı���
RSMEDIARENDER_API void	ROSEEK_MRResizeVideoWnd(PVOID dest);//����ʾ���ڳߴ�仯ʱ��������ʾͼ��ߴ�����Ӧ�´��ڴ�С
RSMEDIARENDER_API BOOL	ROSEEK_MRPutVideoWndOwner(PVOID dest, HWND hWnd);//������ʾ���ڵĸ����ڣ����ΪNULL������ʾ���ڻ������ʾ
RSMEDIARENDER_API BOOL  ROSEEK_MRInvalidateWnd(PVOID dest);//�ð�ɫˢ�±���
RSMEDIARENDER_API void	ROSEEK_MRBeginSetVideoMask(PVOID dest);
RSMEDIARENDER_API void	ROSEEK_MRStopSetVideoMask(PVOID dest);
RSMEDIARENDER_API void	ROSEEK_MRSetVideoMask(PVOID dest, const char *pszMask);
RSMEDIARENDER_API void	ROSEEK_MRGetVideoMask(PVOID dest, char *pszMask);
RSMEDIARENDER_API void	ROSEEK_MRClickVideoMask(PVOID dest, POINT pt);
RSMEDIARENDER_API BOOL	ROSEEK_MRConvertBayerToYUV420(char *pBufDest, char *pBufSrc, BOOL bHasExtendedLine, int nWidth, int nHeight);//��ͼ���Bayer��ʽת����YUV420��ʽ
RSMEDIARENDER_API BOOL	ROSEEK_MRConvertBayerToRGB24(char *pBufDest, char *pBufSrc, int nWidth, int nHeight, int nType);//��ͼ���Bayer��ʽת����RGB24��ʽ

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