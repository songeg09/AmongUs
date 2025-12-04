#pragma once
#include "UI.h"

class Button;
class TitleUI : public UI
{
private:
	std::shared_ptr<Button> m_btnStart;
	std::shared_ptr<Button> m_btnEdit;
	std::shared_ptr<Button> m_btnQuit;

public:
	TitleUI();
	~TitleUI();

	void Init();
};

