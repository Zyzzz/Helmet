
// Helmet-FCEM.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CHelmetFCEMApp:
// �йش����ʵ�֣������ Helmet-FCEM.cpp
//

class CHelmetFCEMApp : public CWinApp
{
public:
	CHelmetFCEMApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CHelmetFCEMApp theApp;