#include "pch.h"
#include "CShapes.h"

CShapes::CShapes(CImage* InImage)
	: m_Image(InImage)
	, m_pClickedShape(nullptr)
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
	for (int i = 0; i < m_vecShapes.size(); ++i)
	{
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

CCircle* CShapes::CreateCircle(CVector2 CenterPos, float fRadius)
{
	CCircle* pCircle = new CCircle(CenterPos, fRadius);
	return pCircle;
}

CCurve* CShapes::CreateCurve(const std::vector<CVector2>& ControlPoints, float fThickness)
{
	CCurve* pCurve = new CCurve(ControlPoints, fThickness);
	return pCurve;
}
