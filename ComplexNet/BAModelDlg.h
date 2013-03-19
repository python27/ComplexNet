#if !defined(AFX_BAMODELDLG_H__0FFC9B53_4500_4131_8CA9_7EEE27CF30F6__INCLUDED_)
#define AFX_BAMODELDLG_H__0FFC9B53_4500_4131_8CA9_7EEE27CF30F6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BAModelDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBAModelDlg dialog

class CBAModelDlg : public CDialog
{
// Construction
public:
	CBAModelDlg(CWnd* pParent = NULL);   // standard constructor
    CString path;
// Dialog Data
	//{{AFX_DATA(CBAModelDlg)
	enum { IDD = IDD_DIALOG_BASCALEFREE };
	long	m_ba_nodes;
	CString	m_ba_name;
	long	m_ba_onodes;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBAModelDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBAModelDlg)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BAMODELDLG_H__0FFC9B53_4500_4131_8CA9_7EEE27CF30F6__INCLUDED_)
