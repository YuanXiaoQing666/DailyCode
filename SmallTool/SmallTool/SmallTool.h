
// SmallTool.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CSmallToolApp: 
// �йش����ʵ�֣������ SmallTool.cpp
//

class CSmallToolApp : public CWinApp
{
public:
	CSmallToolApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CSmallToolApp theApp;