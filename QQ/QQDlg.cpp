
// QQDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "QQ.h"
#include "QQDlg.h"
#include "afxdialogex.h"
#include <list>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CQQDlg �Ի���



CQQDlg::CQQDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CQQDlg::IDD, pParent)
	, m_num(_T("2013011454"))
	, m_code(_T("net2015"))
	, m_friend(_T("2013011454"))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CQQDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDITnum, m_num);
	DDX_Text(pDX, IDC_EDITcode, m_code);
	DDX_Text(pDX, IDC_EDITfriend, m_friend);
	DDX_Control(pDX, IDC_IPfriend, m_IPfriend);
	DDX_Control(pDX, IDC_EDITnum, m_editNum);
	DDX_Control(pDX, IDC_EDITcode, m_editCode);
	DDX_Control(pDX, IDlogin, m_buttonLogin);
	DDX_Control(pDX, IDC_EDITfriend, m_editFriend);
	DDX_Control(pDX, IDsearch, m_buttonSearch);
	DDX_Control(pDX, IDconnectfriend, m_buttonConnectfriend);
	DDX_Control(pDX, IDC_LISTgroup, m_ListGroup);
}

BEGIN_MESSAGE_MAP(CQQDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDlogin, &CQQDlg::OnBnClickedlogin)
	ON_BN_CLICKED(IDlogout, &CQQDlg::OnBnClickedlogout)
	ON_BN_CLICKED(IDsearch, &CQQDlg::OnBnClickedsearch)
	ON_BN_CLICKED(IDconnectfriend, &CQQDlg::OnBnClickedconnectfriend)
	ON_BN_CLICKED(IDC_BUTTONgroup, &CQQDlg::OnBnClickedButtongroup)
	ON_BN_CLICKED(IDC_BUTTONclear, &CQQDlg::OnBnClickedButtonclear)
	ON_BN_CLICKED(IDC_BUTTONgrouptalk, &CQQDlg::OnBnClickedButtongrouptalk)
END_MESSAGE_MAP()


// CQQDlg ��Ϣ�������

BOOL CQQDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	m_editFriend.EnableWindow(false);
	m_buttonSearch.EnableWindow(false);
	m_buttonConnectfriend.EnableWindow(false);
	m_ListenSocket=NULL;
	for(int i=0;i<10;i++)
	{
		groupFriend[i] = "";
		groupIP[i] = ""; 
	}

	m_ListenSocket = new CMySocket();
	if(!m_ListenSocket->Create(6666))
	{
		AfxMessageBox("�׽��ִ���ʧ�ܣ�");
		return FALSE;
	}
	if(!m_ListenSocket->Listen(5))
	{
		AfxMessageBox("����ʧ�ܣ�");
		m_ListenSocket->Close();
		return FALSE;
	}

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CQQDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CQQDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CQQDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CQQDlg::OnBnClickedlogin()
{
	UpdateData(TRUE);

	CString sIP = "166.111.140.14";
	USHORT sPort = 8000;
	
	WSADATA wsd;
	WSAStartup(MAKEWORD(2,2),&wsd);
	m_client = socket(AF_INET,SOCK_STREAM,0);

	sockaddr_in serveraddr; 
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.S_un.S_addr = inet_addr(sIP);
	serveraddr.sin_port = htons(sPort);

	int k=connect(m_client,(sockaddr*)&serveraddr,sizeof(serveraddr));

	if(k!=0)
	{
		AfxMessageBox("����ʧ�ܣ�");
		return;
	}

	if(m_code!="net2015")
	{
		AfxMessageBox("�û������������");
		return;
	}

	CString MessageIn = m_num + "_" + m_code;
	
	char buffer[1024];
	int i = send(m_client, MessageIn.GetBuffer(0), MessageIn.GetLength(),0);

	int num = recv(m_client, buffer, 1024, 0);
	buffer[num] = '\0';
	CString sTemp;
	sTemp.Format("%s",buffer);
	
	if(sTemp == "lol")
	{
		AfxMessageBox("��¼�ɹ���");
		m_editNum.EnableWindow(false);
		m_editCode.EnableWindow(false);
		m_buttonLogin.EnableWindow(false);
		m_editFriend.EnableWindow(true);
		m_buttonSearch.EnableWindow(true);

	}
}


