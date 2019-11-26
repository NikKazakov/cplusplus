#include "pch.h"
#include "framework.h"
#include "l5.h"
#include "l5Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

Cl5Dlg::Cl5Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_l5_DIALOG, pParent)
	, m_MPosX_Echo(_T(""))
	, m_MPosY_Echo(_T(""))
	, m_Log(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cl5Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_MPOSX, m_MPosX_Echo);
	DDX_Text(pDX, IDC_MPOSY, m_MPosY_Echo);
	DDX_Text(pDX, IDC_LOG, m_Log);
	DDX_Control(pDX, IDC_HELP1, m_Help1);
	DDX_Control(pDX, IDC_HELP2, m_Help2);
	DDX_Control(pDX, IDC_HELP3, m_Help3);
	DDX_Control(pDX, IDC_HELP4, m_Help4);
	DDX_Control(pDX, IDC_HELP5, m_Help5);
	DDX_Control(pDX, IDC_HELP7, m_Help7);
	DDX_Control(pDX, IDC_EXTRAHELP, m_ExHelp);
}

BEGIN_MESSAGE_MAP(Cl5Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_BTN_QUIT, &Cl5Dlg::OnBnClickedBtnQuit)
	ON_BN_CLICKED(IDC_BTN_ADD, &Cl5Dlg::OnBnClickedBtnAdd)
	ON_BN_CLICKED(IDC_BTN_REMOVE, &Cl5Dlg::OnBnClickedBtnRemove)
	ON_BN_CLICKED(IDC_BTN_CONNECT, &Cl5Dlg::OnBnClickedBtnConnect)
	ON_BN_CLICKED(IDC_BTN_HELP, &Cl5Dlg::OnBnClickedBtnHelp)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOVING()
	ON_WM_RBUTTONDOWN()
	ON_BN_CLICKED(IDC_BTN_LOAD, &Cl5Dlg::OnBnClickedBtnLoad)
	ON_BN_CLICKED(IDC_BTN_SAVE, &Cl5Dlg::OnBnClickedBtnSave)
END_MESSAGE_MAP()

BOOL Cl5Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	ModifyStyle(WS_THICKFRAME, WS_BORDER);

	m_MPosX_Echo.Format(_T("0"));
	m_MPosY_Echo.Format(_T("0"));

	m_Log.Format(_T("Do something!"));

	Drag.isDragged = FALSE;

	InitRouters();
	
	Action = -1;

	Connect.isDrawing = FALSE;

	InitHelp();

	m_ExHelp.ShowWindow(SW_HIDE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void Cl5Dlg::InitRouters() {
	CRect rect(0, 0, 0, 0);
	bitmap_addr = "C:\\Users\\plox\\source\\repos\\l5\\l5\\res\\bitmap1.bmp";
	hBitMap = (HBITMAP)::LoadImageA(NULL, bitmap_addr, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	for (int i = 0; i < 100; i++) {
		m_R[i] = r{ new CStatic, FALSE };
		m_R[i].Router->Create(NULL, WS_CHILD | WS_VISIBLE | SS_BITMAP, rect, this);
		m_R[i].Router->SetBitmap(hBitMap);
		m_R[i].Router->ShowWindow(SW_HIDE);
		m_R[i].Router->MoveWindow(rect);
	}
}

CRect Cl5Dlg::GetRect(CStatic& wnd) {
	CRect rect;
	wnd.GetClientRect(&rect);
	wnd.ClientToScreen(&rect);
	ScreenToClient(&rect);
	return rect;
}

CRect Cl5Dlg::CheckRect(CRect rect) {
	if (rect.left <= 5) {
		rect.left = 6;
		rect.right = rect.left + 24;
	}
	if (rect.top <= 5) {
		rect.top = 6;
		rect.bottom = rect.top + 24;
	}
	if (rect.right >= 390) {
		rect.right = 389;
		rect.left = rect.right - 24;
	}
	if (rect.bottom >= 300) {
		rect.bottom = 299;
		rect.top = rect.bottom - 24;
	}
	return rect;
}

CPoint Cl5Dlg::CheckPoint(CPoint point) {
	if (point.x <= 5) {
		point.x = 6;
	}
	if (point.x >= 390) {
		point.x = 389;
	}
	if (point.y <= 5) {
		point.y = 6;
	}
	if (point.y >= 300) {
		point.y = 299;
	}
	return point;
}

int Cl5Dlg::FindClickedR(CPoint point) {
	CRect rect;
	int size = sizeof(m_R) / sizeof(*m_R);
	for (int i = 0; i < size; i++) {
		rect = GetRect(*m_R[i].Router);
		if (PtInRect(&rect, point)) {
			return i;
		}
	}
	return -1;
}

void Cl5Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
		CDialogEx::OnSysCommand(nID, lParam);
}

void Cl5Dlg::OnMoving(UINT fwSide, LPRECT pRect)
{
	CDialogEx::OnMoving(fwSide, pRect);
	DrawConnections();
}


void Cl5Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	switch (Action) {
	case 1: {
		Add(point);
		break;
	}
	case 2: {
		int a = FindClickedR(point);
		if (a >= 0) {
			Remove(a);
		}
		break;
	}
	case 3: {
			BeginConnect(point);
		break;
	}
	case 4: {
		break;
	}
	default: {
		int a = FindClickedR(point);
		if (a >= 0) {
			Drag.Router = m_R[a].Router;
			m_Log.Format(_T("Router %d is dragged"), a);
			BeginDrag(point);
		}
	}
	}

	UpdateData(FALSE);

	CDialogEx::OnLButtonDown(nFlags, point);
}

