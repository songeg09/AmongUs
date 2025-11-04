#pragma once
#include "PathManager.h"

enum TEXTURE_TYPE
{
	BACKGROUND,
	PLAYER_IDLE_START,
	PLAYER_IDLE_1 = PLAYER_IDLE_START,
	PLAYER_IDLE_2,
	PLAYER_IDLE_3,
	PLAYER_IDLE_4,
	PLAYER_IDLE_5,
	PLAYER_IDLE_6,
	PLAYER_IDLE_END,
	PLAYER_RUN_START,
	PLAYER_RUN_1 = PLAYER_RUN_START,
	PLAYER_RUN_2,
	PLAYER_RUN_3,
	PLAYER_RUN_4,
	PLAYER_RUN_5,
	PLAYER_RUN_6,
	PLAYER_RUN_END,
	PLAYER_ATTACK_START,
	PLAYER_ATTACK_1 = PLAYER_ATTACK_START,
	PLAYER_ATTACK_2,
	PLAYER_ATTACK_3,
	PLAYER_ATTACK_4,
	PLAYER_ATTACK_END,
	MONSTER_IDLE_START,
	MONSTER_IDLE_1 = MONSTER_IDLE_START,
	MONSTER_IDLE_2,
	MONSTER_IDLE_3,
	MONSTER_IDLE_END,
	EFFECT_01_START,
	EFFECT_01_01 = EFFECT_01_START,
	EFFECT_01_02,
	EFFECT_01_03,
	EFFECT_01_04,
	EFFECT_01_05,
	EFFECT_01_06,
	EFFECT_01_END,
	EFFECT
};

class Texture;
class Data;
class ResourceManager
{
	SINGLETON(ResourceManager)
private:
	std::map<std::wstring, Texture*> m_MapTexture;
	std::map<std::wstring, std::vector<Data*>> m_MapData;
	std::wstring GetTextureFileName(TEXTURE_TYPE _eTextureType, DIRECTION _eDirection = DIRECTION::END);
	std::wstring GetDirectionString(DIRECTION _eDirection);
public:
	void Init();
	Texture* LoadTexture(TEXTURE_TYPE _eTextureType, DIRECTION _eDirection = DIRECTION::END);
	Texture* LoadSubTexture(TEXTURE_TYPE _eTextureType, int _iStartTextureIndexI, int _iStartTextureIndexJ, int _Size );
	Texture* FindTexture(const std::wstring& _strKey);

	Data* GetData(std::wstring _strkey, int _iIndex);

	template<typename DataType>
	void LoadData(std::wstring _strFileName)
	{
		std::wifstream load;
		load.open(PathManager::GetInstance()->GetContentpath() + ConstValue::strDataPath + _strFileName);
		if (load.is_open())
		{
			int count;
			load >> count;
			m_MapData[_strFileName].resize(count);
			for (int i = 0; i < count; ++i)
			{
				DataType* data = new DataType;
				data->Load(load);
				m_MapData[_strFileName][i] = data;
			}
		}
	}
};

