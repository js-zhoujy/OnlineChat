// MySocket.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "QQ.h"
#include "MySocket.h"
#include "QQDlg.h"


// CMySocket

CMySocket::CMySocket()
{
}

CMySocket::~CMySocket()
{
}


// CMySocket ��Ա����


void CMySocket::OnAccept(int nErrorCode)
{
	CAsyncSocket::OnAccept(nErrorCode);
	CClientSocket* m_ClientSocket = new CClientSocket();
	Accept(*m_ClientSocket);
}

