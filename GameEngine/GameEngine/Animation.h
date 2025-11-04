#pragma once
#include "ResourceManager.h"
class Texture;

struct AnimNode
{
	Texture* m_pTexture;
	std::function<void()> m_callBack;
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
	void Init(DIRECTION _eDirection, int _iStartTextureIndex, int _iEndTextureIndex, ANIMATION_TYPE _eType, float _fSpeed, ANCHOR _eAnchor);
	void Init(int _iStartTextureIndex, int _iEndTextureIndex, ANIMATION_TYPE _eType, float _fSpeed, ANCHOR _eAnchor);
	void Init(TEXTURE_TYPE _TextureType, int _iStartTextureIndexI, int _iStartTextureIndexJ, int _AnimationLength, int _Size, ANIMATION_TYPE _eType, float _fSpeed, ANCHOR _eAnchor);
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

