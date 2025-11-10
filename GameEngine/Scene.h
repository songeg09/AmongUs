#pragma once

class Object;
class Collider;
class Scene
{
protected:
	Vector2 m_vec2SceneSize;
	Vector2 m_vec2ViewPortSize;
	Vector2 m_vec2BackBufferSize;

	std::vector<Object*>	m_arrObjects;
	std::vector<Collider*>  m_arrColliders[static_cast<int>(COLLISION_TAG::END)];
	std::wstring			m_strName;
public:
	Scene(std::wstring _strName);
	virtual ~Scene();
	virtual void Update();
	void LateUpdate();
	virtual void Render(HDC _memDC);
	virtual void Init() = 0;
	virtual void Release();

	const std::vector<Collider*>& GetCollisionTagGroup(COLLISION_TAG _eCollsionTag) {return m_arrColliders[static_cast<int>(_eCollsionTag)]; }
	void SetSceneSize(int _iWidth, int _iHeight);
	void AddObject(Object* _object);
	void AddCollider(Collider* _collider, COLLISION_TAG _eTag);
	inline Vector2 GetSceneSize() { return m_vec2SceneSize; }
	inline void SetName(const std::wstring _strName) { m_strName = _strName; }

	Vector2 GetViewPortSize() { return m_vec2ViewPortSize; }
	void SetViewPortSize(Vector2 _Size);
	Vector2 GetViewportTopLeftInBackBuffer();
	Vector2 GetBackBufferSize() { return m_vec2BackBufferSize; }
	virtual Vector2 GetViewPortTopLeftInScene() { return Vector2(0, 0); }
	virtual Vector2 GetBackBufferTopLeftInScene() { return Vector2(-m_vec2ViewPortSize.m_fx / 2, -m_vec2ViewPortSize.m_fy / 2); }

	void 
};

