
// minesweeperDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "minesweeper.h"
#include "minesweeperDlg.h"

#include <string>

#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CminesweeperDlg 对话框



CminesweeperDlg::CminesweeperDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MINESWEEPER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CminesweeperDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange ( pDX );
	DDX_Control ( pDX, IDC_EDIT3, time_cost );
	DDX_Control ( pDX, IDC_EDIT1, total_number_of_mines );
	DDX_Control ( pDX, IDC_EDIT2, remaining_mines );
}

BEGIN_MESSAGE_MAP ( CminesweeperDlg, CDialogEx )
	ON_WM_SYSCOMMAND ( )
	ON_WM_PAINT ( )
	ON_WM_QUERYDRAGICON ( )
	ON_WM_TIMER ( )
	ON_BN_CLICKED ( IDC_BUTTON71, &CminesweeperDlg::OnBnClickedButton71 )
	ON_COMMAND_RANGE ( 1000, 1069, CminesweeperDlg::OnButtonPort )
	ON_CONTROL_RANGE ( BN_DOUBLECLICKED, 1000, 1069, CminesweeperDlg::OnButtonRight )
END_MESSAGE_MAP()


// CminesweeperDlg 消息处理程序

BOOL CminesweeperDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		CString strAboutMenu;
		BOOL bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	//ShowWindow(SW_MINIMIZE);

	// TODO: 在此添加额外的初始化代码


	const auto app = dynamic_cast<CminesweeperApp*>(AfxGetApp ( ));

	time_cost.SetWindowTextW ( TEXT ( "0" ) );
	SetTimer ( timing, 1000, nullptr );//调用计时器统计时间

	total_number_of_mines.SetWindowTextW ( static_cast<CString>(std::to_string(app->total_number_of_mines).c_str()) );//显示雷总数

	remaining_mines_int = app->total_number_of_mines;
	remaining_mines.SetWindowTextW ( static_cast<CString>(std::to_string ( remaining_mines_int ).c_str ( )) );//显示剩余的雷


	//布雷
	const double probability = static_cast<double>(app->total_number_of_mines) / 70.0;
	int now_mine = 0;//用于统计以布雷个数
	bool end_flag = false;//结束布雷的标志
	srand ( time (nullptr) );//设置随机数种子
	while ( end_flag == false )
	{
		for ( int i = 0; i < 7; i++ )
		{
			for ( int j = 0; j < 10; j++ )
			{
				if ( now_mine >= app->total_number_of_mines )
				{
					end_flag = true;
					break;
				}
				if ( const double flag = rand ( ) / static_cast<double>(RAND_MAX); flag < probability )
				{
					//雷
					location[i][j] = true;
					now_mine++;

				}
				else if ( flag >= probability )
				{
					//非雷
					location[i][j] = false;
				}
				Sleep ( 1 );
			}
			if ( end_flag == true )
			{
				break;
			}
		}
	}


	for ( int i = 0; i < 7; i++ )
	{
		for ( int j = 0; j < 10; j++ )
		{
			location_flag[i][j] = true;
		}
	}


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CminesweeperDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CminesweeperDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		const int cxIcon = GetSystemMetrics(SM_CXICON);
		const int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		const int x = (rect.Width() - cxIcon + 1) / 2;
		const int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CminesweeperDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



