// DeterminDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ComplexNet.h"
#include "DeterminDlg.h"
#include "afxdialogex.h"


// CDeterminDlg 对话框

IMPLEMENT_DYNAMIC(CDeterminDlg, CDialog)

CDeterminDlg::CDeterminDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDeterminDlg::IDD, pParent)
{
	m_determin_iterations = 0;
	m_determin_name = _T("");
}

CDeterminDlg::~CDeterminDlg()
{
}

void CDeterminDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_DETERMIN_ITERATIONS, m_determin_iterations);
	DDX_Text(pDX, IDC_EDIT_DETERMIN_NAME, m_determin_name);
}


BEGIN_MESSAGE_MAP(CDeterminDlg, CDialog)
END_MESSAGE_MAP()


// CDeterminDlg 消息处理程序
BOOL CDeterminDlg::OnInitDialog()
{
	SetWindowTextA(title);
	if(flag==1)
	GetDlgItem(IDC_STATIC_DETERMIN_ITERATIONS)->SetWindowTextA("总节点数");
	return CDialog::OnInitDialog();
}
void CDeterminDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
    m_determin_name.TrimLeft();
	m_determin_name.TrimRight();
	if(m_determin_name=="")
	{
	  MessageBox("Please input the filename you want to save");
	  return;
	}
	if(flag!=1&&(m_determin_iterations<1||m_determin_iterations>=1000))
	{
	  MessageBox("Please input the number of iterations (>=1, <1000)");
	  return;
	}
    if(flag==1&&(m_determin_iterations<1||m_determin_iterations>=1000000))
	{
	  MessageBox("Please input the number of nodes (>=1, <1000000)");
	  return;
	}
    path=path+"\\NetFiles\\"+m_determin_name;
	path+=".net";
	CDialog::OnOK();
}