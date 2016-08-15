#pragma once
#include "afxwin.h"


// CTalkDlg 对话框

class CTalkDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTalkDlg)

public:
	CTalkDlg(CString n, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTalkDlg();
	CString FriendNum;
	CString Title;

	BOOL	m_Send;			//是否开始发送
	BOOL	m_SendNext;		//是否继续发送
	BOOL	m_OKReceive;	//是否接收文件

	CString m_FileName;
	CString	m_ReceiveFile;

	CFile	m_File;			//接收的文件
	DWORD   m_FileSize;		//接收的文件大小
	DWORD   m_FileLen ;		//接收的文件长度

	CFile	m_SendFile;		//传送的文件
	DWORD	m_SendLen;		//已经传送的文件大小
	DWORD	m_SendFileLen;	//发送文件的大小
	DWORD	m_SendNum;		//当前发送次数

	CString GetFileName(CString filename);


// 对话框数据
	enum { IDD = IDD_TALK_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_MsgSend;
	CListBox m_ListTalk;
	afx_msg void OnBnClickedButtonsend();
	CEdit m_EditMsg;
	virtual BOOL OnInitDialog();
	virtual void PostNcDestroy();
	virtual void OnCancel();
	afx_msg void OnBnClickedButtonsendfile();
};
