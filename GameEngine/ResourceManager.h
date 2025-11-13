#pragma once
#include "PathManager.h"

enum TEXTURE_TYPE
{
	BACKGROUND,
	DEVMAP,
	TITLE,
	CHARACTER,
	MAP,
	BTN_START,
};

class Texture;
class TextureAtlas;
class Data;
class ResourceManager
{
	SINGLETON(ResourceManager)
private:
	std::map<std::wstring, Texture*> m_MapTexture;
	std::map<std::wstring, TextureAtlas*> m_MapTextureAtlas;
	std::map<std::wstring, std::vector<Data*>> m_MapData;
	std::wstring GetTextureFileName(TEXTURE_TYPE _eTextureType);
public:
	void Init();
	Texture* LoadTexture(TEXTURE_TYPE _eTextureType, bool _bFlipOption = false);
	Texture* FindTexture(const std::wstring& _strKey);

	TextureAtlas* LoadTextureAtlas(TEXTURE_TYPE _eTextureType, Vector2 _vec2Position, Vector2 _vec2Size, int _margin, bool _Flip);
	TextureAtlas* FindTextureAtlas(const std::wstring& _strKey);

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

