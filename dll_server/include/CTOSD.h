// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 CTOSD_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// CTOSD_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
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