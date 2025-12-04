#include "pch.h"
#include "DataUploadTask.h"

#include "ResourceManager.h"
#include "TimerManager.h"
#include "Button.h"
#include "ProgressBar.h"


DataUploadTask::DataUploadTask()
{
	m_fTimePassed = 0.0f;
	m_fUploadTime = 0.0f;
	m_bUploadStarted = false;
}

DataUploadTask::~DataUploadTask()
{
}

void DataUploadTask::Init(std::function<void()> _funcOpenCallback, std::function<void()> _funcCloseCallback, std::function<void()> _funcSuccessCallback, std::function<void()> _funcBtnCloseCallback)
{
	TaskUI::Init(
		TEXTURE_TYPE::TASK_DATA_UPLOAD_FRAME, 
		_funcOpenCallback, 
		_funcCloseCallback, 
		_funcSuccessCallback, 
		nullptr, 
		_funcBtnCloseCallback
	);

	m_btnUpload = std::make_shared<Button>();
	m_btnUpload->Init(
		TEXTURE_TYPE::TASK_DATA_UPLOAD_BTN, 
		Vector2(0.5, 0.6), 
		UIElement::ANCHOR::CENTER, 
		[this]() { StartUpload(); },
		true
	);
	m_arrUIElemetns.push_back(m_btnUpload);

	m_ProgressBar = std::make_shared<ProgressBar>();
	m_ProgressBar->Init(
		TEXTURE_TYPE::TASK_DATA_UPLOAD_PROGRESSBAR_FRAME,
		TEXTURE_TYPE::TASK_DATA_UPLOAD_PROGRESSBAR,
		Vector2(0.5, 0.6),
		UIElement::ANCHOR::CENTER
	);
	m_arrUIElemetns.push_back(m_ProgressBar);

	Reset();
}


void DataUploadTask::Update()
{
	if (m_bVisibility == false)
		return;

	if (m_bUploadStarted == true)
	{
		m_fTimePassed += TimerManager::GetInstance()->GetfDeltaTime();
		m_ProgressBar->SetProgress(easing::Easeout(m_fTimePassed / m_fUploadTime));
	}
	TaskUI::Update();
}

void DataUploadTask::Reset()
{
	m_bUploadStarted = false;
	m_fTimePassed = 0;
	m_fUploadTime = rand() % (int)ConstValue::fMaxUploadTime + 5;
	m_eTaskStatus = TASK_STATUS::PLAYING;
	m_ProgressBar->SetVisibility(false);
	m_btnUpload->SetVisibility(true);
}

void DataUploadTask::CheckWinStatus()
{
	if(m_fTimePassed <= m_fUploadTime)
		m_eTaskStatus = TASK_STATUS::PLAYING;
	else
		m_eTaskStatus = TASK_STATUS::SUCCESS;
}

void DataUploadTask::StartUpload()
{
	m_bUploadStarted = true;
	m_ProgressBar->SetVisibility(true);
	m_btnUpload->SetVisibility(false);
}


