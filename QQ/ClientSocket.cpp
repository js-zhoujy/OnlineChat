// ClientSocket.cpp : 实现文件
//

#include "stdafx.h"
#include "QQ.h"
#include "ClientSocket.h"
#include "QQDlg.h"
#include "TalkDlg.h"
#include <list>
using namespace std;

const int MAXSENDNUM = 256;
// CClientSocket

CClientSocket::CClientSocket()
{
}

CClientSocket::CClientSocket(CString n)
{
	FriendNum = n;
}

CClientSocket::~CClientSocket()
{
}


// CClientSocket 成员函数


void CClientSocket::OnConnect(int nErrorCode)
{
	if(nErrorCode)
	{
		AfxMessageBox("连接失败，请重试！");
		return;
	}
	
	CSList::iterator i;
	int k=0;

	for(i=((CQQDlg*)(AfxGetApp()->m_pMainWnd))->ClientSocketList.begin();i!=((CQQDlg*)(AfxGetApp()->m_pMainWnd))->ClientSocketList.end();i++)
	{
		if((*i)->FriendNum==FriendNum)
		{
			TDList::iterator t;
			for(int j=0;j<k;j++)
				t++;
			(*t)->ShowWindow(SW_SHOWNORMAL);
			return;
		}
		k++;
	}
	((CQQDlg*)(AfxGetApp()->m_pMainWnd))->ClientSocketList.push_back(this);

	CString MsgID = "MID" + ((CQQDlg*)(AfxGetApp()->m_pMainWnd))->m_num;
	this->Send(MsgID, MsgID.GetLength());

	CTalkDlg* m_TalkDlg = new CTalkDlg(this->FriendNum);
	m_TalkDlg->Title = "正在与" + this->FriendNum + "聊天...";
	m_TalkDlg->Create(IDD_TALK_DIALOG);
	m_TalkDlg->ShowWindow(SW_SHOWNORMAL);
	((CQQDlg*)(AfxGetApp()->m_pMainWnd))->TalkDlgList.push_back(m_TalkDlg);
}

