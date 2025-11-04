#include "pch.h"
#include "Animation.h"
#include "Texture.h"
#include "TimerManager.h"

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

void Animation::Init(DIRECTION _eDirection, int _iStartTextureIndex, int _iEndTextureIndex, ANIMATION_TYPE _eType, float _fSpeed, ANCHOR _eAnchor)
{
	m_vecList.clear();
	m_vecList.resize(_iEndTextureIndex - _iStartTextureIndex);
	for (int j = 0; j < m_vecList.size(); ++j)
	{
		m_vecList[j] = AnimNode{ ResourceManager::GetInstance()->LoadTexture(static_cast<TEXTURE_TYPE>(j + _iStartTextureIndex),_eDirection),nullptr };
	}
	m_eType = _eType;
	m_fSpeed = _fSpeed / static_cast<float>(m_vecList.size());
	m_eAnchor = _eAnchor;
	m_iCurIndex = 0;
	m_fAccTime = 0.0f;
}

void Animation::Init(int _iStartTextureIndex, int _iEndTextureIndex, ANIMATION_TYPE _eType, float _fSpeed, ANCHOR _eAnchor)
{
	m_vecList.clear();
	m_vecList.resize(_iEndTextureIndex - _iStartTextureIndex);
	for (int j = 0; j < m_vecList.size(); ++j)
	{
		m_vecList[j] = AnimNode{ ResourceManager::GetInstance()->LoadTexture(static_cast<TEXTURE_TYPE>(j + _iStartTextureIndex)),nullptr };
	}
	m_eType = _eType;
	m_fSpeed = _fSpeed / static_cast<float>(m_vecList.size());
	m_eAnchor = _eAnchor;
	m_iCurIndex = 0;
	m_fAccTime = 0.0f;
}

void Animation::Init(TEXTURE_TYPE _TextureType, int _iStartTextureIndexI, int _iStartTextureIndexJ, int _AnimationLength, int _Size, ANIMATION_TYPE _eType, float _fSpeed, ANCHOR _eAnchor)
{
	m_vecList.clear();
	m_vecList.resize(_AnimationLength);
	for (int j = 0; j < _AnimationLength; ++j)
	{
		m_vecList[j] = AnimNode{ ResourceManager::GetInstance()->LoadSubTexture(_TextureType, _iStartTextureIndexI, _iStartTextureIndexJ + j, _Size), nullptr };
	}
	m_eType = _eType;
	m_fSpeed = _fSpeed / static_cast<float>(_AnimationLength);
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
	int iWidth = m_vecList[m_iCurIndex].m_pTexture->GetWidth();
	int iHeight = m_vecList[m_iCurIndex].m_pTexture->GetHeight();
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
	TransparentBlt(_memDC, _vec2Position.m_fx - iWidth / 2, _vec2Position.m_fy - iHeight / 2, iWidth * 2, iHeight * 2,
		m_vecList[m_iCurIndex].m_pTexture->GetDC(), 0, 0, iWidth, iHeight, RGB(255, 255, 255));
}

void Animation::SetEvent(int _iTextureIndex, std::function<void()> _pCallBack)
{
	assert(_iTextureIndex < m_vecList.size());
	m_vecList[_iTextureIndex].m_callBack = _pCallBack;
}

