#pragma once
#include "UI.h"

class Button;
class EditorUI : public UI
{
private:
	std::unique_ptr<Button>		m_btnPlayerStart;
	std::unique_ptr<Button>		m_btnWayPoints;
	std::unique_ptr<Button>		m_btnWallVertices;
	std::unique_ptr<Button>		m_btnVent;
	std::unique_ptr<Button>		m_btnDataUpload;
	std::unique_ptr<Button>		m_btnTimedButtons;
	std::unique_ptr<Button>		m_btnNumberSequence;

	std::unique_ptr<Button>		m_btnBacktoTitle;
	std::unique_ptr<Button>		m_btnSave;
	std::unique_ptr<Button>		m_btnRemoveLast;
	std::unique_ptr<Button>		m_btnClearSelected;

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

