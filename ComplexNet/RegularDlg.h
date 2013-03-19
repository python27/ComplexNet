#if !defined(AFX_REGULARDLG_H__78F35DA9_B944_4BF0_9BD0_BF5B5259CD66__INCLUDED_)
#define AFX_REGULARDLG_H__78F35DA9_B944_4BF0_9BD0_BF5B5259CD66__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RegularDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRegularDlg dialog

class CRegularDlg : public CDialog
{
// Construction
public:
	CRegularDlg(CWnd* pParent = NULL);   // standard constructor
    CString path;
// Dialog Data
	//{{AFX_DATA(CRegularDlg)
	enum { IDD = IDD_DIALOG_REGULAR };
	long	m_reg_nodes;
	long	m_reg_neighbors;
	CString	m_reg_name;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRegularDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRegularDlg)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REGULARDLG_H__78F35DA9_B944_4BF0_9BD0_BF5B5259CD66__INCLUDED_)
