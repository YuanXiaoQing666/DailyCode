#include  "NetHelper.h"
// SmallToolDlg.h : ͷ�ļ�
//

#pragma once
#define  FREE_POINTER(p)    free(p);p = NULL

// CSmallToolDlg �Ի���
class CSmallToolDlg : public CDialogEx
{
// ����
public:
	CSmallToolDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SMALLTOOL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRecvBroad();
	CString g_port;
};
