
// ListDlg.h : header file
//

#pragma once


// CListDlg dialog
class CListDlg : public CDialogEx
{
// Construction
public:
	CListDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LIST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	CImageList m_imageLarge;
	CImageList m_imageSmall;
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_ctrlCombo;
	CString m_strCombo;
	CListCtrl m_ctrlList;
	void SetListView(DWORD dwNewStyle);
	afx_msg void OnSelchangeCombo1();
};
