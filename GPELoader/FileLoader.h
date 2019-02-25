#pragma once

#include "BaseLoader.h"
#include "GFileAnalyze.h"

class FileLoader : public BaseLoader {
public:
	FileLoader();
	FileLoader(void(*callback)(DWORD errCode, CString errMsg));
	~FileLoader();
public:
	BOOL load(CString filePath);
	BOOL unload();
	
	/**
	 * ������Ϣ�ص�
	 */
	void setMsgCallback(void(*msgCallback)(DWORD errCode, CString errMsg));

	void operator=(FileLoader &fileLoader);

private:
	P_STU_MAP_FILE m_pFileHandle;
	BOOL isLoadSuccess;
	
	void(*msgCallback)(DWORD errCode, CString errMsg);

	BOOL init();
	BOOL outputMsg(DWORD errCode, CString errMsg);

};

FileLoader::FileLoader() {
	this->msgCallback = NULL;
	this->m_pFileHandle = NULL;
}

FileLoader::FileLoader(void(*msgCallback)(DWORD errCode, CString errMsg) = NULL) {
	this->msgCallback = msgCallback;
	this->m_pFileHandle = NULL;
}

FileLoader::~FileLoader() {
	this->msgCallback = NULL;
}

BOOL FileLoader::init() {

	if (m_pFileHandle == NULL) {
		this->m_pFileHandle = new STU_MAP_FILE;
	}

	memset(m_pFileHandle, 0, sizeof(STU_MAP_FILE));
	return TRUE;
}

BOOL FileLoader::load(CString filePath) {
	isLoadSuccess = FALSE;

	HANDLE hFile = INVALID_HANDLE_VALUE;
	HANDLE hMapping = INVALID_HANDLE_VALUE;
	LPVOID pImageBase = NULL;
	DWORD dwFileSize = 0;
	DWORD dwFileSizeHight = 0;
	CString msg;

	if (init() != TRUE) {
		msg = _T("��ʼ��ʧ��!");
		outputMsg(ERROR_RET, msg);
		return FALSE;
	}

	//������Ӧ�ļ�
	hFile = CreateFile(filePath,
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ,
		NULL,
		OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	if (!hFile) {
		msg = _T("�ļ�����ʧ��!");
		outputMsg(ERROR_RET, msg);
		return FALSE;
	}

	//��ȡ�ļ���С
	dwFileSize = GetFileSize(hFile, &dwFileSizeHight);

	if (0 == dwFileSize && 0 == dwFileSizeHight) {
		msg = _T("�ļ���С��ȡʧ��!");
		outputMsg(ERROR_RET, msg);
		return FALSE;
	}

	//�����ļ��ڴ�ӳ��
	hMapping = CreateFileMapping(hFile,
		NULL,
		PAGE_READWRITE,
		NULL,
		dwFileSize,
		NULL);

	if (!hMapping) {
		msg = _T("�ļ��ڴ�ӳ�䴴��ʧ��!");
		outputMsg(ERROR_RET, msg);
		return FALSE;
	}

	//��ȡ�ڴ澵���ַ
	pImageBase = MapViewOfFile(hMapping,
		FILE_MAP_ALL_ACCESS,
		0,
		0,
		dwFileSize);

	if (!pImageBase) {
		msg = _T("��ȡ�ڴ澵���ַʧ��!");
		outputMsg(ERROR_RET, msg);
		return FALSE;
	}

	m_pFileHandle->hFile = hFile;
	m_pFileHandle->dwFileSize = dwFileSize;
	m_pFileHandle->hMapping = hMapping;
	m_pFileHandle->pImageBase = pImageBase;

	isLoadSuccess = TRUE;
	msg = _T("���سɹ�!");
	outputMsg(SUCCESS_RET, msg);
	return TRUE;
}

BOOL FileLoader::unload() {
	CString msg;

	if (!isLoadSuccess) {
		msg = _T("û��load�ɹ�,�޷�ִ��ж��!");
		outputMsg(ERROR_RET, msg);
	}

	if (!UnmapViewOfFile(m_pFileHandle->pImageBase)) {
		msg = _T("ж���ڴ澵���ַʧ��,�޷�ִ��ж��!");
		outputMsg(ERROR_RET, msg);
		return FALSE;
	}
	m_pFileHandle->pImageBase = NULL;

	if (!CloseHandle(m_pFileHandle->hMapping)) {
		msg = _T("�ر��ļ��ڴ�ӳ��ʧ��,�޷�ִ��ж��!");
		outputMsg(ERROR_RET, msg);
		return FALSE;
	}
	m_pFileHandle->hMapping = NULL;

	if (!CloseHandle(m_pFileHandle->hFile)) {
		msg = _T("�ر��ļ����ʧ��,�޷�ִ��ж��!");
		outputMsg(ERROR_RET, msg);
		return FALSE;
	}
	m_pFileHandle->dwFileSize = 0;
	m_pFileHandle->hFile = NULL;

	isLoadSuccess = FALSE;
	msg = _T("ж�سɹ�!");
	outputMsg(SUCCESS_RET, msg);
	return TRUE;
}

BOOL FileLoader::outputMsg(DWORD errCode, CString errMsg) {
	if (msgCallback != NULL) {
		msgCallback(errCode, errMsg);
	}
	return TRUE;
}

void FileLoader::setMsgCallback(void(*msgCallback)(DWORD errCode, CString errMsg)) {
	this->msgCallback = msgCallback;
}

void FileLoader::operator=(FileLoader &fileLoader) {
	this->m_pFileHandle = fileLoader.m_pFileHandle;
}
