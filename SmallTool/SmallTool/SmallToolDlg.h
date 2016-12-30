#include  "NetHelper.h"
// SmallToolDlg.h : 头文件
//

#pragma once
#define  FREE_POINTER(p)    free(p);p = NULL

// CSmallToolDlg 对话框
class CSmallToolDlg : public CDialogEx
{
// 构造
public:
	CSmallToolDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SMALLTOOL_DIALOG };
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
public:
	afx_msg void OnBnClickedRecvBroad();
	CString g_port;
};
