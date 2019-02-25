#pragma once

#include "BaseLoader.h"

class FileLoader : public BaseLoader {
public:
	FileLoader(void(*ecb)(DWORD errCode, CString errMsg) = NULL);
	~FileLoader();
public:
	BOOL init();
	BOOL load(CString filePath);
	BOOL unload();
	BOOL outputErrorMsg(DWORD errCode, CString errMsg);
	void setErrorCallback(void(*ecb)(DWORD errCode, CString errMsg));

private:
	void(*errorCallBack)(DWORD errCode, CString errMsg);
};


FileLoader::FileLoader(void(*ecb)(DWORD errCode, CString errMsg) = NULL) {
	this->errorCallBack = ecb;
;

FileLoader::~FileLoader() {
	this->errorCallBack = NULL;
}

BOOL FileLoader::init() {
	return TRUE;
}

BOOL FileLoader::load(CString filePath) {
	return TRUE;
}

BOOL FileLoader::unload() {
	return TRUE;
}

BOOL FileLoader::outputErrorMsg(DWORD errCode, CString errMsg) {
	return TRUE;
}

void FileLoader::setErrorCallback(void(*ecb)(DWORD errCode, CString errMsg)) {
	this->errorCallBack = ecb;
}
