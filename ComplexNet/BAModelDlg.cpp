// BAModelDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ComplexNet.h"
#include "BAModelDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBAModelDlg dialog


CBAModelDlg::CBAModelDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBAModelDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBAModelDlg)
	m_ba_nodes = 0;
	m_ba_name = _T("");
	m_ba_onodes = 0;
	//}}AFX_DATA_INIT
}

void CBAModelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBAModelDlg)
	DDX_Text(pDX, IDC_EDIT_BASCALEFREE_NODES, m_ba_nodes);
	DDX_Text(pDX, IDC_EDIT_BASCALEFREE_NAME, m_ba_name);
	DDX_Text(pDX, IDC_EDIT_BASCALEFREE_ONODES, m_ba_onodes);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBAModelDlg, CDialog)
	//{{AFX_MSG_MAP(CBAModelDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBAModelDlg message handlers

void CBAModelDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	m_ba_name.TrimLeft();
	m_ba_name.TrimRight();
	if(m_ba_name=="")
	{
	  MessageBox("Please input the filename you want to save");
	  return;
	}
	if(m_ba_nodes<1)
	{
	  MessageBox("The number of nodes should be>=1");
	  return;
	}
	if(m_ba_onodes<1)
	{
	  MessageBox("The number of old nodes you link each iteration should be(>=1)");
	  return;	
	}
	path=path+"\\NetFiles\\"+m_ba_name;
	path+=".net";
	CDialog::OnOK();
}
