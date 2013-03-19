// DlgCommuNumSet.cpp : 实现文件
//

#include "stdafx.h"
#include "ComplexNet.h"
#include "DlgCommuNumSet.h"
#include "afxdialogex.h"
#include "Network.h"

// CDlgCommuNumSet 对话框

IMPLEMENT_DYNAMIC(CDlgCommuNumSet, CDialogEx)

CDlgCommuNumSet::CDlgCommuNumSet(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgCommuNumSet::IDD, pParent)
{

	m_Commu_One_Num = 0;
	m_Commu_Two_Num = 0;
}

CDlgCommuNumSet::~CDlgCommuNumSet()
{
}

void CDlgCommuNumSet::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_COMMUNITY_ONE, m_Commu_One_Num);
	DDX_Text(pDX, IDC_COMMUNITY_TWO, m_Commu_Two_Num);
}


BEGIN_MESSAGE_MAP(CDlgCommuNumSet, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgCommuNumSet::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgCommuNumSet 消息处理程序


void CDlgCommuNumSet::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);    

	CDialogEx::OnOK();
}
