
// MFCStudyDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCStudy.h"
#include "MFCStudyDlg.h"
#include "afxdialogex.h"
#include "afxpropertygridctrl.h"
#include "CShapes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CMFCStudyDlg 대화 상자



CMFCStudyDlg::CMFCStudyDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCSTUDY_DIALOG, pParent)
	, m_bInitialized(false)
	, m_pShapes(nullptr)
	, m_MainDC(nullptr)
	, m_eMode(EClickMode::Create)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CMFCStudyDlg::~CMFCStudyDlg()
{
	if (m_pShapes)
		delete m_pShapes;
}

void CMFCStudyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCStudyDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


// CMFCStudyDlg 메시지 처리기

BOOL CMFCStudyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	Initialize();

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCStudyDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCStudyDlg::OnPaint()
{
	if (!m_bInitialized)
	{
		DrawBackBuffer();
		DrawMainBuffer();
		m_bInitialized = true;
	}

	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

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
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCStudyDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFCStudyDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	m_MousePos = CVector2::CPointToVector2(point);

	CShape* pClickedShape = m_pShapes->GetClickedShape();
	if (pClickedShape != nullptr)
	{
		CVector2 PrevPos = pClickedShape->GetPos();
		if (PrevPos != m_MousePos)
		{
			pClickedShape->SetPos(m_MousePos);
			pClickedShape->SetOverlapped(true);
			Refresh();
			m_eMode = EClickMode::Move;
		}
	}
}

void CMFCStudyDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_pShapes->CheckOverlap(CVector2::CPointToVector2(point));
}

void CMFCStudyDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	CShape* pClickedShape = m_pShapes->GetClickedShape();
	if (pClickedShape)
	{
		pClickedShape->SetOverlapped(false);
		m_pShapes->RemoveClickedShape();
		Refresh();
	}
	if (m_eMode == EClickMode::Move)
	{
		m_eMode = EClickMode::Create;
		return;
	}

	CShapeInfo ShapeInfo;
	ShapeInfo.Pos = CVector2::CPointToVector2(point);
	ShapeInfo.fThickness = 8.0f;
	ShapeInfo.eShapeTypes = EShapeTypes::Circle;
	m_pShapes->AddShape<CCircle>(ShapeInfo);

	Refresh();
}

void CMFCStudyDlg::Initialize()
{
	InitDC();
	InitGridCtrl();
	InitImage();

	m_pShapes = new CShapes(&m_Image);

	DrawScreen();
}

void CMFCStudyDlg::InitImage()
{
	int nBitsPerPixel = 8;

	if (!m_Image.IsNull())
	{
		m_Image.Destroy();
	}

	CRect ClientRect;
	GetClientRect(&ClientRect);

	m_Image.Create(ClientRect.Width(), ClientRect.Height(), nBitsPerPixel);
	unsigned char* p = (unsigned char*)m_Image.GetBits();

	if (nBitsPerPixel == 8)
	{
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; ++i)
		{
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		}
		m_Image.SetColorTable(0, 256, rgb);
	}

	ClearImage();
}

void CMFCStudyDlg::InitDC()
{
	CRect ClientRect;
	GetClientRect(&ClientRect);

	m_MainDC = GetDC();
	m_BackBufDC.CreateCompatibleDC(m_MainDC);
	m_BackBufBit.CreateCompatibleBitmap(m_MainDC, ClientRect.Width(), ClientRect.Height());
	m_BackBufDC.SelectObject(m_BackBufBit);
}

void CMFCStudyDlg::InitGridCtrl()
{
	HDITEM Item;
	Item.mask = HDI_WIDTH;
	Item.cxy = 100;

	auto pControl = GetControl<CMFCPropertyGridCtrl>(IDC_GRIDPROPERTY);
	pControl->GetHeaderCtrl().SetItem(0, &Item);

	CMFCPropertyGridProperty* pGroup = new CMFCPropertyGridProperty(_T("Shapes"));
	pControl->AddProperty(pGroup);
}

void CMFCStudyDlg::DrawShapesInBackBuffer()
{
	m_pShapes->Draw();
}

void CMFCStudyDlg::DrawBackBuffer()
{
	m_Image.Draw(m_BackBufDC, 0, 0);
}

void CMFCStudyDlg::DrawMainBuffer()
{
	auto pControl = GetControl<CMFCPropertyGridCtrl>(IDC_GRIDPROPERTY);
	CRect ControlRect;
	pControl->GetWindowRect(&ControlRect);
	ScreenToClient(&ControlRect);

	CRect ClientRect;
	GetClientRect(&ClientRect);
	m_MainDC->BitBlt(0, 0, ControlRect.left, ClientRect.Height(), &m_BackBufDC, 0, 0, SRCCOPY);
}

void CMFCStudyDlg::DrawScreen()
{
	DrawShapesInBackBuffer();
	DrawBackBuffer();
	DrawMainBuffer();
}

void CMFCStudyDlg::Refresh()
{
	RenewGridCtrl();
	ClearImage();
	DrawScreen();
}

void CMFCStudyDlg::ClearImage()
{
	unsigned char* p = (unsigned char*)m_Image.GetBits();
	for (int y = 0; y < m_Image.GetHeight(); ++y)
	{
		memset(p + (y * m_Image.GetPitch()), 0xff, m_Image.GetWidth());
	}
}

void CMFCStudyDlg::RenewGridCtrl()
{
	auto pControl = GetControl<CMFCPropertyGridCtrl>(IDC_GRIDPROPERTY);
	auto Shapes = m_pShapes->GetShapes();

	pControl->RemoveAll();
	CMFCPropertyGridProperty* pGroup = new CMFCPropertyGridProperty(_T("Shapes"));
	for (int i = 0; i < Shapes.size(); ++i)
	{
		CVector2 Pos = Shapes[i]->GetPos();
		std::wstring OutputStr = Pos.ToString();

		std::wstring PropertyName;
		{
			std::wstring Name = Shapes[i]->GetName();
			PropertyName = Name + std::to_wstring(i);
		}
		pGroup->AddSubItem(new CMFCPropertyGridProperty(PropertyName.c_str(), OutputStr.c_str()));
	}

	pControl->AddProperty(pGroup);
}
