// Byte2Bitmap.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CByte2BitmapApp:
// �йش����ʵ�֣������ Byte2Bitmap.cpp
//

class CByte2BitmapApp : public CWinApp
{
public:
	CByte2BitmapApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CByte2BitmapApp theApp;