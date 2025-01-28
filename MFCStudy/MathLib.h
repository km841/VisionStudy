#pragma once


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

	float Length() const
	{
		return sqrt((static_cast<double>(x * x + y * y)));
	}

	static CVector2 CPointToVector2(const CPoint& cp)
	{
		return CVector2((float)cp.x, (float)cp.y);
	}
};