#pragma once



// CDlgExampleNets 对话框

class CDlgExampleNets : public CDialog
{
	DECLARE_DYNAMIC(CDlgExampleNets)

public:
	CDlgExampleNets(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgExampleNets();
	virtual BOOL OnInitDialog();
// 对话框数据
	enum { IDD = IDD_DIALOG_EXAMPLENETS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CString m_netfile;
	CString path;
	CString title;
};
