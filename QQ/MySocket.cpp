// MySocket.cpp : 实现文件
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


// CMySocket 成员函数


void CMySocket::OnAccept(int nErrorCode)
{
	CAsyncSocket::OnAccept(nErrorCode);
	CClientSocket* m_ClientSocket = new CClientSocket();
	Accept(*m_ClientSocket);
}

