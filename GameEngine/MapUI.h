#pragma once
#include "UI.h"

class Texture;
class MapUI : public UI
{
private:
	Texture* m_pMap;

public:
	MapUI();
	~MapUI();

	void Init() override;
	void Render(HDC _memDC) override;
};

