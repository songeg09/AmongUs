#pragma once
#include "UI.h"

class Button;
class TitleUI : public UI
{
private:
	Button* m_btnStart;
	Button* m_btnSetting;
	Button* m_btnExit;

public:
	TitleUI();
	~TitleUI();

	void Init() override;

	void OnClick();
};

