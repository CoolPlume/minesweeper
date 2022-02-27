#pragma once
#include "afxdialogex.h"


// dlg_difficulty_choice 对话框

class dlg_difficulty_choice : public CDialogEx
{
	DECLARE_DYNAMIC(dlg_difficulty_choice)

public:
	dlg_difficulty_choice(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~dlg_difficulty_choice();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIFFICULTY_CHOICE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	virtual void OnCancel ( );
public:
	virtual BOOL OnInitDialog ( );
private:
	CEdit total_number_of_mines;
public:
	afx_msg void OnBnClickedButton2 ( );
	afx_msg void OnBnClickedButton1 ( );
	virtual void OnOK ( );
};
