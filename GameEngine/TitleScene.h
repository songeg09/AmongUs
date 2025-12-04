#pragma once
#include "Scene.h"

class Texture;
class UI;
class TitleScene : public Scene
{
	enum class UI_TYPE
	{
		TITLE,
		END
	};

private:
	std::weak_ptr<Texture>			m_pBackGround;

public:
	TitleScene(std::wstring _strName);
	~TitleScene();
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC _memDC) override;
	
};

