#pragma once

#include <wtypes.h>

#define SUCCESS_RET 0
#define ERROR_RET -1

typedef int Mode;

enum ENUM_MAP_FROM {
	MAP_FROM_FILE = 0, //���ļ�ӳ��
	MAP_FROM_MEMORY, //���ڴ�ӳ��
	MAP_FROM_REST
};

typedef struct _STU_MAP_FILE {
public:
	HANDLE hFile;		//�ļ����
	HANDLE hMapping;	//�ļ�ӳ�䵽�ڴ�ľ��
	LPVOID pImageBase;	//�ļ��ľ����ַ
	DWORD dwFileSize;	//�ļ��Ĵ�С
} STU_MAP_FILE, *P_STU_MAP_FILE;