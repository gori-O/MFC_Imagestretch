
// mfc_image_extentionDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "mfc_image_extention.h"
#include "mfc_image_extentionDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CmfcimageextentionDlg 대화 상자



CmfcimageextentionDlg::CmfcimageextentionDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC_IMAGE_EXTENTION_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CmfcimageextentionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CmfcimageextentionDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_x2, &CmfcimageextentionDlg::OnBnClickedBtnx2)
	ON_BN_CLICKED(IDC_BTN_x4, &CmfcimageextentionDlg::OnBnClickedBtnx4)
	ON_BN_CLICKED(IDC_BTN_x8, &CmfcimageextentionDlg::OnBnClickedBtnx8)
	ON_BN_CLICKED(IDC_BTN_file, &CmfcimageextentionDlg::OnBnClickedBtnfile)
	ON_BN_CLICKED(IDC_BTN_x1, &CmfcimageextentionDlg::OnBnClickedBtnx1)
END_MESSAGE_MAP()


// CmfcimageextentionDlg 메시지 처리기

BOOL CmfcimageextentionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	SetBackgroundColor(RGB(168, 168, 0));

	m_image.Load(L"cap.png");

	CRect win_rect, client_rect;
	GetWindowRect(win_rect);
	GetClientRect(client_rect);

	m_cx_margin = win_rect.Width() - client_rect.Width() + 4;
	m_cy_margin = win_rect.Height() - client_rect.Height() + 4;

	GetDlgItem(IDC_BTN_x2)->GetWindowRect(win_rect);
	ScreenToClient(win_rect);

	m_top_margin = win_rect.bottom;

	SetWindowPos(NULL, 0, 0,
		m_image.GetWidth() * m_zoom_level + m_cx_margin,
		m_image.GetHeight() * m_zoom_level + m_cy_margin + m_top_margin, SWP_NOMOVE);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CmfcimageextentionDlg::OnPaint()
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
	if (IsIconic())
	{
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		m_image.Draw(dc, 2, 2 + m_top_margin, m_image.GetWidth() * m_zoom_level, m_image.GetHeight() * m_zoom_level);
		//CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CmfcimageextentionDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CmfcimageextentionDlg::OnBnClickedBtnx2()
{
	m_zoom_level = 2;
	SetWindowPos(NULL, 0, 0,
		m_image.GetWidth() * m_zoom_level + m_cx_margin,
		m_image.GetHeight() * m_zoom_level + m_cy_margin + m_top_margin, SWP_NOMOVE);
	Invalidate();
}


void CmfcimageextentionDlg::OnBnClickedBtnx4()
{
	m_zoom_level = 4;
	SetWindowPos(NULL, 0, 0,
		m_image.GetWidth() * m_zoom_level + m_cx_margin,
		m_image.GetHeight() * m_zoom_level + m_cy_margin + m_top_margin, SWP_NOMOVE);
	Invalidate();
}


void CmfcimageextentionDlg::OnBnClickedBtnx8()
{
	m_zoom_level = 8;
	SetWindowPos(NULL, 0, 0,
		m_image.GetWidth() * m_zoom_level + m_cx_margin,
		m_image.GetHeight() * m_zoom_level + m_cy_margin + m_top_margin, SWP_NOMOVE);
	Invalidate();
}


void CmfcimageextentionDlg::OnBnClickedBtnfile()
{
	wchar_t name_filter[] = L"모든 파일(*.*)|*.*|Jpeg 파일(*.jpg)|*.jpg|PNG 파일(*.png)|*.png||";
	CFileDialog ins_dls(TRUE, L"jpg", L"*.jpg", OFN_HIDEREADONLY | OFN_NOCHANGEDIR, name_filter);
	ins_dls.m_ofn.nFilterIndex = 2;

	if (ins_dls.DoModal() == IDOK)
	{
		if (!m_image.IsNull()) m_image.Destroy();

		m_image.Load(ins_dls.GetPathName());
		SetWindowPos(NULL, 0, 0,
			m_image.GetWidth() * m_zoom_level + m_cx_margin,
			m_image.GetHeight() * m_zoom_level + m_cy_margin + m_top_margin, SWP_NOMOVE);
		Invalidate();
	}

}


void CmfcimageextentionDlg::OnBnClickedBtnx1()
{
	m_zoom_level = 1;
	SetWindowPos(NULL, 0, 0,
		m_image.GetWidth() * m_zoom_level + m_cx_margin,
		m_image.GetHeight() * m_zoom_level + m_cy_margin + m_top_margin, SWP_NOMOVE);
	Invalidate();
}
