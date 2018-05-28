// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 RSJPEGUTIL_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// RSJPEGUTIL_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#ifndef _RS_JPEG_UTIL_H_
#define _RS_JPEG_UTIL_H_

#ifdef RSJPEGUTIL_EXPORTS
#define RSJPEGUTIL_API __declspec(dllexport)
#else
#define RSJPEGUTIL_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

	enum LJ_YUV_TYPE
	{
		LJ_UNKNOWN,
		LJ_YUV420P,
		LJ_YUV422P,
		LJ_YUV444P
	};

RSJPEGUTIL_API void* Roseek_JpegEncoder_Create();
RSJPEGUTIL_API void Roseek_JpegEncoder_Destroy(void* handle);
RSJPEGUTIL_API int Roseek_JpegEncoder_EncodeRGB(void* handle
						, unsigned char * p_src, int width, int height, int quality
						, unsigned char * p_dest, long * p_dest_size);
RSJPEGUTIL_API int Roseek_JpegEncoder_EncodeYUV(void * handle
						, unsigned char * p_src_y, unsigned char * p_src_u, unsigned char * p_src_v
						, int width, int height, int fmt, int quality
						, unsigned char * p_dest, long * p_dest_size);

RSJPEGUTIL_API void * Roseek_JpegDecoder_Create();
RSJPEGUTIL_API void Roseek_JpegDecoder_Destroy(void * handle);
RSJPEGUTIL_API int Roseek_JpegDecoder_DecodeToRGB(void * handle
						, unsigned char * p_src, long src_size
						, unsigned char * p_dest, long dest_size
						, int * p_width, int * p_height);
RSJPEGUTIL_API int Roseek_JpegDecoder_DecodeToYUV(void * handle
						, unsigned char * p_src, long src_size
						, unsigned char * p_dest, long dest_size
						, int * p_width, int * p_height, int * p_fmt);

#ifdef __cplusplus
};
#endif

#endif