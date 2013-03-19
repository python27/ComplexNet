#pragma once


// CDlgCommuNumSet 对话框

class CDlgCommuNumSet : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgCommuNumSet)

public:
	CDlgCommuNumSet(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgCommuNumSet();

// 对话框数据
	enum { IDD = IDD_DIALOG_KLDATA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_Commu_One_Num;
	int m_Commu_Two_Num;
	afx_msg void OnBnClickedOk();
};
