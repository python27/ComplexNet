#pragma once


// CNetFileSaveAs 对话框

class CNetFileSaveAs : public CDialog
{
	DECLARE_DYNAMIC(CNetFileSaveAs)

public:
	CNetFileSaveAs(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CNetFileSaveAs();
    CString path;
// 对话框数据
	enum { IDD = IDD_DIALOG_SAVEFILE };
	CString	m_savefile_name;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual void OnOK();
	DECLARE_MESSAGE_MAP()
};