int CminesweeperDlg::count_mine ( int i, int j )
{
	int sum = 0;//周围八格雷的数量
	if ( j != 0 )
	{
		if ( location[i][static_cast<std::array<bool, 10Ui64>::size_type>(j) - 1] == true )
		{
			sum++;
		}
		else
		{
			if ( count_mine ( i, j - 1, 1 ) == 0 )
			{
				const int nID = i * 10 + j - 1 + 1000;
				GetDlgItem ( nID )->SetWindowText ( TEXT ( "0" ) );
				GetDlgItem ( nID )->EnableWindow ( false );
				location_flag[i][static_cast<std::array<bool, 10Ui64>::size_type>(j) - 1] = false;
			}
		}
	}
	if ( j != 9 )
	{
		if ( location[i][static_cast<std::array<bool, 10Ui64>::size_type>(j) + 1] == true )
		{
			sum++;
		}
		else
		{
			if ( count_mine ( i, j + 1, 1 ) == 0 )
			{
				const int nID = i * 10 + j + 1 + 1000;
				GetDlgItem ( nID )->SetWindowText ( TEXT ( "0" ) );
				GetDlgItem ( nID )->EnableWindow ( false );
				location_flag[i][static_cast<std::array<bool, 10Ui64>::size_type>(j) + 1] = false;
			}
		}
	}
	if ( i != 0 )
	{
		if ( location[static_cast<std::array<std::array<bool, 10Ui64>, 7Ui64>::size_type>(i) - 1][j] == true )
		{
			sum++;
		}
		else
		{
			if ( count_mine ( i - 1, j, 1 ) == 0 )
			{
				const int nID = (i - 1) * 10 + j + 1000;
				GetDlgItem ( nID )->SetWindowText ( TEXT ( "0" ) );
				GetDlgItem ( nID )->EnableWindow ( false );
				location_flag[static_cast<std::array<std::array<bool, 10Ui64>, 7Ui64>::size_type>(i) - 1][j] = false;
			}
		}
	}
	if ( i != 6 )
	{
		if ( location[static_cast<std::array<std::array<bool, 10Ui64>, 7Ui64>::size_type>(i) + 1][j] == true )
		{
			sum++;
		}
		else
		{
			if ( count_mine ( i+1, j, 1 ) == 0 )
			{
				const int nID = (i + 1) * 10 + j + 1000;
				GetDlgItem ( nID )->SetWindowText ( TEXT ( "0" ) );
				GetDlgItem ( nID )->EnableWindow ( false );
				location_flag[static_cast<std::array<std::array<bool, 10Ui64>, 7Ui64>::size_type>(i) + 1][j] = false;
			}
		}
	}
	if ( j != 0 && i != 0 )
	{
		if ( location[static_cast<std::array<std::array<bool, 10Ui64>, 7Ui64>::size_type>(i) - 1][static_cast<std::array<bool, 10Ui64>::size_type>(j) - 1] == true )
		{
			sum++;
		}
	}
	if ( i != 6 && j != 9 )
	{
		if ( location[static_cast<std::array<std::array<bool, 10Ui64>, 7Ui64>::size_type>(i) + 1][static_cast<std::array<bool, 10Ui64>::size_type>(j) + 1] == true )
		{
			sum++;
		}
	}
	if ( i != 6 && j != 0 )
	{
		if ( location[static_cast<std::array<std::array<bool, 10Ui64>, 7Ui64>::size_type>(i) + 1][static_cast<std::array<bool, 10Ui64>::size_type>(j) - 1] == true )
		{
			sum++;
		}
	}
	if ( i != 0 && j != 9 )
	{
		if ( location[static_cast<std::array<std::array<bool, 10Ui64>, 7Ui64>::size_type>(i) - 1][static_cast<std::array<bool, 10Ui64>::size_type>(j) + 1] == true )
		{
			sum++;
		}
	}
	return sum;
}

int CminesweeperDlg::count_mine ( int i, int j, bool flag )
{
	int sum = 0;//周围八格雷的数量
	if ( j != 0 )
	{
		if ( location[i][static_cast<std::array<bool, 10Ui64>::size_type>(j) - 1] == true )
		{
			sum++;
		}
	}
	if ( j != 9 )
	{
		if ( location[i][static_cast<std::array<bool, 10Ui64>::size_type>(j) + 1] == true )
		{
			sum++;
		}
	}
	if ( i != 0 )
	{
		if ( location[static_cast<std::array<std::array<bool, 10Ui64>, 7Ui64>::size_type>(i) - 1][j] == true )
		{
			sum++;
		}
	}
	if ( i != 6 )
	{
		if ( location[static_cast<std::array<std::array<bool, 10Ui64>, 7Ui64>::size_type>(i) + 1][j] == true )
		{
			sum++;
		}
	}
	if ( j != 0 && i != 0 )
	{
		if ( location[static_cast<std::array<std::array<bool, 10Ui64>, 7Ui64>::size_type>(i) - 1][static_cast<std::array<bool, 10Ui64>::size_type>(j) - 1] == true )
		{
			sum++;
		}
	}
	if ( i != 6 && j != 9 )
	{
		if ( location[static_cast<std::array<std::array<bool, 10Ui64>, 7Ui64>::size_type>(i) + 1][static_cast<std::array<bool, 10Ui64>::size_type>(j) + 1] == true )
		{
			sum++;
		}
	}
	if ( i != 6 && j != 0 )
	{
		if ( location[static_cast<std::array<std::array<bool, 10Ui64>, 7Ui64>::size_type>(i) + 1][static_cast<std::array<bool, 10Ui64>::size_type>(j) - 1] == true )
		{
			sum++;
		}
	}
	if ( i != 0 && j != 9 )
	{
		if ( location[static_cast<std::array<std::array<bool, 10Ui64>, 7Ui64>::size_type>(i) - 1][static_cast<std::array<bool, 10Ui64>::size_type>(j) + 1] == true )
		{
			sum++;
		}
	}
	return sum;
}

