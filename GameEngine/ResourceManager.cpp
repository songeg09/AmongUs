#include "pch.h"
#include "ResourceManager.h"
#include "PathManager.h"
#include "Texture.h"
#include "CircleSkillData.h"
#include "RectSkillData.h"
#include "CircleZoneData.h"
#include "RectZoneData.h"

ResourceManager::ResourceManager()
{

}
ResourceManager::~ResourceManager()
{
	for (auto iter = m_MapTexture.begin(); iter != m_MapTexture.end(); iter++)
		delete iter->second;
}

std::wstring ResourceManager::GetTextureFileName(TEXTURE_TYPE _eTextureType, DIRECTION _eDirection)
{
	switch (_eTextureType)
	{
	case TEXTURE_TYPE::BACKGROUND:			return L"background.bmp";
	default: return L"";
	}
}

std::wstring ResourceManager::GetDirectionString(DIRECTION _eDirection)
{
	switch (_eDirection)
	{
	case DIRECTION::LEFT:
		return L"left";
	case DIRECTION::RIGHT:
		return L"right";
	case DIRECTION::UP:
		return L"up";
	case DIRECTION::DOWN:
		return L"down";
	default:
		break;
	}
	return std::wstring();
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

Texture* ResourceManager::LoadTexture(TEXTURE_TYPE _eTextureType, DIRECTION _eDirection)
{
	std::wstring strFileName = GetTextureFileName(_eTextureType, _eDirection);
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
	return pTexture;
}

Texture* ResourceManager::FindTexture(const std::wstring& _strKey)
{
	std::map<std::wstring, Texture*>::iterator iter = m_MapTexture.find(_strKey);
	if (iter == m_MapTexture.end())
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