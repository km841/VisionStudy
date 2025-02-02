#include "pch.h"
#include "CHmGridProperty.h"
#include "CShapes.h"
#include "MFCStudyDlg.h"

CHmGridProperty::CHmGridProperty(const CString& strGroupName, DWORD_PTR dwData, BOOL bIsValueList)
	: CMFCPropertyGridProperty(strGroupName, dwData, bIsValueList)
	, m_pDialog(nullptr)
	, m_pPrevShape(nullptr)
	, m_eGridPropertyType(EGridPropertyType::Group)
{
}

CHmGridProperty::CHmGridProperty(const CString& strName, const COleVariant& varValue, LPCTSTR lpszDescr, DWORD_PTR dwData, LPCTSTR lpszEditMask, LPCTSTR lpszEditTemplate, LPCTSTR lpszValidChars)
	: CMFCPropertyGridProperty(strName, varValue, lpszDescr, dwData, lpszEditMask, lpszEditTemplate, lpszValidChars)
	, m_pDialog(nullptr)
	, m_pPrevShape(nullptr)
	, m_eGridPropertyType(EGridPropertyType::Single)
{
}

CHmGridProperty::CHmGridProperty(const CString& strName, const COleVariant& varValue, CMFCStudyDlg* pDialog)
	: CMFCPropertyGridProperty(strName, varValue, NULL, 0, NULL, NULL, NULL)
	, m_pDialog(pDialog)
	, m_pPrevShape(nullptr)
	, m_eGridPropertyType(EGridPropertyType::Single)
{
}

void CHmGridProperty::OnClickName(CPoint point)
{
	if (m_eGridPropertyType == EGridPropertyType::Group)
		return;

	static CShape* pPrevShape = nullptr;
	CShapes* pShapes = m_pDialog->GetShapes();

	CString PropName = GetName();
	std::wstring Name(PropName);

	CShape* pShape = pShapes->FindShape(Name);
	if (pShape)
	{
		if (pShape == pPrevShape)
		{
			pShapes->SetGridCtrlClickShape(nullptr);
			pPrevShape = nullptr;
			goto Skip;
		}
		
		if (pShape->GetShapeType() == EShapeType::Circle)
			pShapes->SetGridCtrlClickShape(static_cast<CCircle*>(pShape));

		pPrevShape = pShape;

Skip:
		m_pDialog->Refresh();
	}

	CMFCPropertyGridProperty::OnClickName(point);
}
