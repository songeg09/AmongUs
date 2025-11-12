#pragma once
#include "Scene.h"

class Texture;
class UI;
class TitleScene : public Scene
{
	enum UI_MODE
	{
		TITLE,
		END
	};

private:
	Texture*			m_pBackGround;
	UI*					m_arrUIs[UI_MODE::END];
	UI_MODE				m_eCurUI;

public:
	TitleScene(std::wstring _strName);
	~TitleScene();
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC _memDC) override;
	
};

