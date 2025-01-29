#pragma once
#include "CShape.h"
#include "Common.h"

class CCurve :
    public CShape
{
public:
    CCurve(const std::vector<CVector2>& ControlPoints, float fThickness);

public:
    virtual std::wstring GetName() const;
    virtual void Draw(CImage* InImage);
    virtual bool Save(const std::wstring& FileName);
    virtual bool Load(const std::wstring& FileName);

private:
    CVector2 m_StartPoint;
    CVector2 m_EndPoint;
    std::vector<CVector2> m_ControlPoints;
};

