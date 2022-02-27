
// minesweeper.h: PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含 'pch.h' 以生成 PCH"
#endif

#include "resource.h"		// 主符号


// CminesweeperApp:
// 有关此类的实现，请参阅 minesweeper.cpp
//

class CminesweeperApp : public CWinApp
{
public:
	CminesweeperApp();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()

public:
	unsigned int total_number_of_mines = 0;
};

extern CminesweeperApp theApp;
constexpr int timing = 1;//定时器类型1