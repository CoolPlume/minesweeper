
// minesweeperDlg.h: 头文件
//

#pragma once

#include <array>

// CminesweeperDlg 对话框
class CminesweeperDlg : public CDialogEx
{
// 构造
public:
	CminesweeperDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MINESWEEPER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	CEdit time_cost;
	CEdit total_number_of_mines;
	CEdit remaining_mines;

private:
	int time_cost_int = 0;
	int remaining_mines_int = 0;
	bool pause_flag = false;
	std::array<std::array<bool, 10>, 7>location {};
	std::array<std::array<bool, 10>, 7>location_flag {};
	int count_mine ( int i, int j );
	int count_mine ( int i, int j ,bool flag);

	bool next_flag = false;
public:
	afx_msg void OnTimer ( UINT_PTR nIDEvent );
	afx_msg void OnBnClickedButton71 ( );
	afx_msg void OnButtonPort ( UINT nID );
	afx_msg void OnButtonRight ( UINT nID );
	virtual BOOL PreTranslateMessage ( MSG* pMsg );
};
