#pragma once

#include <wtypes.h>

#define SUCCESS_RET 0
#define ERROR_RET -1

typedef int Mode;

enum ENUM_MAP_FROM {
	MAP_FROM_FILE = 0, //从文件映射
	MAP_FROM_MEMORY, //从内存映射
	MAP_FROM_REST
};

typedef struct _STU_MAP_FILE {
public:
	HANDLE hFile;		//文件句柄
	HANDLE hMapping;	//文件映射到内存的句柄
	LPVOID pImageBase;	//文件的镜像基址
	DWORD dwFileSize;	//文件的大小
} STU_MAP_FILE, *P_STU_MAP_FILE;