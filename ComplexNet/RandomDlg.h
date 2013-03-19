#if !defined(AFX_RANDOMDLG_H__7FD1BEF4_D3F1_4918_B2C9_F310AF0D482F__INCLUDED_)
#define AFX_RANDOMDLG_H__7FD1BEF4_D3F1_4918_B2C9_F310AF0D482F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RandomDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRandomDlg dialog

class CRandomDlg : public CDialog
{
// Construction
public:
	CRandomDlg(CWnd* pParent = NULL);   // standard constructor
    CString path;

// Dialog Data
	//{{AFX_DATA(CRandomDlg)
	enum { IDD = IDD_DIALOG_RANDOM };
	long	m_ran_edges;
	CString	m_ran_name;
	long	m_ran_nodes;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRandomDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRandomDlg)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RANDOMDLG_H__7FD1BEF4_D3F1_4918_B2C9_F310AF0D482F__INCLUDED_)
