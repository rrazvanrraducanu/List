
// ListDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "List.h"
#include "ListDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CListDlg dialog



CListDlg::CListDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LIST_DIALOG, pParent)
	, m_strCombo(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_ctrlCombo);
	DDX_CBString(pDX, IDC_COMBO1, m_strCombo);
	DDX_Control(pDX, IDC_LIST1, m_ctrlList);
}

BEGIN_MESSAGE_MAP(CListDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_COMBO1, &CListDlg::OnSelchangeCombo1)
END_MESSAGE_MAP()


// CListDlg message handlers

BOOL CListDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_ctrlCombo.AddString("Icon");
	m_ctrlCombo.AddString("Small");
	m_ctrlCombo.AddString("List");
	m_ctrlCombo.AddString("Report");
	m_imageLarge.Create(
		IDB_BITMAP1, 32, 1, RGB(255, 255, 255));
	m_imageSmall.Create(
		IDB_BITMAP2, 16, 1, RGB(255, 255, 255));
	m_ctrlList.SetImageList(&m_imageLarge,LVSIL_NORMAL);
	m_ctrlList.SetImageList(&m_imageSmall,LVSIL_SMALL);
	// Create list view columns
	LV_COLUMN listColumn;
	char* arColumns[3] = { "Orase", "Universitati", "Simboluri" };
	listColumn.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	listColumn.fmt = LVCFMT_LEFT;
	listColumn.cx = 60;
	for (int nColumn = 0; nColumn < 3; nColumn++)
	{
		listColumn.iSubItem = nColumn;
		listColumn.pszText = arColumns[nColumn];
		m_ctrlList.InsertColumn(nColumn, &listColumn);
	}
	// Add list items
	LV_ITEM listItem;
	listItem.mask = LVIF_TEXT | LVIF_IMAGE;
	listItem.iSubItem = 0;
	char* arOrase[3] = { "Iasi", "Bucuresti", "Cluj" };
	char* arUniversitati[3] = { "Al.I.Cuza", "Bucuresti", "Babes Bolay" };
	char* arSimboluri[3] = { "Palatul Culturii", "Casa Poporului", "Universitatea" };
	for (int nItem = 0; nItem < 3; nItem++)
	{
	listItem.iItem = nItem;
	listItem.pszText = arOrase[nItem];
	listItem.iImage = nItem % 2;
	m_ctrlList.InsertItem(&listItem);
	m_ctrlList.SetItemText(nItem, 1, arUniversitati[nItem]);
	m_ctrlList.SetItemText(nItem, 2, arSimboluri[nItem]);
	}
	SetListView(LVS_REPORT);
	m_ctrlCombo.SetCurSel(2);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CListDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CListDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CListDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CListDlg::SetListView(DWORD dwNewStyle)
{
	// TODO: Add your implementation code here.
	DWORD dwOldStyle;
	HWND hWndList;
	hWndList = m_ctrlList.GetSafeHwnd();
	dwOldStyle = GetWindowLong(hWndList,
		GWL_STYLE);
	if ((dwOldStyle & LVS_TYPEMASK) !=
		dwNewStyle)
	{
		dwOldStyle &= ~LVS_TYPEMASK;
		dwNewStyle |= dwOldStyle;
		SetWindowLong(hWndList, GWL_STYLE,
			dwNewStyle);
	}
}


void CListDlg::OnSelchangeCombo1()
{
	// TODO: Add your control notification handler code here
	m_ctrlCombo.GetLBText(
		m_ctrlCombo.GetCurSel(), m_strCombo);
	CString str = m_strCombo;
	str.MakeUpper();
	if (str == "ICON") SetListView(LVS_ICON);
	else if (str == "REPORT")
		SetListView(LVS_REPORT);
	else if (str == "LIST") SetListView(LVS_LIST);
	else if (str == "SMALL")
		SetListView(LVS_SMALLICON);
}
