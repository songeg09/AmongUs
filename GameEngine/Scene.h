#pragma once

class Object;
class Collider;
class UI;
class Wall;
class WallDetector;
class Scene
{
protected:
	Vector2 m_vec2SceneSize;		// 씬의 최종적으로 전체 크기를 설정 (맵의 크기라고 생각하면 편함)
	Vector2 m_vec2BackBufferSize;	// 뷰포트 사이즈보다 살짝 커서 포트내에 물체들이 범위내에 있고
									// 어색하게 그려지지 않게 도와주는 버퍼
	float   m_fGuardBandPx;

	std::set<std::weak_ptr<Object>>				m_setObjects;
	std::set<std::weak_ptr<WallDetector>>		m_setWallDetectors;
	std::list<std::unique_ptr<Wall>>			m_listWalls;

	std::wstring								m_strName;

	std::vector<std::unique_ptr<UI>>			m_arrUIs;
	Flags										m_UIFlags;
	Flags										m_PrevUIFlags;

public:
	Scene(std::wstring _strName);
	virtual ~Scene();
	virtual void Update();
	void LateUpdate();
	virtual void Render(HDC _memDC);
	virtual void Init();
	virtual void Release();

	void AddObject(Object* _object);
	void CreateWall(Vector2 _vec2Start, Vector2 _vec2End);
	void RegisterWallDetector(std::shared_ptr<WallDetector> _wallDetector);
	void UnregisterWallDetector(std::shared_ptr<WallDetector>  _wallDetector);
	inline void SetName(const std::wstring _strName) { m_strName = _strName; }

	inline Vector2 GetSceneSize() { return m_vec2SceneSize; }
	Vector2 GetBackBufferSize() { return m_vec2BackBufferSize; }
	
	virtual void ConfigureRenderSurface(Vector2 _vec2SceneSize, float _fGuardBandPx);
	Vector2 GetViewportTopLeftInBackBuffer() { return Vector2(m_fGuardBandPx, m_fGuardBandPx); }
	virtual Vector2 GetViewPortTopLeftInScene() { return GetBackBufferTopLeftInScene() + Vector2(m_fGuardBandPx, m_fGuardBandPx); }
	virtual Vector2 GetBackBufferTopLeftInScene() { return Vector2(-m_fGuardBandPx, -m_fGuardBandPx); }

	virtual void OpenUI(int _flagIndex);
	virtual void UpdateUIVisibility();
};

