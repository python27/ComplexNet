// DlgDrivers.cpp : 实现文件
//

#include "stdafx.h"
#include "ComplexNet.h"
#include "DlgDrivers.h"
#include "afxdialogex.h"


// DlgDrivers 对话框

IMPLEMENT_DYNAMIC(DlgDrivers, CDialogEx)

DlgDrivers::DlgDrivers(CWnd* pParent /*=NULL*/)
	: CDialogEx(DlgDrivers::IDD, pParent)
{

}

DlgDrivers::~DlgDrivers()
{
}

void DlgDrivers::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}



BEGIN_MESSAGE_MAP(DlgDrivers, CDialogEx)
END_MESSAGE_MAP()


// DlgDrivers 消息处理程序


BOOL DlgDrivers::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	this->MoveWindow(100, 100, 400, 600);
	CWnd* pWnd1 = this->GetDlgItem(IDC_STATIC_DRIVERS);
	pWnd1->MoveWindow(10, 10, 100, 30);

	CWnd* pWnd2 = this->GetDlgItem(IDC_EDIT_DRIVERS);
	pWnd2->MoveWindow(10, 60, 200, 200);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}
