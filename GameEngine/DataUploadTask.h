#pragma once
#include "TaskUI.h"

class Button;
class Texture;
class ProgressBar;
class DataUploadTask : public TaskUI
{
private:
	Button*			m_btnUpload;
	ProgressBar*	m_ProgressBar;
	float			m_fTimePassed;
	float			m_fUploadTime;
	bool			m_bUploadStarted;

public:
	DataUploadTask();
	~DataUploadTask();

	void Init(
		std::function<void()>	_funcOpenCallback,
		std::function<void()>	_funcCloseCallback,
		std::function<void()>	_funcSuccessCallback,
		std::function<void()>	_funcBtnCloseCallback
	);

	void Update() override;
	void Reset() override;
	void CheckWinStatus() override;
	void Open()	override;
	void StartUpload();
	float Easeout(float _ftime);
};

