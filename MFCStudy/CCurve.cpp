#include "pch.h"
#include "CCurve.h"

CCurve::CCurve(const std::vector<CVector2>& ControlPoints, float fThickness)
	: CShape(ControlPoints[0])
	, m_fThickness(fThickness)
{
	m_ControlPoints = ControlPoints;
}

std::wstring CCurve::GetName() const
{
	return TEXT("Curve");
}

void CCurve::Draw(CImage* InImage)
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
					p[y * nPitch + x] = 0x80;
				}
			}
		}

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

CVector2 CCurve::DeCasteljau(float fWeight)
{
	int nCount = m_ControlPoints.size();
	std::vector<CVector2> Temp = m_ControlPoints;

	for (int r = 1; r < nCount; ++r) {
		for (int i = 0; i < nCount - r; ++i) {
			Temp[i] = CVector2::Lerp(Temp[i], Temp[i + 1], fWeight);
		}
	}
	return Temp[0];
}
