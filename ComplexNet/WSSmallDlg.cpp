// WSSmallDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ComplexNet.h"
#include "WSSmallDlg.h"
#include "afxdialogex.h"


// CWSSmallDlg 对话框

IMPLEMENT_DYNAMIC(CWSSmallDlg, CDialog)

CWSSmallDlg::CWSSmallDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWSSmallDlg::IDD, pParent)
{
	m_wssmall_name = _T("");
	m_wssmall_neighbors = 0;
	m_wssmall_nodes = 0;
	m_wssmall_prob = 0.0;
}

CWSSmallDlg::~CWSSmallDlg()
{
}

void CWSSmallDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_WSSMALL_NAME, m_wssmall_name);
	DDX_Text(pDX, IDC_EDIT_WSSMALL_NEIGHBORS, m_wssmall_neighbors);
	DDX_Text(pDX, IDC_EDIT_WSSMALL_NODES, m_wssmall_nodes);
	DDX_Text(pDX, IDC_EDIT_WSSMALL_PROB, m_wssmall_prob);
}


BEGIN_MESSAGE_MAP(CWSSmallDlg, CDialog)
END_MESSAGE_MAP()


// CWSSmallDlg 消息处理程序
void CWSSmallDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	m_wssmall_name.TrimLeft();
	m_wssmall_name.TrimRight();
	if(m_wssmall_name=="")
	{
	  MessageBox(_T("Please input the filename you want to save"));
	  return;
	}
	if(m_wssmall_nodes<4||m_wssmall_nodes>=50000)
	{
	  MessageBox(_T("The number of nodes you want to generate should be(>=4, <50000)"));
	  return;
	}
	if(m_wssmall_neighbors%2!=0||m_wssmall_neighbors<2||m_wssmall_neighbors>m_wssmall_nodes/2)
	{
	  MessageBox(_T("The number of neigboring nodes (should be even number and >=2, <=nodes/2"));
	  return;	
	}
	if(m_wssmall_prob>1||m_wssmall_prob<0)
	{
      MessageBox(LPCTSTR("The probability of reconnection should be>=0  <=1"),LPCTSTR("Information"),MB_OK|MB_ICONINFORMATION);
	  return;	
	}	
    path=path+"\\NetFiles\\"+m_wssmall_name;
	path+=".net";
	CDialog::OnOK();
}