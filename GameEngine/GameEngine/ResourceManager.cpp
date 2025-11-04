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

	case TEXTURE_TYPE::PLAYER_IDLE_1:			return std::format(L"character_idle_{}_00.bmp", GetDirectionString(_eDirection));
	case TEXTURE_TYPE::PLAYER_IDLE_2:			return std::format(L"character_idle_{}_01.bmp", GetDirectionString(_eDirection));
	case TEXTURE_TYPE::PLAYER_IDLE_3:			return std::format(L"character_idle_{}_02.bmp", GetDirectionString(_eDirection));
	case TEXTURE_TYPE::PLAYER_IDLE_4:			return std::format(L"character_idle_{}_03.bmp", GetDirectionString(_eDirection));
	case TEXTURE_TYPE::PLAYER_IDLE_5:			return std::format(L"character_idle_{}_04.bmp", GetDirectionString(_eDirection));
	case TEXTURE_TYPE::PLAYER_IDLE_6:			return std::format(L"character_idle_{}_05.bmp", GetDirectionString(_eDirection));

	case TEXTURE_TYPE::PLAYER_RUN_1:			return std::format(L"character_run_{}_00.bmp", GetDirectionString(_eDirection));
	case TEXTURE_TYPE::PLAYER_RUN_2:			return std::format(L"character_run_{}_01.bmp", GetDirectionString(_eDirection));
	case TEXTURE_TYPE::PLAYER_RUN_3:			return std::format(L"character_run_{}_02.bmp", GetDirectionString(_eDirection));
	case TEXTURE_TYPE::PLAYER_RUN_4:			return std::format(L"character_run_{}_03.bmp", GetDirectionString(_eDirection));
	case TEXTURE_TYPE::PLAYER_RUN_5:			return std::format(L"character_run_{}_04.bmp", GetDirectionString(_eDirection));
	case TEXTURE_TYPE::PLAYER_RUN_6:			return std::format(L"character_run_{}_05.bmp", GetDirectionString(_eDirection));

	case TEXTURE_TYPE::PLAYER_ATTACK_1:			return std::format(L"character_attack_{}_00.bmp", GetDirectionString(_eDirection));
	case TEXTURE_TYPE::PLAYER_ATTACK_2:			return std::format(L"character_attack_{}_01.bmp", GetDirectionString(_eDirection));
	case TEXTURE_TYPE::PLAYER_ATTACK_3:			return std::format(L"character_attack_{}_02.bmp", GetDirectionString(_eDirection));
	case TEXTURE_TYPE::PLAYER_ATTACK_4:			return std::format(L"character_attack_{}_03.bmp", GetDirectionString(_eDirection));

	case TEXTURE_TYPE::MONSTER_IDLE_1:			return std::format(L"monster2_{}_00.bmp", GetDirectionString(_eDirection));
	case TEXTURE_TYPE::MONSTER_IDLE_2:			return std::format(L"monster2_{}_01.bmp", GetDirectionString(_eDirection));
	case TEXTURE_TYPE::MONSTER_IDLE_3:			return std::format(L"monster2_{}_02.bmp", GetDirectionString(_eDirection));

	case TEXTURE_TYPE::EFFECT_01_01:				return L"Effect00.bmp";
	case TEXTURE_TYPE::EFFECT_01_02:				return L"Effect01.bmp";
	case TEXTURE_TYPE::EFFECT_01_03:				return L"Effect02.bmp";
	case TEXTURE_TYPE::EFFECT_01_04:				return L"Effect03.bmp";
	case TEXTURE_TYPE::EFFECT_01_05:				return L"Effect04.bmp";
	case TEXTURE_TYPE::EFFECT_01_06:				return L"Effect05.bmp";

	case TEXTURE_TYPE::EFFECT:						return L"Effect.bmp";
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

Texture* ResourceManager::LoadSubTexture(TEXTURE_TYPE _eTextureType, int _iStartTextureIndexI, int _iStartTextureIndexJ, int _Size)
{
	std::wstring strFileName = GetTextureFileName(_eTextureType);
	std::wstring strKey = strFileName.substr(0, strFileName.length() - 4);
	strKey += std::to_wstring(_iStartTextureIndexI) + L"_" + std::to_wstring(_iStartTextureIndexJ);

	Texture* pTexture = FindTexture(strKey);
	if (pTexture == nullptr)
	{
		pTexture = new Texture;
		std::wstring strPath = PathManager::GetInstance()->GetContentpath();
		strPath += ConstValue::strTexturePath + strFileName;
		pTexture->LoadPartially(strPath, _iStartTextureIndexI, _iStartTextureIndexJ, _Size);
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