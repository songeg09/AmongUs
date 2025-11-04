#pragma once

enum DIRECTION
{
	START,
	LEFT = START,
	RIGHT,
	UP,
	DOWN,
	END
};

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
	void operator *= (float _fValue)
	{
		m_fx *= _fValue;
		m_fy *= _fValue;
	}
	float Length()
	{
		return sqrt(pow(m_fx, 2) + pow(m_fy, 2));
	}
	void Normalize()
	{
		float length = Length();
		assert(length != 0.0f);
		m_fx /= length;
		m_fy /= length;
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
