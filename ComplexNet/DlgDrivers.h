#pragma once
#include <set>

// DlgDrivers �Ի���

class DlgDrivers : public CDialogEx
{
	DECLARE_DYNAMIC(DlgDrivers)

public:
	DlgDrivers(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DlgDrivers();
public:
	

// �Ի�������
	enum { IDD = IDD_DIALOG_DRIVERS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
