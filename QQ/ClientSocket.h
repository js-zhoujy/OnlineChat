#pragma once

// CClientSocket ÃüÁîÄ¿±ê

class CClientSocket : public CAsyncSocket
{
public:
	CClientSocket();
	CClientSocket(CString n);
	virtual ~CClientSocket();
	virtual void OnConnect(int nErrorCode);
	virtual void OnReceive(int nErrorCode);

	CString FriendNum;
	virtual void OnClose(int nErrorCode);
};


