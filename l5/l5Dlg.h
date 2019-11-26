#pragma once
#include <iostream>
#include <vector>
#include <fstream>

struct r {
	CStatic* Router;
	bool isEnabled;
	CPoint tl;
};

struct drag {
	bool isDragged;
	int xOffset;
	int yOffset;
	CStatic* Router;
};

struct connect{
	bool isDrawing;
	CPoint from;
	CPoint to;
};

struct connections {
	int from;
	int to;
};

// Cl5Dlg dialog
class Cl5Dlg : public CDialogEx
{
// Construction
public:
	Cl5Dlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_l5_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

// Implementation
protected:
	HICON m_hIcon;
	LPCSTR bitmap_addr;
	HBITMAP  hBitMap;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
private:
	CString m_MPosX_Echo;
	CString m_MPosY_Echo;
	CString m_Log;
	int Action; //0=Drag,1=Add,2=Remove,3=Connect
public:
	r m_R[100];
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
private:
	drag Drag;
	void BeginDrag(CPoint point);
	void IsDragged(CPoint point);
	void EndDrag(CPoint point);
public:
	afx_msg void OnBnClickedBtnAdd();
private:
	int m_add_id;
	void Add(CPoint point);
public:
	afx_msg void OnBnClickedBtnRemove();
private:
	void Remove(int i);
public:
	afx_msg void OnBnClickedBtnConnect();
	std::vector<connections> m_Connected;
private:
	struct connect Connect;
	void BeginConnect(CPoint point);
	void IsConnecting(CPoint point);
	void EndConnect(CPoint point);
	void DrawConnections();
public:
	afx_msg void OnBnClickedBtnHelp();
private:
	CStatic m_Help1;
	CStatic m_Help2;
	CStatic m_Help3;
	CStatic m_Help4;
	CStatic m_Help5;
	CStatic m_Help7;
	void InitHelp();
	bool showing_help;
public:
	afx_msg void OnBnClickedBtnQuit();
	CRect GetRect(CStatic &wnd);
	void InitRouters();
	CRect CheckRect(CRect rect);
	CPoint CheckPoint(CPoint point);
	int FindClickedR(CPoint point);
	afx_msg void OnMoving(UINT fwSide, LPRECT pRect);
private:
	CStatic m_ExHelp;
public:
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedBtnLoad();
	afx_msg void OnBnClickedBtnSave();
};
