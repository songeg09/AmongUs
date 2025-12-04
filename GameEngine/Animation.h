#pragma once
#include "ResourceManager.h"
class TextureAtlas;

struct AnimNode
{
	std::weak_ptr<TextureAtlas> m_pTextureAtlas;
	std::function<void()>		m_callBack;
};

enum class ANIMATION_TYPE
{
	LOOP,
	ONCE,
	END,
};

enum class ANCHOR
{
	CENTER,
	CENTER_BOTTOM,
	CENTER_TOP,
};

class Animation
{
private:
	std::vector<AnimNode>	m_vecList;
	ANIMATION_TYPE			m_eType;
	ANCHOR					m_eAnchor;
	float					m_fSpeed;
	float					m_fAccTime;
	int						m_iCurIndex;
public:
	Animation();
	~Animation();
	void Reset();
	void Init(TEXTURE_TYPE _TextureType, Vector2 _vec2Position, Vector2 _vec2Size, int _iMargin, int _iLength, bool _bFlip, ANIMATION_TYPE _eType, float _fSpeed, ANCHOR _eAnchor);
	void Update();
	void Render(HDC _memDC, Vector2 _vec2Position);
	void SetEvent(int _iTextureIndex, std::function<void()> _pCallBack);
	bool GetLive()
	{
		if (m_eType == ANIMATION_TYPE::LOOP)
			return true;
		else if (m_eType == ANIMATION_TYPE::ONCE && m_iCurIndex < m_vecList.size() - 1)
			return true;
		return false;
	}
};

