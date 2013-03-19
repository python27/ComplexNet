// NWSmallDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ComplexNet.h"
#include "NWSmallDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNWSmallDlg dialog


CNWSmallDlg::CNWSmallDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNWSmallDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNWSmallDlg)
	m_nwsmall_name = _T("");
	m_nwsmall_neighbors = 0;
	m_nwsmall_nodes = 0;
	m_nwsmall_prob = 0.0;
	//}}AFX_DATA_INIT
}


void CNWSmallDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNWSmallDlg)
	DDX_Text(pDX, IDC_EDIT_NWSMALL_NAME, m_nwsmall_name);
	DDX_Text(pDX, IDC_EDIT_NWSMALL_NEIGHBORS, m_nwsmall_neighbors);
	DDX_Text(pDX, IDC_EDIT_NWSMALL_NODES, m_nwsmall_nodes);
	DDX_Text(pDX, IDC_EDIT_NWSMALL_PROB, m_nwsmall_prob);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNWSmallDlg, CDialog)
	//{{AFX_MSG_MAP(CNWSmallDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNWSmallDlg message handlers

void CNWSmallDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	m_nwsmall_name.TrimLeft();
	m_nwsmall_name.TrimRight();
	if(m_nwsmall_name=="")
	{
	  MessageBox("Please input the filename you want to save");
	  return;
	}
    if(m_nwsmall_nodes<4||m_nwsmall_nodes>=50000)
	{
	  MessageBox(_T("The number of nodes you want to generate should be(>=4, <50000)"));
	  return;
	}
	if(m_nwsmall_neighbors%2!=0||m_nwsmall_neighbors<2||m_nwsmall_neighbors>m_nwsmall_nodes/2)
	{
	  MessageBox(_T("The number of neigboring nodes (should be even number and >=2, <=nodes/2"));
	  return;	
	}
	if(m_nwsmall_prob>1||m_nwsmall_prob<0)
	{
      MessageBox(LPCTSTR("The probability of reconnection should be>=0  <=1"),LPCTSTR("Information"),MB_OK|MB_ICONINFORMATION);
	  return;	
	}	
	path=path+"\\NetFiles\\"+m_nwsmall_name;
	path+=".net";
	CDialog::OnOK();
}
