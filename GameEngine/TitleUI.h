#pragma once
#include "UI.h"

class Button;
class TitleUI : public UI
{
private:
	std::unique_ptr<Button> m_btnStart;
	std::unique_ptr<Button> m_btnEdit;
	std::unique_ptr<Button> m_btnQuit;

public:
	TitleUI();
	~TitleUI();

	void Init();
};

