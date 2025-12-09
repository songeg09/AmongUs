#pragma once
#include "Scene.h"
#include "MapInfo.h"

class Texture;
class EditorScene : public Scene
{
	enum class SELECTED
	{
		NUMBER_SEQUNECE,
		DATA_UPLOAD,
		TIMED_BUTTONS,
		WALL_VERTICES,
		VENT,
		WAY_POINTS,
		PLAYER_START
	};

	enum class UI_TYPE
	{
		EDITOR,
		END,
	};

private:
	std::weak_ptr<Texture>				m_pBackGround;

	MapInfo								m_MapInfo;
	std::vector<Vector2>				m_arrCurWallVertices;

	SELECTED							m_eCurSelected;
	bool								m_bUIClicked;

	Vector2								m_vec2CurPos;

public:
	EditorScene(std::wstring _strName);
	~EditorScene();

	void Init() override;
	void Update() override;
	void Render(HDC _memDC) override;
	void Release() override;

	Vector2 GetBackBufferTopLeftInScene() override;
	Vector2 GetViewPortTopLeftInScene() override;
	void Move();
	void InputCheck();

private:
	void PrintSelected(HDC _memDC);
	void DrawObjects(HDC _memDC);
	void DrawRect(HDC _memDC, Vector2 _BackBufferTopLeftInScene, Vector2 Pos, Vector2 _Size);
	void DrawLine(HDC _memDC, Vector2 _BackBufferTopLeftInScene, Vector2 StartPos, Vector2 EndPos);
	void DrawCircle(HDC _memDC, Vector2 _BackBufferTopLeftInScene, Vector2 _Pos, float _Size);

	std::wstring GetSelectedString();

	void PlaceObject(Vector2 _vec2Pos);
	void ChangeSelected(SELECTED _eNewSelected);
	void RemoveLast();
	void Save();
	void ClearSelected();
	void BacktoTitle();
};

