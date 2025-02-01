﻿#pragma once
#include "Common.h"
class CShapes;
class CCurve;
class CCircle;

#define THICKNESS 6.0f

enum class EClickMode
{
	Create,
	Move,
};

class CMFCStudyDlg : public CDialogEx
{
// 생성입니다.

public:
	CMFCStudyDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	virtual ~CMFCStudyDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCSTUDY_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

protected:
	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

	void Initialize();
	void InitImage();
	void InitDC();
	void InitGridCtrl();

	void DrawShapesInBackBuffer();
	void DrawBackBuffer();
	void DrawMainBuffer();
	void DrawScreen();
	void Refresh();

	bool IsOverTheLimit(CPoint Point);

	void ClearImage();
	void RenewGridCtrl();

	CCurve* CreateCurve(const CVector2& Pos, float fThickness);
	CCurve* RedefineCurve(float fThickness);
	CCircle* CreateCircle(const CVector2& Pos, float fRadius);

	template<typename T>
	T* GetControl(int nID);

	DECLARE_MESSAGE_MAP()
public:
	HICON m_hIcon;
	CImage m_Image;

	// Double Buffering
	CDC* m_MainDC;
	CDC m_BackBufDC;
	CBitmap  m_BackBufBit;

	// Helper Classes
	CVector2 m_MousePos;
	CShapes* m_pShapes;

	// bool & Enum
	bool m_bInitialized;
	EClickMode m_eMode;
};

template<typename T>
inline T* CMFCStudyDlg::GetControl(int nID)
{
	T* pControl = (T*)GetDlgItem(nID);
	return pControl;
}