void CClientSocket::OnReceive(int nErrorCode)
{
	char* buffer = (char*)LocalAlloc(LMEM_FIXED,MAXSENDNUM+4);
	int n=Receive(buffer,MAXSENDNUM+4);
	if(n==SOCKET_ERROR)
	{
		AfxMessageBox("错误！");
		return;
	}
	*(buffer+n)='\0';
	CString dd = _T("");
	for(int j=0;j<3;j++)
		dd+=*(buffer+j);

	if(dd=="MSG")
	{
		CString sTemp;
		sTemp.Format("%s",buffer+3);
		
		int k=sTemp.Find('#');
		CString pHead = sTemp.Left(k);
		sTemp.Delete(0,k+1);

		CSList::iterator i;
		int kk=0;
		CTalkDlg* m_TalkDlg=NULL;

		for(i=((CQQDlg*)(AfxGetApp()->m_pMainWnd))->ClientSocketList.begin();i!=((CQQDlg*)(AfxGetApp()->m_pMainWnd))->ClientSocketList.end();i++)
		{
			if((*i)->FriendNum==this->FriendNum)
			{
				TDList::iterator t=((CQQDlg*)(AfxGetApp()->m_pMainWnd))->TalkDlgList.begin();
				for(int j=0;j<kk;j++)
					t++;
				m_TalkDlg=*t;
				break;
			}
			kk++;
		}

		HWND h=m_TalkDlg->GetSafeHwnd();
		CTalkDlg *pWnd=(CTalkDlg*)CWnd::FromHandle(h);
		pWnd->m_ListTalk.AddString(pHead);
		pWnd->m_ListTalk.AddString(sTemp);

		LocalFree(buffer);
	}
	else if(dd=="MID")
	{
		CString sTemp;
		sTemp.Format("%s",buffer+3);
		
		this->FriendNum=sTemp;

		CSList::iterator i;
		int kk=0;

		for(i=((CQQDlg*)(AfxGetApp()->m_pMainWnd))->ClientSocketList.begin();i!=((CQQDlg*)(AfxGetApp()->m_pMainWnd))->ClientSocketList.end();i++)
		{
			if((*i)->FriendNum==this->FriendNum)
			{
				TDList::iterator t;
				for(int j=0;j<kk;j++)
					t++;
				(*t)->ShowWindow(SW_SHOWNORMAL);
				return;
			}
			kk++;
		}
		((CQQDlg*)(AfxGetApp()->m_pMainWnd))->ClientSocketList.push_back(this);

		CTalkDlg* m_TalkDlg = new CTalkDlg(this->FriendNum);
		m_TalkDlg->Title = "正在与" + this->FriendNum + "聊天..."; 
		m_TalkDlg->Create(IDD_TALK_DIALOG);
		m_TalkDlg->ShowWindow(SW_SHOWNORMAL);
		((CQQDlg*)(AfxGetApp()->m_pMainWnd))->TalkDlgList.push_back(m_TalkDlg);

		LocalFree(buffer);
	}

	else if(dd=="MSQ")		//第一次接收数据，接收文件信息
	{
		CString sTemp;
		sTemp.Format("%s",buffer+3);
		
		CSList::iterator i;
		int kk=0;
		CTalkDlg* m_TalkDlg=NULL;

		for(i=((CQQDlg*)(AfxGetApp()->m_pMainWnd))->ClientSocketList.begin();i!=((CQQDlg*)(AfxGetApp()->m_pMainWnd))->ClientSocketList.end();i++)
		{
			if((*i)->FriendNum==this->FriendNum)
			{
				TDList::iterator t=((CQQDlg*)(AfxGetApp()->m_pMainWnd))->TalkDlgList.begin();
				for(int j=0;j<kk;j++)
					t++;
				m_TalkDlg=*t;
				break;
			}
			kk++;
		}
		
		if(m_TalkDlg->m_OKReceive != TRUE)
			return;

		m_TalkDlg->m_ReceiveFile = sTemp;

		CString name = m_TalkDlg->GetFileName(m_TalkDlg->m_ReceiveFile);

		int pos = sTemp.ReverseFind('#');
		CString sizetemp = sTemp.Mid(pos+1, sTemp.GetLength()-pos-1);
		
		m_TalkDlg->m_ListTalk.AddString("好友正在向你发送文件" + name +",大小为" + sizetemp + "字节。");

		m_TalkDlg->m_FileSize = atoi(sizetemp);
		m_TalkDlg->m_FileLen = 0;

		
		if (AfxMessageBox("是否接收文件？",MB_YESNO)==IDYES)
		{
			BROWSEINFO bInfo;
			bInfo.hwndOwner = m_TalkDlg->m_hWnd;
			bInfo.pidlRoot  = NULL;
			char filename[MAX_PATH];
			char dir[MAX_PATH];
			memset(filename,0,MAX_PATH);
			memset(dir,0,MAX_PATH);

			bInfo.pszDisplayName = filename;
			bInfo.lpszTitle ="请选择目的路径";
			bInfo.ulFlags = BIF_BROWSEINCLUDEFILES|BIF_RETURNFSANCESTORS|BIF_RETURNONLYFSDIRS|BIF_BROWSEFORCOMPUTER;
			bInfo.lParam  = NULL;
			bInfo.lpfn  = NULL;
			bInfo.iImage = 0;

			LPITEMIDLIST lpList =  SHBrowseForFolder(&bInfo);

			CString filedir;
			if (SHGetPathFromIDList(lpList,dir))
			{
				m_TalkDlg->m_File.Abort();
				filedir = dir;
				filedir += "\\";
				m_TalkDlg->m_File.Open(filedir+name,CFile::modeCreate|CFile::modeWrite|CFile::typeBinary);
				m_TalkDlg->m_OKReceive = FALSE;		//接收完毕文件信息
				Send("SSF",3);						//发送开始接收文件信息
				return;
			}
		}
		else
		{
			Send("QSF",3);
			m_TalkDlg->m_OKReceive = TRUE;
			return;
		}
		
		LocalFree(buffer);
	}
	else if(dd == "MSF")		//接收数据
	{	
		CSList::iterator i;
		int kk=0;
		CTalkDlg* m_TalkDlg;
		
		for(i=((CQQDlg*)(AfxGetApp()->m_pMainWnd))->ClientSocketList.begin();i!=((CQQDlg*)(AfxGetApp()->m_pMainWnd))->ClientSocketList.end();i++)
		{
			if((*i)->FriendNum==this->FriendNum)
			{
				TDList::iterator t=((CQQDlg*)(AfxGetApp()->m_pMainWnd))->TalkDlgList.begin();
				for(int j=0;j<kk;j++)
					t++;
				m_TalkDlg=*t;
				break;
			}
			kk++;
		}
		
		int flen=n-3;
		char* s = (char*)LocalAlloc(LMEM_FIXED,flen);
		memset(s,0,flen);
		memcpy(s,buffer+3,flen);

		m_TalkDlg->m_FileLen += flen;
		m_TalkDlg->m_File.Write(s,flen);

		if (m_TalkDlg->m_FileLen>=m_TalkDlg->m_FileSize)  //接收完成
		{
			m_TalkDlg->m_File.Close();
			m_TalkDlg->m_OKReceive = TRUE;
			AfxMessageBox("文件接收完成！");
			Send("SSF",3);
		}
		else
			Send("SSF",3);		//继续接收

		LocalFree(buffer);
	}

	else if(dd=="QSF")		//取消传送文件
	{
		CSList::iterator i;
		int kk=0;
		CTalkDlg* m_TalkDlg;
		
		for(i=((CQQDlg*)(AfxGetApp()->m_pMainWnd))->ClientSocketList.begin();i!=((CQQDlg*)(AfxGetApp()->m_pMainWnd))->ClientSocketList.end();i++)
		{
			if((*i)->FriendNum==this->FriendNum)
			{
				TDList::iterator t=((CQQDlg*)(AfxGetApp()->m_pMainWnd))->TalkDlgList.begin();
				for(int j=0;j<kk;j++)
					t++;
				m_TalkDlg=*t;
				break;
			}
			kk++;
		}
		
		m_TalkDlg->m_Send = FALSE;
		m_TalkDlg->m_SendNext = FALSE;
		m_TalkDlg->m_SendFile.Close();
		AfxMessageBox("对方取消了文件接收！");
		LocalFree(buffer);
		return;
	}

	else if(dd == "SSF")	
	{
		CSList::iterator i;
		int kk=0;
		CTalkDlg* m_TalkDlg;
		
		for(i=((CQQDlg*)(AfxGetApp()->m_pMainWnd))->ClientSocketList.begin();i!=((CQQDlg*)(AfxGetApp()->m_pMainWnd))->ClientSocketList.end();i++)
		{
			if((*i)->FriendNum==this->FriendNum)
			{
				TDList::iterator t=((CQQDlg*)(AfxGetApp()->m_pMainWnd))->TalkDlgList.begin();
				for(int j=0;j<kk;j++)
					t++;
				m_TalkDlg=*t;
				break;
			}
			kk++;
		}

		m_TalkDlg->m_Send = TRUE;
		m_TalkDlg->m_SendNext = TRUE;


		if(m_TalkDlg->m_SendLen>=m_TalkDlg->m_SendFileLen)
		{
			m_TalkDlg->m_Send = FALSE;
			m_TalkDlg->m_SendNext = FALSE;
			m_TalkDlg->m_SendFile.Close();
			AfxMessageBox("文件发送完成！");
			return;
		}

		char* membuf= (char*)LocalAlloc(LMEM_FIXED,MAXSENDNUM+4);
		memset(membuf,0,MAXSENDNUM+4);
		*membuf = 'M';
		*(membuf+1) = 'S';
		*(membuf+2) = 'F';
		char *mk = membuf+3;

		int result;
		
		if ((m_TalkDlg->m_SendLen <m_TalkDlg->m_SendFileLen)&&((m_TalkDlg->m_SendLen+MAXSENDNUM)>m_TalkDlg->m_SendFileLen))
		{
			m_TalkDlg->m_SendFile.Read(mk,m_TalkDlg->m_SendFileLen-m_TalkDlg->m_SendLen);

			result = Send(membuf, m_TalkDlg->m_SendFileLen-m_TalkDlg->m_SendLen+3);
			if (result ==SOCKET_ERROR)
			{
				m_TalkDlg->m_Send = FALSE;
				m_TalkDlg->m_SendNext = FALSE;
				m_TalkDlg->m_SendFile.Close();
				LocalFree(membuf);
				AfxMessageBox("发送失败！");	
				return ;
			}
			m_TalkDlg->m_SendLen = m_TalkDlg->m_SendFileLen;
		}
		else
		{	
			m_TalkDlg->m_SendFile.Read(mk,MAXSENDNUM);
			result = Send(membuf, MAXSENDNUM+3);
			if (result ==SOCKET_ERROR)
			{
				m_TalkDlg->m_Send = FALSE;
				m_TalkDlg->m_SendNext = FALSE;
				m_TalkDlg->m_SendFile.Close();
				LocalFree(membuf);
				AfxMessageBox("发送失败");	
				return;
			}
			LocalFree(membuf);
			m_TalkDlg->m_SendLen +=MAXSENDNUM;
		}
		LocalFree(buffer);
	}

}


void CClientSocket::OnClose(int nErrorCode)
{
	CAsyncSocket::OnClose(nErrorCode);
	AfxMessageBox("对方已断开聊天！");

	CSList::iterator i;
	int kk=0;
	CTalkDlg* m_TalkDlg=NULL;

	for(i=((CQQDlg*)(AfxGetApp()->m_pMainWnd))->ClientSocketList.begin();i!=((CQQDlg*)(AfxGetApp()->m_pMainWnd))->ClientSocketList.end();i++)
	{
		if((*i)->FriendNum==this->FriendNum)
		{
			TDList::iterator t=((CQQDlg*)(AfxGetApp()->m_pMainWnd))->TalkDlgList.begin();
			for(int j=0;j<kk;j++)
				t++;
			m_TalkDlg=*t;
			((CQQDlg*)(AfxGetApp()->m_pMainWnd))->ClientSocketList.erase(i);
			((CQQDlg*)(AfxGetApp()->m_pMainWnd))->TalkDlgList.erase(t);
			break;
		}
		kk++;
	}

	delete m_TalkDlg;

	Close();
}
