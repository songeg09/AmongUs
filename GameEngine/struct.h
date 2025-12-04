#pragma once
struct Rect
{
	float left;
	float top;
	float right;
	float bottom;
};

struct Vector2
{

	float m_fx;
	float m_fy;

	Vector2()
	{
		m_fx = 0.0f;
		m_fy = 0.0f;
	}
	Vector2(float _fx, float _fy)
	{
		m_fx = _fx;
		m_fy = _fy;
	}

	void operator += (Vector2 _vec2)
	{
		m_fx += _vec2.m_fx;
		m_fy += _vec2.m_fy;
	}
	void operator -= (Vector2 _vec2)
	{
		m_fx -= _vec2.m_fx;
		m_fy -= _vec2.m_fy;
	}
	Vector2 operator - (Vector2 _vec2)
	{
		Vector2 value;
		value.m_fx = m_fx - _vec2.m_fx;
		value.m_fy = m_fy - _vec2.m_fy;
		return value;
	}
	Vector2 operator + (Vector2 _vec2)
	{
		Vector2 value;
		value.m_fx = m_fx + _vec2.m_fx;
		value.m_fy = m_fy + _vec2.m_fy;
		return value;
	}
	Vector2 operator * (Vector2 _vec2)
	{
		Vector2 value;
		value.m_fx = m_fx * _vec2.m_fx;
		value.m_fy = m_fy * _vec2.m_fy;
		return value;
	}
	Vector2 operator * (float _fValue)
	{
		Vector2 value;
		value.m_fx = m_fx * _fValue;
		value.m_fy = m_fy * _fValue;
		return value;
	}
	bool operator<= (const Vector2 _other) const
	{
		if (m_fx != _other.m_fx)
			return m_fx <= _other.m_fx;
		return m_fy <= _other.m_fy;
	}

	bool operator> (const Vector2 _other) const
	{
		if (m_fx != _other.m_fx)
			return m_fx > _other.m_fx;
		return m_fy > _other.m_fy;
	}

	void operator *= (float _fValue)
	{
		m_fx *= _fValue;
		m_fy *= _fValue;
	}
	float Length()
	{
		return sqrt(pow(m_fx, 2) + pow(m_fy, 2));
	}
	static float Distance(Vector2 _first, Vector2 _second)
	{
		Vector2 NewVector = _second - _first;
		return NewVector.Length();
	}
	static float Dot(Vector2 _first, Vector2 _second)
	{
		return _first.m_fx * _second.m_fx + _first.m_fy * _second.m_fy;
	}
	void Normalize()
	{
		float length = Length();
		if (length == 0.0f)
		{
			m_fx = 0.0f;
			m_fy = 0.0f;
		}
		else
		{
			m_fx /= length;
			m_fy /= length;
		}
	}
	bool isValid()
	{
		return m_fx != 0.0f || m_fy != 0.0f;
	}
	void ZeroSet()
	{
		if (abs(m_fx) <= FLT_MIN)
			m_fx = 0.0f;
		if (abs(m_fy) <= FLT_MIN)
			m_fy = 0.0f;
	}
};

using Flags = unsigned int;

constexpr Flags Flag(int kind) { return 1u << static_cast<unsigned>(kind); }