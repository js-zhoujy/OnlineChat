#pragma once
#include "afxwin.h"


// CTalkDlg �Ի���

class CTalkDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTalkDlg)

public:
	CTalkDlg(CString n, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTalkDlg();
	CString FriendNum;
	CString Title;

	BOOL	m_Send;			//�Ƿ�ʼ����
	BOOL	m_SendNext;		//�Ƿ��������
	BOOL	m_OKReceive;	//�Ƿ�����ļ�

	CString m_FileName;
	CString	m_ReceiveFile;

	CFile	m_File;			//���յ��ļ�
	DWORD   m_FileSize;		//���յ��ļ���С
	DWORD   m_FileLen ;		//���յ��ļ�����

	CFile	m_SendFile;		//���͵��ļ�
	DWORD	m_SendLen;		//�Ѿ����͵��ļ���С
	DWORD	m_SendFileLen;	//�����ļ��Ĵ�С
	DWORD	m_SendNum;		//��ǰ���ʹ���

	CString GetFileName(CString filename);


// �Ի�������
	enum { IDD = IDD_TALK_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
