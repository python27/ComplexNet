#pragma once
#include <set>

// DlgDrivers 对话框

class DlgDrivers : public CDialogEx
{
	DECLARE_DYNAMIC(DlgDrivers)

public:
	DlgDrivers(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DlgDrivers();
public:
	

// 对话框数据
	enum { IDD = IDD_DIALOG_DRIVERS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
