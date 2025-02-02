#pragma once
#include "CShape.h"
#include "Common.h"

class CCurve :
    public CShape
{
public:
    CCurve(const std::vector<CVector2>& ControlPoints, float fThickness);

    void Redefine(const std::vector<CVector2>& ControlPoints, float fThickness, ECurveType eCurveType);
    void SetCurveType(ECurveType eCurveType) { m_eCurveType = eCurveType; }
    ECurveType GetCurveType() const { return m_eCurveType; }

public:
    virtual std::wstring GetName() const;
    virtual void Draw(CImage* InImage);
    virtual bool Save(const std::wstring& FileName);
    virtual bool Load(const std::wstring& FileName);

protected:
    void DrawBezierCurve(CImage* InImage);
    CVector2 DeCasteljau(float fWeight);

private:
    float m_fThickness;
    ECurveType m_eCurveType;
    std::vector<CVector2> m_ControlPoints;
};

