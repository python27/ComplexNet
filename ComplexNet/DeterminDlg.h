#pragma once


// CDeterminDlg 对话框

class CDeterminDlg : public CDialog
{
	DECLARE_DYNAMIC(CDeterminDlg)

public:
	CDeterminDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDeterminDlg();
	virtual BOOL OnInitDialog();
	CString path;
	CString title;
	int flag;
// 对话框数据
	enum { IDD = IDD_DIALOG_DETERMIN };
    long m_determin_iterations;
	CString	m_determin_name;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual void OnOK();
	
	DECLARE_MESSAGE_MAP()
};
