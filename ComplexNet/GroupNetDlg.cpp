// GroupNetDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ComplexNet.h"
#include "GroupNetDlg.h"
#include "afxdialogex.h"


// CGroupNetDlg 对话框

IMPLEMENT_DYNAMIC(CGroupNetDlg, CDialog)

CGroupNetDlg::CGroupNetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGroupNetDlg::IDD, pParent)
{
	m_groupnet_name = _T("");
	m_groupnet_groups = 0;
	m_groupnet_nodes = 0;
	m_groupnet_proba = 0.0;
	m_groupnet_probb = 0.0;
}

CGroupNetDlg::~CGroupNetDlg()
{
}

void CGroupNetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_GROUPNET_NAME, m_groupnet_name);
	DDX_Text(pDX, IDC_EDIT_GROUPNET_GROUPS, m_groupnet_groups);
	DDX_Text(pDX, IDC_EDIT_GROUPNET_NODES, m_groupnet_nodes);
	DDX_Text(pDX, IDC_EDIT_GROUPNET_PROBA, m_groupnet_proba);
	DDX_Text(pDX, IDC_EDIT_GROUPNET_PROBB, m_groupnet_probb);
}


BEGIN_MESSAGE_MAP(CGroupNetDlg, CDialog)
END_MESSAGE_MAP()


// CGroupNetDlg 消息处理程序
void CGroupNetDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	m_groupnet_name.TrimLeft();
	m_groupnet_name.TrimRight();
	if(m_groupnet_name=="")
	{
	  MessageBox("Please input the filename you want to save");
	  return;
	}
    if(m_groupnet_nodes<4||m_groupnet_nodes>=50000)
	{
	  MessageBox(_T("The number of nodes you want to generate should be(>=4, <50000)"));
	  return;
	}
	if(m_groupnet_groups<2||m_groupnet_groups>m_groupnet_nodes/2)
	{
	  MessageBox(_T("The number of neigboring nodes (should be >=2, <=nodes/2"));
	  return;	
	}
	if(m_groupnet_proba>1||m_groupnet_proba<0)
	{
      MessageBox(LPCTSTR("The probability A should be>=0  <=1"),LPCTSTR("Information"),MB_OK|MB_ICONINFORMATION);
	  return;	
	}	
	if(m_groupnet_probb>1||m_groupnet_probb<0)
	{
      MessageBox(LPCTSTR("The probability B should be>=0  <=1"),LPCTSTR("Information"),MB_OK|MB_ICONINFORMATION);
	  return;	
	}	
	path=path+"\\NetFiles\\"+m_groupnet_name;
	path+=".net";
	CDialog::OnOK();
}