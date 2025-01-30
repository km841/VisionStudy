#pragma once
#include <string>
#include <sstream>

struct CVector2
{
	float x = 0.0f;
	float y = 0.0f;

	CVector2(float x, float y)
		: x(x), y(y)
	{}

	CVector2()
		: x(0.0f), y(0.0f)
	{}

	std::wstring ToString()
	{
		std::wstringstream Stream;
		Stream << x << TEXT(", ") <<  y;
		return Stream.str();
	}

	bool operator<(const CVector2& other) const
	{
		if (x < other.x && y < other.y)
			return true;
		else
			return false;
		
	}

	bool operator==(const CVector2& other)
	{
		return (other.x == x) && (other.y == y);
	}

	bool operator!=(const CVector2& other)
	{
		return !(*this == other);
	}

	CVector2 operator/(float value)
	{
		return CVector2(x / value, y / value);
	}

	CVector2& operator+=(const CVector2& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}

	CVector2& operator/=(float value)
	{
		x /= value;
		y /= value;
		return *this;
	}

	CVector2 operator-(const CVector2& other)
	{
		return CVector2(x - other.x, y - other.y);
	}

	CVector2 operator-(const CVector2& other) const
	{
		return CVector2(x - other.x, y - other.y);
	}

	double Length() const
	{
		return sqrt((static_cast<double>(x * x + y * y)));
	}

	static CVector2 CPointToVector2(const CPoint& cp)
	{
		return CVector2((float)cp.x, (float)cp.y);
	}

	static CVector2 Lerp(const CVector2& V1, const CVector2& V2, float t)
	{
		CVector2 Ret;
		Ret.x = (1 - t) * V1.x + t * V2.x;
		Ret.y = (1 - t) * V1.y + t * V2.y;
		return Ret;
	}
};