#pragma once
#include "UI.h"

class Button;
class TitleUI : public UI
{
private:
	Button* m_btnStart;
	Button* m_btnEdit;
	Button* m_btnQuit;

public:
	TitleUI();
	~TitleUI();

	void Init();
};

