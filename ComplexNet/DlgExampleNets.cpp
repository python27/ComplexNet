// DlgExampleNets.cpp : 实现文件
//

#include "stdafx.h"
#include "ComplexNet.h"
#include "DlgExampleNets.h"
#include "afxdialogex.h"


// CDlgExampleNets 对话框

IMPLEMENT_DYNAMIC(CDlgExampleNets, CDialog)

CDlgExampleNets::CDlgExampleNets(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgExampleNets::IDD, pParent)
	, m_netfile(_T(""))
{

}

CDlgExampleNets::~CDlgExampleNets()
{
}

void CDlgExampleNets::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EXAMPLE_NETFILE, m_netfile);
}


BEGIN_MESSAGE_MAP(CDlgExampleNets, CDialog)
	ON_BN_CLICKED(IDOK, &CDlgExampleNets::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgExampleNets 消息处理程序
BOOL CDlgExampleNets::OnInitDialog()
{
	SetWindowTextA(title);
	return CDialog::OnInitDialog();
}

void CDlgExampleNets::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_netfile.TrimLeft();
	m_netfile.TrimRight();
	if(m_netfile=="")
	{
	  MessageBox(_T("Please input the filename you want to save"));
	  return;
	}
    path=path+"\\NetFiles\\"+m_netfile;
	path+=".net";
	CDialog::OnOK();
}