void Cl5Dlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (Drag.isDragged) {
		EndDrag(point);
	}
	else if (Connect.isDrawing) {
		EndConnect(point);
	}
	UpdateData(FALSE);
	CDialogEx::OnLButtonUp(nFlags, point);
}

void Cl5Dlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	m_ExHelp.ShowWindow(SW_HIDE);
	Action = -1;
	CDialogEx::OnRButtonDown(nFlags, point);
}

void Cl5Dlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if (Drag.isDragged) {
		IsDragged(point);
	}
	else if (Connect.isDrawing) {
		IsConnecting(point);
	}
	m_MPosX_Echo.Format(_T("%d"), point.x);
	m_MPosY_Echo.Format(_T("%d"), point.y);
	UpdateData(FALSE);

	CDialogEx::OnMouseMove(nFlags, point);
}


void Cl5Dlg::BeginDrag(CPoint point) {
	SetCapture();
	CRect rect = GetRect(*Drag.Router);
	Drag.xOffset = point.x - rect.left;
	Drag.yOffset = point.y - rect.top;
	Drag.isDragged = TRUE;
	UpdateData(FALSE);
}

void Cl5Dlg::IsDragged(CPoint point) {
	point.x = point.x - Drag.xOffset;
	point.y = point.y - Drag.yOffset;
	CRect rect = GetRect(*Drag.Router);
	rect.MoveToXY(point);
	Drag.Router->MoveWindow(CheckRect(rect));
	DrawConnections();
	UpdateData(FALSE);
}

void Cl5Dlg::EndDrag(CPoint point) {
	ReleaseCapture();
	Drag.isDragged = FALSE;
	UpdateData(FALSE);
}


void Cl5Dlg::OnBnClickedBtnAdd()
{
		int size = sizeof(m_R) / sizeof(*m_R);
		for (int i = 0; i < size; i++) {
			if (!m_R[i].isEnabled) {
				m_add_id = i;
				break;
			}
		}
		if (m_add_id == -1) {
			m_Log.Format(_T("Limit reached!"));
		}
		else {
			m_Log.Format(_T("Click anywhere"));
			m_ExHelp.ShowWindow(SW_SHOW);
			Action = 1;
		}
	UpdateData(FALSE);
}

void Cl5Dlg::Add(CPoint point) {
	int l = point.x - 12;
	int t = point.y - 12;
	int r = point.x + 12;
	int b = point.y + 12;
	m_R[m_add_id].Router->ShowWindow(SW_SHOW);
	m_R[m_add_id].Router->MoveWindow(CheckRect(CRect(l, t, r, b)));
	UpdateWindow();
	m_R[m_add_id].isEnabled = TRUE;
	m_Log.Format(_T("R%d spawned"), m_add_id);
	OnBnClickedBtnAdd();
}


void Cl5Dlg::OnBnClickedBtnRemove()
{
	m_Log.Format(_T("Click on any router"));
	m_ExHelp.ShowWindow(SW_SHOW);
	Action = 2;
	UpdateData(FALSE);
}

void Cl5Dlg::Remove(int i) {
	m_R[i].Router->MoveWindow(CRect(0, 0, 0, 0));
	m_R[i].Router->ShowWindow(SW_HIDE);
	m_R[i].isEnabled = FALSE;
	m_Log.Format(_T("R%d has been removed"), i);
	for (int j = 0; j < m_Connected.size(); j++) {
		if (m_Connected[j].from == i || m_Connected[j].to == i) {
			m_Connected.erase(m_Connected.begin() + j);
			j--;
		}
	}
	DrawConnections();
}


void Cl5Dlg::OnBnClickedBtnConnect()
{
	m_Log.Format(_T("Click'n'drag from any router"));
	m_ExHelp.ShowWindow(SW_SHOW);
	Action = 3;
	UpdateData(FALSE);
}

void Cl5Dlg::BeginConnect(CPoint point) {
	SetCapture();
	int a = FindClickedR(point);
	if (a >= 0) {
		Connect.from = (GetRect(*m_R[a].Router)).CenterPoint();
		Connect.isDrawing = TRUE;
	}
}

