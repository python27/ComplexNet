#pragma once


// CWSSmallDlg 对话框

class CWSSmallDlg : public CDialog
{
	DECLARE_DYNAMIC(CWSSmallDlg)

public:
	CWSSmallDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CWSSmallDlg();
    CString path;
// 对话框数据
	enum { IDD = IDD_DIALOG_WSSMALL };
    CString	m_wssmall_name;
	long	m_wssmall_neighbors;
	long	m_wssmall_nodes;
	double	m_wssmall_prob;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
    virtual void OnOK();
	DECLARE_MESSAGE_MAP()
};


