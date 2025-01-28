#pragma once
#include "MathLib.h"

class CMFCStudyDlg : public CDialogEx
{
// 생성입니다.
public:
	CMFCStudyDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

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

	void Initialize();
	void InitImage();
	void InitDC();
	void InitGridCtrl();

	void DrawBackBuffer();
	void DrawMainBuffer();

	
	template<typename T>
	T* GetControl(int nID);

	DECLARE_MESSAGE_MAP()
public:
	HICON m_hIcon;
	CImage m_Image;
	CDC* m_MainDC;
	CDC m_BackBufDC;
	CBitmap  m_BackBufBit;
	CVector2 m_MousePos;

	bool m_bInitialized;
};

template<typename T>
inline T* CMFCStudyDlg::GetControl(int nID)
{
	T* pControl = (T*)GetDlgItem(nID);
	return pControl;
}
