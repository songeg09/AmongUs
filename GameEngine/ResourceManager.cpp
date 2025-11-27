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
	case TEXTURE_TYPE::BACKGROUND:								return L"background.bmp";
	case TEXTURE_TYPE::DEVMAP:									return L"devmap.bmp";
	case TEXTURE_TYPE::TITLE:									return L"title.bmp";
	case TEXTURE_TYPE::CHARACTER:								return L"character.bmp";
	case TEXTURE_TYPE::CHARACTER_ICON:							return L"character_icon.bmp";
	case TEXTURE_TYPE::OBJECT_ICON:								return L"object_icon.bmp";
	case TEXTURE_TYPE::BTN_START:								return L"btn_start.bmp";
	case TEXTURE_TYPE::BTN_EDIT:								return L"btn_edit.bmp";
	case TEXTURE_TYPE::BTN_USE:									return L"btn_use.bmp";
	case TEXTURE_TYPE::BTN_MAP:									return L"btn_map.bmp";
	case TEXTURE_TYPE::BTN_SETTING:								return L"btn_setting.bmp";
	case TEXTURE_TYPE::BTN_X:									return L"btn_x.bmp";
	case TEXTURE_TYPE::BTN_PLAYAGAIN:							return L"btn_playagain.bmp";
	case TEXTURE_TYPE::BTN_QUIT:								return L"btn_quit.bmp";
	case TEXTURE_TYPE::BTN_PLAYER_START:						return L"\\Editor\\btn_playerstart.bmp";
	case TEXTURE_TYPE::BTN_WAY_POINTS:							return L"\\Editor\\btn_waypoints.bmp";
	case TEXTURE_TYPE::BTN_WALL_VERTICES:						return L"\\Editor\\btn_wallvertices.bmp";
	case TEXTURE_TYPE::BTN_DATA_UPLOAD:							return L"\\Editor\\btn_dataupload.bmp";
	case TEXTURE_TYPE::BTN_TIMED_BUTTONS:						return L"\\Editor\\btn_timedbuttons.bmp";
	case TEXTURE_TYPE::BTN_NUMBER_SEQUENCE:						return L"\\Editor\\btn_numbersequence.bmp";

	case TEXTURE_TYPE::WIN:										return L"win.bmp";
	case TEXTURE_TYPE::LOSE:									return L"lose.bmp";

	case TEXTURE_TYPE::PROGRESSBAR_FRAME:						return L"progressbar_frame.bmp";
	case TEXTURE_TYPE::PROGRESSBAR:								return L"progressbar.bmp";
	case TEXTURE_TYPE::MAP:										return L"map.bmp";
	case TEXTURE_TYPE::TASK_NUMBER_SEQUENCE_FRAME:				return L"\\Tasks\\NumberSequence\\frame.bmp";
	case TEXTURE_TYPE::TASK_NUMBER_SEQUENCE_1:					return L"\\Tasks\\NumberSequence\\numberpad_1.bmp";
	case TEXTURE_TYPE::TASK_NUMBER_SEQUENCE_2:					return L"\\Tasks\\NumberSequence\\numberpad_2.bmp";
	case TEXTURE_TYPE::TASK_NUMBER_SEQUENCE_3:					return L"\\Tasks\\NumberSequence\\numberpad_3.bmp";
	case TEXTURE_TYPE::TASK_NUMBER_SEQUENCE_4:					return L"\\Tasks\\NumberSequence\\numberpad_4.bmp";
	case TEXTURE_TYPE::TASK_NUMBER_SEQUENCE_5:					return L"\\Tasks\\NumberSequence\\numberpad_5.bmp";
	case TEXTURE_TYPE::TASK_NUMBER_SEQUENCE_6:					return L"\\Tasks\\NumberSequence\\numberpad_6.bmp";
	case TEXTURE_TYPE::TASK_NUMBER_SEQUENCE_7:					return L"\\Tasks\\NumberSequence\\numberpad_7.bmp";
	case TEXTURE_TYPE::TASK_NUMBER_SEQUENCE_8:					return L"\\Tasks\\NumberSequence\\numberpad_8.bmp";
	case TEXTURE_TYPE::TASK_NUMBER_SEQUENCE_9:					return L"\\Tasks\\NumberSequence\\numberpad_9.bmp";
	case TEXTURE_TYPE::TASK_NUMBER_SEQUENCE_10:					return L"\\Tasks\\NumberSequence\\numberpad_10.bmp";
	case TEXTURE_TYPE::TASK_DATA_UPLOAD_FRAME:					return L"\\Tasks\\DataUpload\\frame.bmp";
	case TEXTURE_TYPE::TASK_DATA_UPLOAD_PROGRESSBAR_FRAME:		return L"\\Tasks\\DataUpload\\progressbar.bmp";
	case TEXTURE_TYPE::TASK_DATA_UPLOAD_PROGRESSBAR:			return L"\\Tasks\\DataUpload\\progress.bmp";
	case TEXTURE_TYPE::TASK_DATA_UPLOAD_BTN:					return L"\\Tasks\\DataUpload\\button.bmp";
	case TEXTURE_TYPE::TASK_TIMED_BUTTONS_FRAME:				return L"\\Tasks\\TimedButtons\\frame.bmp";
	case TEXTURE_TYPE::TASK_TIMED_BUTTONS_BUTTON:				return L"\\Tasks\\TimedButtons\\button.bmp";
	case TEXTURE_TYPE::TASK_TIMED_BUTTONS_PROGRESSBAR_FRAME:	return L"\\Tasks\\TimedButtons\\progressbar.bmp";
	case TEXTURE_TYPE::TASK_TIMED_BUTTONS_PROGRESSBAR:			return L"\\Tasks\\TimedButtons\\progress.bmp";
	case TEXTURE_TYPE::TASK_TIMED_BUTTONS_TIMINGBAR:			return L"\\Tasks\\TimedButtons\\timingbar.bmp";
	case TEXTURE_TYPE::TASK_TIMED_BUTTONS_TIMINGCURSOR:			return L"\\Tasks\\TimedButtons\\timingbarcursor.bmp";
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