#pragma once
#include <afxpropertygridctrl.h>
#include "Common.h"

class CShape;
class CMFCStudyDlg;
class CHmGridProperty :
    public CMFCPropertyGridProperty
{
public:
	// Group constructor
	CHmGridProperty(const CString& strGroupName, DWORD_PTR dwData = 0, BOOL bIsValueList = FALSE);

	// Simple property
	CHmGridProperty(const CString& strName, const COleVariant& varValue, LPCTSTR lpszDescr = NULL, DWORD_PTR dwData = 0,
		LPCTSTR lpszEditMask = NULL, LPCTSTR lpszEditTemplate = NULL, LPCTSTR lpszValidChars = NULL);

	CHmGridProperty(const CString& strName, const COleVariant& varValue, CMFCStudyDlg* pDialog);

public:
	virtual void OnClickName(CPoint point) override;

private:
	CShape* m_pPrevShape;
	CMFCStudyDlg* m_pDialog;
	EGridPropertyType m_eGridPropertyType;
};

