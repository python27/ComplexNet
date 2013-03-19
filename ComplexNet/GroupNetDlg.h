#pragma once


// CGroupNetDlg 对话框

class CGroupNetDlg : public CDialog
{
	DECLARE_DYNAMIC(CGroupNetDlg)

public:
	CGroupNetDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CGroupNetDlg();
	CString path;
// 对话框数据
	enum { IDD = IDD_DIALOG_GROUPNET };
	CString	m_groupnet_name;
	long	m_groupnet_groups;
	long	m_groupnet_nodes;
	double	m_groupnet_proba;
	double	m_groupnet_probb;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual void OnOK();
	DECLARE_MESSAGE_MAP()
};