void CQQDlg::OnBnClickedlogout()
{
	UpdateData(TRUE);

	CString MessageOut = "logout" + m_num;
	
	char buffer[1024];
	int i = send(m_client, MessageOut.GetBuffer(0), MessageOut.GetLength(),0);
	
	int num = recv(m_client, buffer, 1024, 0);
	buffer[num] = '\0';
	CString sTemp;
	sTemp.Format("%s",buffer);
	if(sTemp == "loo")
	{
		AfxMessageBox("���߳ɹ���");
		m_editNum.EnableWindow(true);
		m_editCode.EnableWindow(true);
		m_buttonLogin.EnableWindow(true);

		m_editFriend.EnableWindow(false);
		m_buttonSearch.EnableWindow(false);
		m_buttonConnectfriend.EnableWindow(false);

		delete m_ListenSocket;
		m_ListenSocket=NULL;
	}
	
}


void CQQDlg::OnBnClickedsearch()
{
	UpdateData(TRUE);

	CString MessageFriend = "q" + m_friend;

	char buffer[1024];
	int i = send(m_client, MessageFriend.GetBuffer(0), MessageFriend.GetLength(),0);
	
	int num = recv(m_client, buffer, 1024, 0);
	buffer[num] = '\0';
	CString sTemp;
	sTemp.Format("%s",buffer);
	if(sTemp == "n")
	{
		AfxMessageBox("��ѯ�ĺ��Ѳ����ߣ�");
		m_buttonConnectfriend.EnableWindow(false);
	}
	else
	{
		DWORD dwIP; 
		dwIP = inet_addr(sTemp);
		unsigned char *pIP = (unsigned char*)&dwIP;
		m_IPfriend.SetAddress(*pIP,  *(pIP+1),  *(pIP+2),  *(pIP+3));
		m_buttonConnectfriend.EnableWindow(true);
	}
	
}

void CQQDlg::OnBnClickedconnectfriend()
{
	UpdateData(TRUE);

	if(m_friend==m_num)
	{
		AfxMessageBox("�������Լ����죡");
		return;
	}
	
	CSList::iterator i;
	int kk=0;
	for(i=ClientSocketList.begin();i!=ClientSocketList.end();i++)
	{
		if((*i)->FriendNum==m_friend)
		{
			AfxMessageBox("������ú������죡");
			return;
		}
	}

	BYTE nFild[4];
	CString sIP;
	m_IPfriend.GetAddress(nFild[0], nFild[1], nFild[2], nFild[3]);
	sIP.Format("%d.%d.%d.%d",nFild[0], nFild[1], nFild[2], nFild[3]);
	
	CClientSocket* m_ClientSocket=new CClientSocket(m_friend);
	m_ClientSocket->Create();
	m_ClientSocket->Connect(sIP,6666);
}




void CQQDlg::OnBnClickedButtongroup()
{
	UpdateData(TRUE);
	for(int i=0;i<10;i++)
	{
		if(groupFriend[i] == m_friend)
		{
			AfxMessageBox("�ú����Ѿ���Ⱥ���б��У�");
			return;
		}
	}
	int i=0;
	while(groupFriend[i] != "")
		i++;
	if(i>=10)
	{
		AfxMessageBox("�Ѿ��ﵽ���Ⱥ���������ߣ�");
		return;
	}
	groupFriend[i] = m_friend;
	BYTE nFild[4];
	CString sIP;
	m_IPfriend.GetAddress(nFild[0], nFild[1], nFild[2], nFild[3]);
	sIP.Format("%d.%d.%d.%d",nFild[0], nFild[1], nFild[2], nFild[3]);
	groupIP[i] = sIP;
	m_ListGroup.AddString(m_friend);
}


void CQQDlg::OnBnClickedButtonclear()
{
	UpdateData(TRUE);
	for(int i=0;i<10;i++)
	{
		groupFriend[i] = "";
		groupIP[i] = "";
	}
	m_ListGroup.ResetContent();
}


void CQQDlg::OnBnClickedButtongrouptalk()
{
	if(groupFriend[0]=="")
	{
		AfxMessageBox("Ⱥ���б���Ϊ�գ�");
		return;
	}
	if(groupFriend[1]=="")
	{
		AfxMessageBox("Ⱥ������Ϊ1����˽�ģ�");
		return;
	}
	for(int i=0;groupFriend[i]!="";i++)
	{
		CClientSocket* m_ClientSocket=new CClientSocket(groupFriend[i]);
		m_ClientSocket->Create();
		m_ClientSocket->Connect(groupIP[i],6666);
	}
}
