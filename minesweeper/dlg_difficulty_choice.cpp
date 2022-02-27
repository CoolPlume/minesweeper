// dlg_difficulty_choice.cpp: 实现文件
//

#include "pch.h"
#include "minesweeper.h"
#include "afxdialogex.h"
#include "dlg_difficulty_choice.h"
#include <string>


// dlg_difficulty_choice 对话框

IMPLEMENT_DYNAMIC(dlg_difficulty_choice, CDialogEx)

dlg_difficulty_choice::dlg_difficulty_choice(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIFFICULTY_CHOICE, pParent)
{

}

dlg_difficulty_choice::~dlg_difficulty_choice()
{
}

void dlg_difficulty_choice::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange ( pDX );
	DDX_Control ( pDX, IDC_EDIT1, total_number_of_mines );
}


BEGIN_MESSAGE_MAP(dlg_difficulty_choice, CDialogEx)
	ON_BN_CLICKED ( IDC_BUTTON2, &dlg_difficulty_choice::OnBnClickedButton2 )
	ON_BN_CLICKED ( IDC_BUTTON1, &dlg_difficulty_choice::OnBnClickedButton1 )
END_MESSAGE_MAP()


// dlg_difficulty_choice 消息处理程序


void dlg_difficulty_choice::OnCancel ( )
{
	// TODO: 在此添加专用代码和/或调用基类
	switch ( const int flag = ::MessageBox ( nullptr, TEXT ( "您确定要退出吗" ), TEXT ( "退出" ), MB_TASKMODAL | MB_YESNO | MB_ICONQUESTION ) )
	{
	case IDOK:
	{
		exit ( 0 );

		break;
	}
	case IDNO:
	{
		return;
		break;

	}
	}
	exit ( 0 );
	CDialogEx::OnCancel ( );
}


BOOL dlg_difficulty_choice::OnInitDialog ( )
{
	CDialogEx::OnInitDialog ( );

	// TODO:  在此添加额外的初始化

	total_number_of_mines.SetWindowTextW ( TEXT ( "10" ) );//默认10颗雷


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void dlg_difficulty_choice::OnBnClickedButton2 ( )//按钮：退出
{
	OnCancel ( );
}


void dlg_difficulty_choice::OnBnClickedButton1 ( )//按钮：开始游戏
{
	const auto app = dynamic_cast<CminesweeperApp*>(AfxGetApp ( ));
	CString num_of_mine;
	GetDlgItemText ( IDC_EDIT1, num_of_mine );
	const unsigned int UINT_num_of_mine = std::stoi ( static_cast<std::string>(CW2A ( num_of_mine )) );

	if ( UINT_num_of_mine > 0 && UINT_num_of_mine <= 70 )
	{
		app->total_number_of_mines = UINT_num_of_mine;
	}
	else
	{
		::MessageBox ( nullptr, TEXT ( "数据范围非法！" ), TEXT ( "警告" ), MB_ICONWARNING | MB_OK | MB_TASKMODAL );
		return;
	}

	EndDialog ( 0 );
}


void dlg_difficulty_choice::OnOK ( )
{

	OnBnClickedButton1 ( );

	//CDialogEx::OnOK ( );
}