void Cl5Dlg::IsConnecting(CPoint point) {
	DrawConnections();
	point = CheckPoint(point);
	CClientDC dc(this);
	dc.MoveTo(Connect.from);
	dc.LineTo(point);
}

void Cl5Dlg::EndConnect(CPoint point) {
	int a = FindClickedR(point);
	int b = FindClickedR(Connect.from);
	if (a >= 0 && a != b) {
		bool dyplicate = FALSE;
		Connect.to = (GetRect(*m_R[a].Router)).CenterPoint();
		for (int i = 0; i < m_Connected.size(); i++) {
			if ((b == m_Connected[i].from && a == m_Connected[i].to) ||
				(a == m_Connected[i].from && b == m_Connected[i].to)) {
				m_Log.Format(_T("Already connected"));
				dyplicate = TRUE;
				break;
			}
		}
		if (!dyplicate) {
			m_Connected.push_back(connections{ b, a });
			m_Log.Format(_T("Connected R%d with R%d"), b, a);
		}
	}
	DrawConnections();
	Connect.isDrawing = FALSE;
	Connect.from = 0;
	Connect.to = 0;
	ReleaseCapture();
}

void Cl5Dlg::DrawConnections() {
	CRect rect(5, 5, 390, 300);
	InvalidateRect(rect);
	UpdateWindow();
	for (int i = 0; i < m_Connected.size(); i++) {
		CPoint from = (GetRect(*m_R[m_Connected[i].from].Router)).CenterPoint();
		CPoint to = (GetRect(*m_R[m_Connected[i].to].Router)).CenterPoint();
		CClientDC dc(this);
		dc.MoveTo(from);
		dc.LineTo(to);
	}
}


void Cl5Dlg::OnBnClickedBtnHelp()
{
	if (showing_help) {
		InitHelp();
	}
	else {
		m_Log.Format(_T("Showing help"));
		m_Help1.ShowWindow(SW_SHOW);
		m_Help2.ShowWindow(SW_SHOW);
		m_Help3.ShowWindow(SW_SHOW);
		m_Help4.ShowWindow(SW_SHOW);
		m_Help5.ShowWindow(SW_SHOW);
		m_Help7.ShowWindow(SW_SHOW);
		showing_help = TRUE;
	}
	UpdateData(FALSE);
}

void Cl5Dlg::InitHelp() {
	m_Help1.ShowWindow(SW_HIDE);
	m_Help2.ShowWindow(SW_HIDE);
	m_Help3.ShowWindow(SW_HIDE);
	m_Help4.ShowWindow(SW_HIDE);
	m_Help5.ShowWindow(SW_HIDE);
	m_Help7.ShowWindow(SW_HIDE);
	showing_help = FALSE;
	UpdateData(FALSE);
}


void Cl5Dlg::OnBnClickedBtnQuit()
{
	m_Log.Format(_T("Quit button pressed"));
	UpdateData(FALSE);
	EndDialog(IDCANCEL);
}

void Cl5Dlg::OnBnClickedBtnLoad()
{
	int size = sizeof(Cl5Dlg::m_R) / sizeof(*Cl5Dlg::m_R);
	for (int i = 0; i < size; i++) {
		Remove(i);
	}
	m_Connected.clear();
	std::ifstream f("C:\\Users\\plox\\source\\repos\\l5\\l5\\res\\save.txt");
	if (f.is_open()) {
		int enabled;
		f >> enabled;
		for (int i = 0; i < enabled; i++) {
			CPoint p;
			f >> m_add_id >> p.x >> p.y;
			Add(p);
		}
		std::string s;
		f >> s;
		if (s.compare("---") == 0) {
			for (; !f.eof();) {
				int from;
				int to;
				f >> from >> to;
				m_Connected.push_back(connections{ from, to });
			}
		}
	}
	m_Log.Format(_T("Loaded"));
	DrawConnections();
	UpdateData(FALSE);
}

void Cl5Dlg::OnBnClickedBtnSave()
{
	std::ofstream f("C:\\Users\\plox\\source\\repos\\l5\\l5\\res\\save.txt");
	if (f.is_open()) {
		int size = sizeof(Cl5Dlg::m_R) / sizeof(*Cl5Dlg::m_R);
		int enabled = 0;
		for (int i = 0; i < size; i++) {
			if (m_R[i].isEnabled) {
				enabled++;
			}
		}
		f << enabled << std::endl;
		for (int i = 0; i < size; i++) {
			if (m_R[i].isEnabled) {
				CPoint p;
				p = GetRect(*m_R[i].Router).TopLeft();
				f << i << " " << p.x << " " << p.y << " " << std::endl;
			}
		}
		f << "---" << std::endl;
		size = m_Connected.size();
		for (int i = 0; i < size; i++) {
			f << m_Connected[i].from << " " << m_Connected[i].to << std::endl;
		}
	}
	m_Log.Format(_T("Saved"));
}