#pragma once
#include "CShape.h"
#include "Common.h"

class CCurve :
    public CShape
{
public:
    CCurve(const std::vector<CVector2>& ControlPoints, float fThickness);

    void Redefine(const std::vector<CVector2>& ControlPoints, float fThickness);
public:
    virtual std::wstring GetName() const;
    virtual void Draw(CImage* InImage);
    virtual bool Save(const std::wstring& FileName);
    virtual bool Load(const std::wstring& FileName);

protected:
    CVector2 DeCasteljau(float fWeight);

private:
    float m_fThickness;
    std::vector<CVector2> m_ControlPoints;
};

