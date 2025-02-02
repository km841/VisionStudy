#include "pch.h"
#include "CCurve.h"

CCurve::CCurve(const std::vector<CVector2>& ControlPoints, float fThickness)
	: CShape(CVector2(0.0f, 0.0f), EShapeType::Curve)
	, m_fThickness(fThickness)
	, m_eCurveType(ECurveType::Bezier)
{
	m_ControlPoints = ControlPoints;
}

void CCurve::Redefine(const std::vector<CVector2>& ControlPoints, float fThickness, ECurveType eCurveType)
{
	m_ControlPoints = ControlPoints;
	m_fThickness = fThickness;
	m_eCurveType = eCurveType;
}

std::wstring CCurve::GetName() const
{
	return _T("Curve") + std::to_wstring(m_ID);
}

void CCurve::Draw(CImage* InImage)
{
	switch (m_eCurveType)
	{
	case ECurveType::Bezier:
		DrawBezierCurve(InImage);
		break;
	case ECurveType::NSpline:
		break;
	case ECurveType::BSpline:
		break;
	}
}

bool CCurve::Save(const std::wstring& FileName)
{
	return false;
}

bool CCurve::Load(const std::wstring& FileName)
{
	return false;
}

void CCurve::DrawBezierCurve(CImage* InImage)
{
	for (float t = 0.0f; t < 1.0f; t += 0.001f)
	{
		CVector2 V = DeCasteljau(t);

		unsigned char* p = (unsigned char*)InImage->GetBits();
		int nPitch = InImage->GetPitch();

		int nWidth = InImage->GetWidth();
		int nHeight = InImage->GetHeight();

		for (int y = V.y - m_fThickness; y < V.y + m_fThickness; ++y)
		{
			for (int x = V.x - m_fThickness; x < V.x + m_fThickness; ++x)
			{
				if (y < 0 || y >= nHeight || x < 0 || x >= nWidth)
					continue;

				float fDistX = x - V.x;
				float fDistY = y - V.y;
				float fDist = fDistX * fDistX + fDistY * fDistY;

				if (fDist < m_fThickness * m_fThickness)
				{
					p[y * nPitch + x] = 0xDD;
				}
			}
		}

	}
}

CVector2 CCurve::DeCasteljau(float fWeight)
{
	int nCount = static_cast<int>(m_ControlPoints.size());
	std::vector<CVector2> Temp = m_ControlPoints;

	for (int r = 1; r < nCount; ++r) {
		for (int i = 0; i < nCount - r; ++i) {
			Temp[i] = CVector2::Lerp(Temp[i], Temp[i + 1], fWeight);
		}
	}
	return Temp[0];
}
