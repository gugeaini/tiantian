
// 大富翁银行系统.h: 大富翁银行系统 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含 'pch.h' 以生成 PCH"
#endif

#include "resource.h"       // 主符号


// C大富翁银行系统App:
// 有关此类的实现，请参阅 大富翁银行系统.cpp
//

class C大富翁银行系统App : public CWinApp
{
public:
	C大富翁银行系统App() noexcept;


// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern C大富翁银行系统App theApp;
