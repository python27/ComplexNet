// RegularDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ComplexNet.h"
#include "RegularDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRegularDlg dialog


CRegularDlg::CRegularDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRegularDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRegularDlg)
	m_reg_nodes = 0;
	m_reg_neighbors = 0;
	m_reg_name = _T("");
	//}}AFX_DATA_INIT
}


void CRegularDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRegularDlg)
	DDX_Text(pDX, IDC_EDIT_REGULAR_NODES, m_reg_nodes);
	DDX_Text(pDX, IDC_EDIT_REGULAR_NEIGHBORS, m_reg_neighbors);
	DDX_Text(pDX, IDC_EDIT_REGULAR_NAME, m_reg_name);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRegularDlg, CDialog)
	//{{AFX_MSG_MAP(CRegularDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRegularDlg message handlers

void CRegularDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	m_reg_name.TrimLeft();
	m_reg_name.TrimRight();
	if(m_reg_name=="")
	{
	  MessageBox("Please input the filename you want to save");
	  return;
	}
	if(m_reg_nodes<3||m_reg_nodes>50000)
	{
	  MessageBox("Please input number of nodes you want to generate (>=3, <50000)");
	  return;
	}
	if(m_reg_neighbors%2!=0||m_reg_neighbors<2||m_reg_neighbors>m_reg_nodes-1)
	{
	  MessageBox("Please input number of neigboring nodes (should be even number and >=2, <=nodes-1)");
	  return;	
	}
    path=path+"\\NetFiles\\"+m_reg_name;
	path+=".net";
	CDialog::OnOK();
}
