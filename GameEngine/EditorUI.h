#pragma once
#include "UI.h"

class Button;
class EditorUI : public UI
{
private:
	Button*		m_btnPlayerStart;
	Button*		m_btnWayPoints;
	Button*		m_btnWallVertices;
	Button*		m_btnVent;
	Button*		m_btnDataUpload;
	Button*		m_btnTimedButtons;
	Button*		m_btnNumberSequence;

	Button*		m_btnBacktoTitle;
	Button*		m_btnSave;
	Button*		m_btnRemoveLast;
	Button*		m_btnClearSelected;

public:
	EditorUI();
	~EditorUI();

	void Init(
		std::function<void()> _funcPlayerStartBtnCallback,
		std::function<void()> _funcWayPointsBtnCallBack,
		std::function<void()> _funcWallVerticesBtnCallback,
		std::function<void()> _funcVentBtnCallback,
		std::function<void()> _funcDataUploadBtnCallback,
		std::function<void()> _funcTimedButtonsBtnCallback,
		std::function<void()> _funcNumberSequenceBtnCallback,

		std::function<void()> _funcBackToTitleCallback,
		std::function<void()> _funcSaveCallback,
		std::function<void()> _funcRemoveLastCallback,
		std::function<void()> _funcClearSelectedCallback
	);
	void Render(HDC _memDC) override;
};

