// RandomDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ComplexNet.h"
#include "RandomDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRandomDlg dialog


CRandomDlg::CRandomDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRandomDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRandomDlg)
	m_ran_edges = 0;
	m_ran_name = _T("");
	m_ran_nodes = 0;
	//}}AFX_DATA_INIT
}


void CRandomDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRandomDlg)
	DDX_Text(pDX, IDC_EDIT_RANDOM_EDGES, m_ran_edges);
	DDX_Text(pDX, IDC_EDIT_RANDOM_NAME, m_ran_name);
	DDX_Text(pDX, IDC_EDIT_RANDOM_NODES, m_ran_nodes);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRandomDlg, CDialog)
	//{{AFX_MSG_MAP(CRandomDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRandomDlg message handlers

void CRandomDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	m_ran_name.TrimLeft();
	m_ran_name.TrimRight();
	if(m_ran_name=="")
	{
	  MessageBox("Please input the filename you want to save");
	  return;
	}
	if(m_ran_nodes<3||m_ran_nodes>50000)
	{
	  MessageBox("Please input number of nodes you want to generate (>=3, <50000)");
	  return;
	}
	if(m_ran_edges>=(m_ran_nodes-1)*m_ran_nodes/2||m_ran_edges<1)
	{
	  MessageBox("Please input number of expected edges (should be <=(nodes-1)nodes/2");
	  return;	
	}
    path=path+"\\NetFiles\\"+m_ran_name;
	path+=".net";
	CDialog::OnOK();

}
