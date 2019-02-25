#pragma once
#pragma once

#include <minwindef.h>
#include <afxstr.h>

class BaseLoader {
public:
	virtual BOOL init() = 0;
	virtual BOOL load() = 0;
	virtual BOOL unload() = 0;
	virtual BOOL outputErrorMsg() = 0;
};