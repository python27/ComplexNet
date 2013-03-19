#if !defined(AFX_NWSMALLDLG_H__92EC47D2_E6DB_4547_A608_05D4DAEA0110__INCLUDED_)
#define AFX_NWSMALLDLG_H__92EC47D2_E6DB_4547_A608_05D4DAEA0110__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NWSmallDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNWSmallDlg dialog

class CNWSmallDlg : public CDialog
{
// Construction
public:
	CNWSmallDlg(CWnd* pParent = NULL);   // standard constructor
    CString path;

// Dialog Data
	//{{AFX_DATA(CWSSAMLLDlg)
    enum { IDD = IDD_DIALOG_NWSMALL };
	CString	m_nwsmall_name;
	long	m_nwsmall_neighbors;
	long	m_nwsmall_nodes;
	double	m_nwsmall_prob;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNWSMALLDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNWSMALLDlg)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NWSMALLDLG_H__92EC47D2_E6DB_4547_A608_05D4DAEA0110__INCLUDED_)
