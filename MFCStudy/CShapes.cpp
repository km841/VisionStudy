#include "pch.h"
#include "CShapes.h"

CShapes::CShapes(CImage* InImage)
	: m_Image(InImage)
	, m_pClickedShape(nullptr)
	, m_pCurve(nullptr)
{
}

CShapes::~CShapes()
{
	for (int i = 0; i < m_vecShapes.size(); ++i)
	{
		if (m_vecShapes[i] != nullptr)
		{
			delete m_vecShapes[i];
			m_vecShapes[i] = nullptr;
		}
	}

	m_vecShapes.clear();
}

void CShapes::Draw()
{
	if (m_pCurve)
		m_pCurve->Draw(m_Image);

	for (int i = 0; i < m_vecShapes.size(); ++i)
	{
		if (m_vecShapes[i] != m_pCurve)
			m_vecShapes[i]->Draw(m_Image);
	}
}

void CShapes::RegisterShape(CShape* pShape)
{
	m_vecShapes.push_back(pShape);
}

bool CShapes::CheckOverlap(CVector2 MousePos)
{
	bool bIsOverlapped = false;
	for (int i = 0; i < m_vecShapes.size(); ++i)
	{
		if (m_vecShapes[i]->IsOverlapped(MousePos))
		{
			bIsOverlapped = true;
			m_pClickedShape = m_vecShapes[i];
			break;
		}
	}
	return bIsOverlapped;
}

bool CShapes::IsExistsCurve()
{
	//for (int i = 0; i < m_vecShapes.size(); ++i)
	//{
	//	if (m_vecShapes[i]->GetName() == _T("Curve"))
	//		return true;
	//}

	return m_pCurve != nullptr;
}

void CShapes::RemoveCurve()
{
	std::vector<CShape*>::iterator Iter = m_vecShapes.begin();
	for (; Iter != m_vecShapes.end(); ++Iter)
	{
		if ((*Iter) == m_pCurve)
		{
			delete *Iter;
			Iter = m_vecShapes.erase(Iter);
			break;
		}
	}

	m_pCurve = nullptr;
}

CCircle* CShapes::CreateCircle(CVector2 CenterPos, float fRadius)
{
	CCircle* pCircle = new CCircle(CenterPos, fRadius);
	return pCircle;
}

CCurve* CShapes::CreateCurve(const std::vector<CVector2>& ControlPoints, float fThickness)
{
	if (IsExistsCurve())
	{
		AssertEx(false, _T("CShapes::CreateCurve(const std::vector<CVector2>& ControlPoints, float fThickness) -> 이미 Curve가 존재합니다!"));
		return nullptr;
	}

	CCurve* pCurve = new CCurve(ControlPoints, fThickness);
	return pCurve;
}
