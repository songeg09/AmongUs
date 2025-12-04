#pragma once 

class Object;
class WallDetector : public std::enable_shared_from_this<WallDetector>
{
private:
	std::weak_ptr<Object>   m_pOwner;
	Vector2					m_vec2Offset;
	Vector2					m_vec2Position;
	float					m_fRadius;

public:
	WallDetector();
	~WallDetector();

	void Init(std::shared_ptr<Object> _pOwner, Vector2 _vec2Offset, float _fRadius);
	void Update();
	void Render(HDC _memDC);
	
	Vector2 GetPosition() { return m_vec2Position; }
	float GetRadius() { return m_fRadius; }
	void ResolvePos(Vector2 _vec2ResolveVec);
};

