#pragma once
#include "Data.h"
class AnimationData : public Data
{
private:
	TEXTURE_TYPE    m_eTextrueType;
	Vector2			m_vec2Position;
	Vector2			m_vec2Size;
	int				m_iMargin;
	int				m_iLength;
	ANIMATION_TYPE  m_eAnimationType;
	float			m_fDuration;
	ANCHOR          m_eAnchor;

public:
	AnimationData(
		TEXTURE_TYPE	_eTextrueType,
		Vector2			_vec2Position,
		Vector2			_vec2Size,
		int				_iMargin,
		int				_iLength,
		ANIMATION_TYPE  _eAnimationType,
		float			_fDuration,
		ANCHOR          _eAnchor
	);

	void Load(std::wifstream& _loadFile) override;

	TEXTURE_TYPE GetTextureType() { return m_eTextrueType; }
	Vector2 GetPosition() { return m_vec2Position; }
	Vector2 GetSize() { return m_vec2Size; }
	int GetMargin() { return m_iMargin; }
	int GetLength() { return m_iLength; }
	ANIMATION_TYPE GetAnimationType(){ return m_eAnimationType; }
	float GetDuration() { return m_fDuration; }
	ANCHOR GetAnchor() { return m_eAnchor; }
};

