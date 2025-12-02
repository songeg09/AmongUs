#pragma once
#include "PathManager.h"

enum TEXTURE_TYPE
{
	BACKGROUND,
	DEVMAP,
	TITLE,
	CHARACTER,
	CHARACTER_ICON,
	OBJECT_ICON,
	MAP,
	BTN_START,
	BTN_EDIT,
	BTN_USE,
	BTN_MAP,
	BTN_SETTING,
	BTN_X,
	BTN_PLAYAGAIN,
	BTN_QUIT,
	BTN_PLAYER_START,
	BTN_WAY_POINTS,
	BTN_VENT,
	BTN_WALL_VERTICES,
	BTN_DATA_UPLOAD,
	BTN_TIMED_BUTTONS,
	BTN_NUMBER_SEQUENCE,
	BTN_BACK_TO_TITLE,
	BTN_CLEAR_SELECTED,
	BTN_SAVE,
	BTN_REMOVE_LAST,
	WIN,
	LOSE,
	PROGRESSBAR_FRAME,
	PROGRESSBAR,
	TASK_NUMBER_SEQUENCE_FRAME,
	TASK_NUMBER_SEQUENCE_NUMBER_START,
	TASK_NUMBER_SEQUENCE_1 = TASK_NUMBER_SEQUENCE_NUMBER_START,
	TASK_NUMBER_SEQUENCE_2,
	TASK_NUMBER_SEQUENCE_3,
	TASK_NUMBER_SEQUENCE_4,
	TASK_NUMBER_SEQUENCE_5,
	TASK_NUMBER_SEQUENCE_6,
	TASK_NUMBER_SEQUENCE_7,
	TASK_NUMBER_SEQUENCE_8,
	TASK_NUMBER_SEQUENCE_9,
	TASK_NUMBER_SEQUENCE_10,
	TASK_NUMBER_SEQUENCE_NUMBER_END,
	TASK_DATA_UPLOAD_FRAME,
	TASK_DATA_UPLOAD_PROGRESSBAR_FRAME,
	TASK_DATA_UPLOAD_PROGRESSBAR,
	TASK_DATA_UPLOAD_BTN,
	TASK_TIMED_BUTTONS_FRAME,
	TASK_TIMED_BUTTONS_BUTTON,
	TASK_TIMED_BUTTONS_PROGRESSBAR_FRAME,
	TASK_TIMED_BUTTONS_PROGRESSBAR,
	TASK_TIMED_BUTTONS_TIMINGBAR,
	TASK_TIMED_BUTTONS_TIMINGCURSOR,
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

