#pragma once
#include "Scene.h"

class Texture;
class EditorScene : public Scene
{
	enum class SELECTED
	{
		NUMBER_SEQUNECE,
		DATA_UPLOAD,
		TIMED_BUTTONS,
		WALL_VERTICES,
		WAY_POINTS,
		PLAYER_START
	};

	enum class UI_TYPE
	{
		EDITOR,
		END,
	};

private:
	Texture*			m_pBackGround;

	std::set<Vector2>	m_arrNumberSequencePos;
	std::set<Vector2>	m_arrDataUploadPos;
	std::set<Vector2>	m_arrTimedButtonsPos;
	std::list<Vector2>	m_arrWallVertices;
	std::set<Vector2>	m_setWayPoints;
	Vector2				m_vec2PlayerStart;

	SELECTED			m_eCurSelected;

	Vector2				m_vec2CurPos;

public:
	EditorScene(std::wstring _strName);
	~EditorScene();

	void Init() override;
	void Update() override;
	void Render(HDC _memDC) override;

	Vector2 GetBackBufferTopLeftInScene() override;
	Vector2 GetViewPortTopLeftInScene() override;
	void Move();

private:
	void PrintSelected(HDC _memDC);
	std::wstring GetSelectedString();
	void DrawObjects();
};

