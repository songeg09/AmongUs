#pragma once
#include "UI.h"

class Button;
class EditorUI : public UI
{
private:
	Button*		m_btnPlayerStart;
	Button*		m_btnWayPoints;
	Button*		m_btnWallVertices;
	Button*		m_btnDataUpload;
	Button*		m_btnTimedButtons;
	Button*		m_btnNumberSequence;

public:
	EditorUI();
	~EditorUI();

	void Init(
		std::function<void()> _funcPlayerStartBtnCallback,
		std::function<void()> _funcWayPointsBtnCallBack,
		std::function<void()> _funcWallVerticesBtnCallback,
		std::function<void()> _funcDataUploadBtnCallback,
		std::function<void()> _funcTimedButtonsBtnCallback,
		std::function<void()> _funcNumberSequenceBtnCallback
	);
	void Render(HDC _memDC) override;
};

