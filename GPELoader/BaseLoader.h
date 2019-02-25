#pragma once
#pragma once

#include <minwindef.h>
#include <afxstr.h>

class BaseLoader {
public:
	virtual BOOL init() = 0;
	virtual BOOL load(CString filePath) = 0;
	virtual BOOL unload() = 0;
	virtual BOOL outputMsg(DWORD errCode, CString errMsg) = 0;
};