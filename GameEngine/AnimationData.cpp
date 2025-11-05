#include "pch.h"
#include "Animation.h"
#include "AnimationData.h"

AnimationData::AnimationData(
	TEXTURE_TYPE	_eTextrueType,
	Vector2			_vec2Position,
	Vector2			_vec2Size,
	int				_iMargin,
	int				_iLength,
	ANIMATION_TYPE  _eAnimationType,
	float			_fDuration,
	ANCHOR          _eAnchor
)
{
	m_eTextrueType = _eTextrueType;
	m_vec2Position = _vec2Position;
	m_vec2Size = _vec2Size;
	m_iMargin = _iMargin;
	m_iLength = _iLength;
	m_eAnimationType = _eAnimationType;
	m_fDuration = _fDuration;
	m_eAnchor = _eAnchor;
}

void AnimationData::Load(std::wifstream& _loadFile)
{
}
