
// SmallToolDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SmallTool.h"
#include "SmallToolDlg.h"
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


// CSmallToolDlg 对话框



CSmallToolDlg::CSmallToolDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SMALLTOOL_DIALOG, pParent)
	, g_port(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSmallToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_Port, g_port);
}

BEGIN_MESSAGE_MAP(CSmallToolDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_RecvBroad, &CSmallToolDlg::OnBnClickedRecvBroad)
END_MESSAGE_MAP()


// CSmallToolDlg 消息处理程序

BOOL CSmallToolDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
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

	ShowWindow(SW_MINIMIZE);

	// TODO: 在此添加额外的初始化代码
	g_port = "52234";            //默认接受的端口号
	GetDlgItem(IDC_Port)->SetWindowText(g_port);


	/* 设置按钮格式 */
	CFont * btn_style;
	btn_style = new CFont;
	btn_style->CreateFont(24,     // 字体的高度 
		0,                        // 字体的宽度 
		0,						  // 字体的倾斜角 
		0,						  // 字体的倾斜角 
		FW_NORMAL,		          // 字体的粗细 
		FALSE,					  // 字体是否斜体 
		FALSE,                    // 字体是否有下划线 
		0,                        // 字体是否有删除线 
		ANSI_CHARSET,             // 字体使用的字符集
		OUT_DEFAULT_PRECIS,       // 指定如何选择合适的字体
		CLIP_DEFAULT_PRECIS,      // 用来确定裁剪的精度
		DEFAULT_QUALITY,          // 跟选择的字体相符合
		DEFAULT_PITCH | FF_SWISS, // 间距标志和属性标志
		_T("宋体"));              // 字体的名称

	GetDlgItem(IDC_RecvBroad)->SetFont(btn_style);
	GetDlgItem(IDC_Port)->SetFont(btn_style);
	GetDlgItem(IDC_StaticPort)->SetFont(btn_style);
	GetDlgItem(IDC_StaticBroad)->SetFont(btn_style);
	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CSmallToolDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSmallToolDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

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
HCURSOR CSmallToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

/******************************************************************************/
#define  ShowMessage(message)  show_view.AppendFormat(_T("%S"),  message )
#define  ShowTime()            show_view.AppendFormat(_T("%s"),CTime::GetCurrentTime().Format(_T("[%Y-%m-%d %H:%M:%S] ")))

CString show_view = _T("");
SOCKET sockfd = -1;
HANDLE broadrecv_thread;

/*****************************************************************************
函 数 名  : BroadrecvThread
功能描述  : 收广播并打印日志
输入参数  : LPVOID cwnd_mainview  窗口句柄

输出参数  : 无
返 回 值  : sockfd
调用函数  : 无
被调函数  : 无

修改历史      :
1.日    期   :   2016_12_29
作    者   :     xq
修改内容   :
*****************************************************************************/
unsigned __stdcall BroadrecvThread(LPVOID cwnd_mainview)
{
	CWnd *cwnd = (CWnd*)cwnd_mainview;  //得到控件句柄。

	const int buf_mess_len = 1024;
	char *buf_mess = (char*)malloc(buf_mess_len);
	if (NULL == buf_mess)
	{
		AfxMessageBox(_T("buf_mess Malloc Failed, Exit!"));
		return -1;
	}

	while (true) 
	{
		memset(buf_mess, '\0', buf_mess_len);
		ReciveMessages(sockfd, buf_mess, buf_mess_len);     //循环接收广播内容
		if (NULL == buf_mess)
		{
			AfxMessageBox(_T("Recive Messages Failed, Exit!"));
			FREE_POINTER(buf_mess);
			return -1;
		}
		ShowTime(); ShowMessage(buf_mess);
		//将接收到的内容写入文件
		CStdioFile file;                                   
		CFileException e;
		TCHAR* file_name = _T("broad.log");
		if (!file.Open(file_name, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite, &e))
		{
			AfxMessageBox(_T("File could not be opened %d"), e.m_cause);
			return -1;
		}
		file.WriteString(show_view);
		file.Close();

		cwnd->SetWindowText(show_view);
		cwnd->PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		Sleep(1000);
	}
	return 0;
}


/*****************************************************************************
函 数 名  : OnBnClickedRecvBroad
功能描述  : 按钮"接收广播"--加入广播网段
输入参数  : 

输出参数  : 无
返 回 值  : 无
调用函数  : 无
被调函数  : 无

修改历史      :
1.日    期   :   2016_12_29
作    者   :     xq
修改内容   :
*****************************************************************************/
int g_reset_flag = 0;             // 全局判断是否重新执行
void CSmallToolDlg::OnBnClickedRecvBroad()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);                        //更新控件数据到变量

	g_reset_flag++;
	if (g_reset_flag % 2 == 0)                 //重连后关闭上次的消息云套接字
	{

		GetDlgItem(IDC_RecvBroad)->SetWindowText(_T("接收广播"));
		closesocket(sockfd);
		sockfd = -1;

		TerminateThread(broadrecv_thread, 0);     //强制结束上次线程 
		CloseHandle(broadrecv_thread);
	}

	if (g_reset_flag % 2 == 1)                    //重连后关闭上次的消息云套接字
	{
		show_view = _T("");
		GetDlgItem(IDC_MainView)->SetWindowText(show_view);
		GetDlgItem(IDC_RecvBroad)->SetWindowText(_T("停止接收"));

		if (g_port.IsEmpty())
		{
			AfxMessageBox(_T("请输入端口号"));
		}
		else
		{
			sockfd = ConnectServer(sockfd, _ttoi(g_port));
			if (-1 == sockfd)
			{
				AfxMessageBox(_T("连接网络失败"));
				return;
			}


			CWnd *cwnd_mainview = GetDlgItem(IDC_MainView); //得到控件句柄
			// 创建线程
			unsigned broadrecv_threadID = NULL;
			broadrecv_thread = (HANDLE)_beginthreadex(NULL, 0, (unsigned int(__stdcall *)(void *))BroadrecvThread, (LPVOID)cwnd_mainview, 0, &broadrecv_threadID);
			if (NULL == broadrecv_thread)
			{
				AfxMessageBox(_T("创建广播接受线程失败"));
				return;
			}

			GetDlgItem(IDC_MainView)->SetWindowText(show_view);
			GetDlgItem(IDC_MainView)->PostMessage(WM_VSCROLL, SB_BOTTOM, 0); // 滑动栏在最下方
		}
	}
	UpdateData(FALSE);//更新视图      
}
