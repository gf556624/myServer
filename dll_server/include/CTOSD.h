// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� CTOSD_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// CTOSD_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef CTOSD_EXPORTS
#define CTOSD_API __declspec(dllexport)
#else
#define CTOSD_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define CT_SUCCESS							(0)
#define CT_ERROR_INVALID_PARAMETERS			(-1)
#define CT_ERROR_UNSUPPORTED				(-2)
#define CT_ERROR_EXCEPTION					(-3)
#define CT_ERROR_BUSY						(-4)
#define CT_ERROR_CREATEFAILED				(-5)
#define CT_ERROR_OPENFAILED					(-6)
#define CT_ERROR_TIMEOUT					(-7)
#define CT_ERROR_BUFFNOTENOUGH				(-8)
#define CT_ERROR_LACKOFRESOURCE				(-9)

enum
{
	IMG_FMT_YUV420SP,
	IMG_FMT_MAX
};

enum
{
	DISPLAY_FMT_ALPHAOVERLAY,
	DISPLAY_FMT_DIRECTOVERLAY,
	DISPLAY_FMT_ALPHAOVERLAY_MONOSPACEDFONT,
	DISPLAY_FMT_DIRECTOVERLAY_MONOSPACEDFONT,
	DISPLAY_FMT_MAX
};

typedef struct _OSDFormat
{
	UINT32		FontWidth;
	UINT32		FontHeight;
	UINT32		FontColor;
	UINT32		BackColor;
	UINT32		ImageFormat;
	UINT32		DisplayFormat;
}OSDFormat;

typedef struct _RAWImageInfo
{
	UINT32		ImageFormat;
	UINT32		ImageWidth;
	UINT32		ImageHeight;
	UINT8*		pImageData[4];
}RAWImageInfo;

CTOSD_API const char * Roseek_OSD_GetModuleInfo();

CTOSD_API int Roseek_OSD_Create(void ** pHandle, const char * pFontFilePath);
CTOSD_API int Roseek_OSD_Close(void * Handle);

CTOSD_API int Roseek_OSD_AddTextCache(void * Handle, OSDFormat Fmt, const wchar_t * pUnicodeText);

CTOSD_API int Roseek_OSD_DrawText(void * Handle, RAWImageInfo ImageInfo, OSDFormat Fmt, UINT32 LocationX, UINT32 LocationY, UINT32 Alpha, const wchar_t * pUnicodeText);

#ifdef __cplusplus
}
#endif