#include "pch.h"
#include "CCurve.h"

CCurve::CCurve(const std::vector<CVector2>& ControlPoints, float fThickness)
	: CShape(ControlPoints[0])
{
	m_ControlPoints = ControlPoints;
	m_StartPoint = ControlPoints[0];
	m_EndPoint = ControlPoints.back();
}

std::wstring CCurve::GetName() const
{
	return TEXT("Curve");
}

void CCurve::Draw(CImage* InImage)
{
}

bool CCurve::Save(const std::wstring& FileName)
{
	return false;
}

bool CCurve::Load(const std::wstring& FileName)
{
	return false;
}
