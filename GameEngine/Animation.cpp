#include "pch.h"
#include "Animation.h"
#include "Texture.h"
#include "TextureAtlas.h"
#include "TimerManager.h"
#include "SceneManager.h"

Animation::Animation()
{
	m_vecList = {};
	m_eType = ANIMATION_TYPE::END;
	m_iCurIndex = 0;
	m_fAccTime = 0.0f;
	m_fSpeed = 0.0f;
}

Animation::~Animation()
{
}

void Animation::Reset()
{
	m_iCurIndex = 0;
	m_fAccTime = 0.0f;
}

void Animation::Init(TEXTURE_TYPE _TextureType, Vector2 _vec2Position, Vector2 _vec2Size, int _iMargin, int _iLength, bool _bFlip, ANIMATION_TYPE _eType, float _fSpeed, ANCHOR _eAnchor)
{
	m_vecList.clear();
	m_vecList.resize(_iLength);
	for (int j = 0; j < _iLength; ++j)
	{
		Vector2 Position = _vec2Position;
		Position.m_fx += j;
		m_vecList[j] = AnimNode{ ResourceManager::GetInstance()->LoadTextureAtlas(_TextureType, Position, _vec2Size, _iMargin, _bFlip), nullptr };
	}
	m_eType = _eType;
	m_fSpeed = _fSpeed / static_cast<float>(_iLength);
	m_eAnchor = _eAnchor;
	m_iCurIndex = 0;
	m_fAccTime = 0.0f;
}


void Animation::Update()
{
	if (m_eType == ANIMATION_TYPE::ONCE && m_iCurIndex >= m_vecList.size() - 1)
		return;
	m_fAccTime += TimerManager::GetInstance()->GetfDeltaTime();
	if (m_fAccTime >= m_fSpeed)
	{
		++m_iCurIndex;
		if (m_eType == ANIMATION_TYPE::LOOP && m_iCurIndex >= m_vecList.size())
			m_iCurIndex = 0;
		m_fAccTime = 0;
		if (m_vecList[m_iCurIndex].m_callBack != nullptr)
			m_vecList[m_iCurIndex].m_callBack();
	}
}

void Animation::Render(HDC _memDC, Vector2 _vec2Position)
{
	int iWidth = m_vecList[m_iCurIndex].m_pTextureAtlas.lock()->GetWidth();
	int iHeight = m_vecList[m_iCurIndex].m_pTextureAtlas.lock()->GetHeight();
	switch (m_eAnchor)
	{
	case ANCHOR::CENTER:
		_vec2Position.m_fx -= iWidth / 2;
		_vec2Position.m_fy -= iHeight / 2;
		break;
	case ANCHOR::CENTER_BOTTOM:
		_vec2Position.m_fx -= iWidth / 2;
		_vec2Position.m_fy -= iHeight;
		break;
	case ANCHOR::CENTER_TOP:
		_vec2Position.m_fx -= iWidth / 2;
		break;
	}
	if (m_vecList.size() == 0)
		return;

	Vector2 BackBuffertTopLeftInScene = SceneManager::GetInstance()->GetCurScene()->GetBackBufferTopLeftInScene();

	_vec2Position.m_fx -= BackBuffertTopLeftInScene.m_fx;
	_vec2Position.m_fy -= BackBuffertTopLeftInScene.m_fy;

	TransparentBlt(_memDC, _vec2Position.m_fx, _vec2Position.m_fy, iWidth, iHeight,
		m_vecList[m_iCurIndex].m_pTextureAtlas.lock()->GetDC(),
		m_vecList[m_iCurIndex].m_pTextureAtlas.lock()->GetAtlasPosition().m_fx,
		m_vecList[m_iCurIndex].m_pTextureAtlas.lock()->GetAtlasPosition().m_fy,
		iWidth, iHeight, RGB(255, 0, 255));
}

void Animation::SetEvent(int _iTextureIndex, std::function<void()> _pCallBack)
{
	assert(_iTextureIndex < m_vecList.size());
	m_vecList[_iTextureIndex].m_callBack = _pCallBack;
}