void CminesweeperDlg::OnTimer ( UINT_PTR nIDEvent )
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnTimer ( nIDEvent );

	switch ( nIDEvent )
	{
	case timing:
	{
		time_cost_int++;
		time_cost.SetWindowTextW ( static_cast<CString>(std::to_string(time_cost_int).c_str()) );
		break;
	}
	}
}


void CminesweeperDlg::OnBnClickedButton71 ( )//按钮：暂停|继续
{
	switch ( pause_flag )
	{
	case true://当前暂停 需切换成继续
	{
		SetTimer ( timing, 1000, nullptr );
		pause_flag = false;

		for ( int i = 1000; i < 1070; i++ )
		{
			const int x = (i - 1000) / 10;
			const int y = (i - 1000) % 10;
			if ( location_flag[x][y] == true )
			{
				GetDlgItem ( i )->EnableWindow ( true );
			}
		}

		break;
	}
	case false://当前继续 需切换成暂停
	{
		KillTimer ( timing );
		pause_flag = true;

		for ( int i = 1000; i < 1070; i++ )
		{
			GetDlgItem ( i )->EnableWindow ( false );
		}

		break;
	}
	}
}

void CminesweeperDlg::OnButtonPort (const UINT nID )
{
	//const CWnd* pWnd = GetFocus ( );
	//int nPortID = pWnd->GetDlgCtrlID ( );
	//MessageBox ( static_cast<CString>(std::to_string ( nID ).c_str ( )) );
	const auto app = dynamic_cast<CminesweeperApp*>(AfxGetApp ( ));
	//auto button = dynamic_cast<CButton*>(GetDlgItem(nID));

	//得到坐标
	const int i = (nID - 1000) / 10;
	const int j = (nID - 1000) % 10;


	if ( location[i][j] == true )//当前格是雷
	{
		GetDlgItem ( nID )->SetWindowText ( TEXT ( "雷" ) );
		KillTimer ( timing );
		MessageBox ( TEXT ( "失败！" ) );
		for ( int i = 1000; i < 1070; i++ )
		{
			GetDlgItem ( i )->EnableWindow ( false );
		}
		GetDlgItem ( IDC_BUTTON71 )->EnableWindow ( false );
	}
	else if ( location[i][j] == false )//当前格不是雷
	{
		



		const int sum = count_mine ( i, j );

		GetDlgItem ( nID )->SetWindowText ( static_cast<CString>(std::to_string(sum).c_str()) );
		GetDlgItem ( nID )->EnableWindow ( false );
		location_flag[i][j] = false;
	}


	//获胜判断
	int remainder = 0;
	for ( int m = 0; m < 7; m++ )
	{
		for ( int n = 0; n < 10; n++ )
		{
			if ( location_flag[m][n] == true )
			{
				remainder++;
			}
		}
	}
	if ( remainder == app->total_number_of_mines )
	{
		KillTimer ( timing );
		MessageBox ( TEXT ( "获胜！" ) );
	}
}

void CminesweeperDlg::OnButtonRight ( UINT nID )
{
	MessageBox ( L"1" );
}


BOOL CminesweeperDlg::PreTranslateMessage ( MSG* pMsg )
{
	// TODO: 在此添加专用代码和/或调用基类


	if ( pMsg->message == WM_RBUTTONDOWN )//鼠标点击右键
	{
		CRect rc;
		CPoint ptCursor;
		GetCursorPos ( &ptCursor );//获取鼠标的位置信息
		for ( int pos = 1000; pos < 1070; pos++ )//IDC_BOUTTON1(1000)--IDC_BOUTTON70(1069)
		{
			GetDlgItem ( pos )->GetWindowRect ( &rc );//获取控件的位置信息
			if ( PtInRect ( &rc, ptCursor ) )//右键点击位置在某一个控件上
			{
				CString content;
				GetDlgItemText ( pos, content );
				if ( content == TEXT ( "*" ) )
				{
					SetDlgItemText ( pos, nullptr );
					remaining_mines_int++;
				}
				else
				{
					SetDlgItemText ( pos, TEXT ( "*" ) );
					remaining_mines_int--;
				}
				remaining_mines.SetWindowTextW ( static_cast<CString>(std::to_string ( remaining_mines_int ).c_str ( )) );

			}
		}
	}

	return CDialogEx::PreTranslateMessage ( pMsg );
}
