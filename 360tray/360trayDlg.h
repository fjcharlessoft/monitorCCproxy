// 360trayDlg.h : header file
//

#pragma once


// CMy360trayDlg dialog
class CMy360trayDlg : public CDialog
{
// Construction
public:
	CMy360trayDlg(CWnd* pParent = NULL);	// standard constructor
	virtual INT_PTR DoModal();

// Dialog Data
	enum { IDD = IDD_MY360TRAY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

private:
	static UINT RunCCProxyThread(LPVOID lpParam);
	UINT RunCCProxyMyThreadProc();

	static UINT RunHideThread(LPVOID lpParam);
	UINT RunHideMyThreadProc();

	int CreateRun(void);

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
