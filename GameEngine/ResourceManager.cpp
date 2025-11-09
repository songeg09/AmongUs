#include "pch.h"
#include "ResourceManager.h"
#include "PathManager.h"
#include "Texture.h"
#include "CircleSkillData.h"
#include "RectSkillData.h"
#include "CircleZoneData.h"
#include "RectZoneData.h"
#include "TextureAtlas.h"

ResourceManager::ResourceManager()
{

}
ResourceManager::~ResourceManager()
{
	for (auto iter = m_MapTexture.begin(); iter != m_MapTexture.end(); iter++)
		delete iter->second;

	for (auto iter = m_MapTextureAtlas.begin(); iter != m_MapTextureAtlas.end(); iter++)
		delete iter->second;
}

std::wstring ResourceManager::GetTextureFileName(TEXTURE_TYPE _eTextureType)
{
	switch (_eTextureType)
	{
	case TEXTURE_TYPE::BACKGROUND:			return L"background.bmp";
	case TEXTURE_TYPE::DEVMAP:			return L"devmap.bmp";
	case TEXTURE_TYPE::CHARACTER:			return L"character.bmp";
	default: return L"";
	}
}

void ResourceManager::Init()
{
	std::wifstream FileNameLoad;
	std::wstring FileName = PathManager::GetInstance()->GetContentpath() + ConstValue::strDataPath + ConstValue::strDataTableNamesFileName;
	FileNameLoad.open(FileName);
	if (FileNameLoad.is_open())
	{
		while (FileNameLoad.eof() == false)
		{
			std::wstring FileName;
			FileNameLoad >> FileName;
			if (FileName == L"CircleSkill.txt")
				LoadData<CircleSkillData>(FileName);
			else if (FileName == L"RectSkill.txt")
				LoadData<RectSkillData>(FileName);
			else if(FileName == L"CircleZone.txt")
				LoadData<CircleZoneData>(FileName);
			else if (FileName == L"RectZone.txt")
				LoadData<RectZoneData>(FileName);
		}
	}
}

Texture* ResourceManager::LoadTexture(TEXTURE_TYPE _eTextureType, bool _bFlipOption)
{
	std::wstring strFileName = GetTextureFileName(_eTextureType);
	assert(strFileName.length() != 0);

	std::wstring strKey = strFileName.substr(0, strFileName.length() - 4);

	Texture* pTexture = FindTexture(strKey);
	if (pTexture == nullptr)
	{
		pTexture = new Texture;
		std::wstring strPath = PathManager::GetInstance()->GetContentpath();
		strPath += ConstValue::strTexturePath + strFileName;
		pTexture->Load(strPath);
		pTexture->SetKey(strKey);
		pTexture->SetRelativePath(strFileName);
		m_MapTexture.insert(std::make_pair(strKey, pTexture));
	}

	if(_bFlipOption == false)
		return pTexture;

	strKey = strKey + L"_flipped";
	Texture* pTextureFlipped = FindTexture(strKey);
	if (pTextureFlipped == nullptr)
	{
		pTextureFlipped = new Texture;
		pTextureFlipped->LoadFlipped(pTexture);
		pTexture->SetKey(strKey);
		pTexture->SetRelativePath(strFileName);
		m_MapTexture.insert(std::make_pair(strKey, pTextureFlipped));
	}

	return pTextureFlipped;
}

Texture* ResourceManager::FindTexture(const std::wstring& _strKey)
{
	std::map<std::wstring, Texture*>::iterator iter = m_MapTexture.find(_strKey);
	if (iter == m_MapTexture.end())
		return nullptr;
	else
		return iter->second;
}

TextureAtlas* ResourceManager::LoadTextureAtlas(TEXTURE_TYPE _eTextureType, Vector2 _vec2Position, Vector2 _vec2Size, int _margin, bool _Flip)
{
	std::wstring strFileName = GetTextureFileName(_eTextureType);

	std::wstring strKey = strFileName.substr(0, strFileName.length() - 4);
	strKey = strKey + std::to_wstring(_vec2Position.m_fx) + L"_" + std::to_wstring(_vec2Position.m_fy) + L"_"
		+ std::to_wstring(_vec2Size.m_fx) + L"_" + std::to_wstring(_vec2Size.m_fy) + L"_"
		+ std::to_wstring(_margin) + L"_" + std::to_wstring(_Flip);

	TextureAtlas* pTextureAtlas = FindTextureAtlas(strKey);
	if (pTextureAtlas == nullptr)
	{
		pTextureAtlas = new TextureAtlas;
		std::wstring strPath = PathManager::GetInstance()->GetContentpath();
		strPath += ConstValue::strTexturePath + strFileName;
		pTextureAtlas->Load(_eTextureType, _vec2Position, _vec2Size, _margin, _Flip);
		pTextureAtlas->SetKey(strKey);
		pTextureAtlas->SetRelativePath(strFileName);
		m_MapTextureAtlas.insert(std::make_pair(strKey, pTextureAtlas));
	}
	return pTextureAtlas;


	return nullptr;
}

TextureAtlas* ResourceManager::FindTextureAtlas(const std::wstring& _strKey)
{
	std::map<std::wstring, TextureAtlas*>::iterator iter = m_MapTextureAtlas.find(_strKey);
	if (iter == m_MapTextureAtlas.end())
		return nullptr;
	else
		return iter->second;
}

Data* ResourceManager::GetData(std::wstring _strkey, int _iIndex)
{
	if (_iIndex >= m_MapData[_strkey].size())
		return nullptr;
	return m_MapData[_strkey][_iIndex];
}