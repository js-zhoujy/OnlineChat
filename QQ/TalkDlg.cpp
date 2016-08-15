// TalkDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "QQ.h"
#include "TalkDlg.h"
#include "afxdialogex.h"
#include "QQDlg.h"


// CTalkDlg 对话框

IMPLEMENT_DYNAMIC(CTalkDlg, CDialogEx)

CTalkDlg::CTalkDlg(CString n, CWnd* pParent /*=NULL*/)
	: CDialogEx(CTalkDlg::IDD, pParent)
	, m_MsgSend(_T(""))
{
	FriendNum = n;
}

CTalkDlg::~CTalkDlg()
{
}

void CTalkDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDITsendmsg, m_MsgSend);
	DDX_Control(pDX, IDC_LISTtalk, m_ListTalk);
	DDX_Control(pDX, IDC_EDITsendmsg, m_EditMsg);
}


BEGIN_MESSAGE_MAP(CTalkDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTONsend, &CTalkDlg::OnBnClickedButtonsend)
	ON_BN_CLICKED(IDC_BUTTONsendfile, &CTalkDlg::OnBnClickedButtonsendfile)
END_MESSAGE_MAP()


// CTalkDlg 消息处理程序


void CTalkDlg::OnBnClickedButtonsend()
{
	UpdateData(TRUE);
	if(m_MsgSend == "")
	{
		AfxMessageBox("请输入消息内容！");
		return;
	}

	CString ct;
	CTime time=CTime::GetCurrentTime();
	ct=time.Format("%H:%M:%S");
	CString msg = "MSG" + ((CQQDlg*)(AfxGetApp()->m_pMainWnd))->m_num + "  " +ct + '#' + m_MsgSend;

	CClientSocket* m_ClientSocket=NULL;

	TDList::iterator i;
	int k=0;
	for(i=((CQQDlg*)(AfxGetApp()->m_pMainWnd))->TalkDlgList.begin();i!=((CQQDlg*)(AfxGetApp()->m_pMainWnd))->TalkDlgList.end();i++)
	{
		if((*i)->FriendNum==this->FriendNum)
		{
			CSList::iterator c=((CQQDlg*)(AfxGetApp()->m_pMainWnd))->ClientSocketList.begin();
			for(int j=0;j<k;j++)
				c++;
			m_ClientSocket=*c;
			break;
		}
		k++;
	}
	
	m_ClientSocket->Send(msg, msg.GetLength());
	
	m_ListTalk.AddString(((CQQDlg*)(AfxGetApp()->m_pMainWnd))->m_num + "  " +ct);
	m_ListTalk.AddString(m_MsgSend);

	m_EditMsg.SetSel(0, -1);
	m_EditMsg.Clear();
	m_EditMsg.GetFocus();
}


BOOL CTalkDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetWindowText(Title);

	m_Send     = FALSE;
	m_SendNext = FALSE;
	m_OKReceive= TRUE;

	return TRUE;  
}


void CTalkDlg::PostNcDestroy()
{
	CDialogEx::PostNcDestroy();
}


void CTalkDlg::OnCancel()
{
	TDList::iterator i;
	int kk=0;
	CClientSocket* m_ClientSocket=NULL;

	for(i=((CQQDlg*)(AfxGetApp()->m_pMainWnd))->TalkDlgList.begin();i!=((CQQDlg*)(AfxGetApp()->m_pMainWnd))->TalkDlgList.end();i++)
	{
		if((*i)->FriendNum==this->FriendNum)
		{
			CSList::iterator t=((CQQDlg*)(AfxGetApp()->m_pMainWnd))->ClientSocketList.begin();
			for(int j=0;j<kk;j++)
				t++;
			m_ClientSocket=*t;
			((CQQDlg*)(AfxGetApp()->m_pMainWnd))->ClientSocketList.erase(t);
			((CQQDlg*)(AfxGetApp()->m_pMainWnd))->TalkDlgList.erase(i);
			break;
		}
		kk++;
	}
	m_ClientSocket->Close();

	delete m_ClientSocket;

	CDialogEx::OnCancel();
}


void CTalkDlg::OnBnClickedButtonsendfile()
{
	CClientSocket* m_ClientSocket=NULL;

	TDList::iterator i;
	int k=0;
	for(i=((CQQDlg*)(AfxGetApp()->m_pMainWnd))->TalkDlgList.begin();i!=((CQQDlg*)(AfxGetApp()->m_pMainWnd))->TalkDlgList.end();i++)
	{
		if((*i)->FriendNum==this->FriendNum)
		{
			CSList::iterator c=((CQQDlg*)(AfxGetApp()->m_pMainWnd))->ClientSocketList.begin();
			for(int j=0;j<k;j++)
				c++;
			m_ClientSocket=*c;
			break;
		}
		k++;
	}
	if(m_Send==FALSE)
	{
		CFileDialog fDlg (TRUE,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,NULL,this);
		if (fDlg.DoModal()==IDOK)
			m_FileName = fDlg.GetPathName();
		else{
			AfxMessageBox("未选择文件！");
			return;
		}

		m_SendFile.Abort();
		m_SendFile.Open(m_FileName,CFile::modeRead|CFile::typeBinary);
		m_SendFileLen = m_SendFile.GetLength();

		CString fileinfo;
		fileinfo = "MSQ" + m_FileName + '#';		//发送传输文件请求和文件名

		CString filesize;
		filesize.Format("%i",m_SendFileLen);
		fileinfo = fileinfo + filesize;

		//m_ListTalk.AddString(fileinfo);

		m_SendNum = 0;
		m_SendLen = 0;
		m_ClientSocket->Send(fileinfo,fileinfo.GetLength());
	}
	else
	{
		AfxMessageBox("当前传输任务未完成！");
		return;
	}
}

CString CTalkDlg::GetFileName(CString filename)
{
	int pos1 = filename.ReverseFind('#');
	int pos2 = filename.ReverseFind('\\');
	CString name = filename.Mid(pos2+1,pos1-pos2-1);
	return name;
}