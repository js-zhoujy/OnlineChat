
// QQDlg.h : ͷ�ļ�
//

#pragma once
#include "MySocket.h"
#include "ClientSocket.h"
#include "TalkDlg.h"
#include "afxwin.h"
#include "afxcmn.h"
#include <list>
using namespace std;

typedef list<CClientSocket*> CSList;
typedef list<CTalkDlg*> TDList;

// CQQDlg �Ի���
class CQQDlg : public CDialogEx
{
// ����
public:
	CMySocket *m_ListenSocket;
	SOCKET m_client;

	CSList ClientSocketList;
	TDList TalkDlgList;
	
	CString groupFriend[10];
	CString groupIP[10];

	CQQDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_QQ_DIALOG };

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
	afx_msg void OnBnClickedlogin();
	CString m_num;
	CString m_code;
	afx_msg void OnBnClickedlogout();
	CString m_friend;
	afx_msg void OnBnClickedsearch();
	afx_msg void OnBnClickedClose();

	CIPAddressCtrl m_IPfriend;
	afx_msg void OnBnClickedconnectfriend();
	CEdit m_editNum;
	CEdit m_editCode;
	CButton m_buttonLogin;
	CEdit m_editFriend;
	CButton m_buttonSearch;
	CButton m_buttonConnectfriend;

	void ReceiveData();
	void CloseSock();



	CListBox m_ListGroup;
	afx_msg void OnBnClickedButtongroup();
	afx_msg void OnBnClickedButtonclear();
	afx_msg void OnBnClickedButtongrouptalk();
};
