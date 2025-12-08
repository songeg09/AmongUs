#pragma once
class Core
{
	SINGLETON(Core)
private:
	HWND m_hWnd;
	HDC m_hDC;

	HBITMAP m_hBackBitMap;
	HDC m_hBackDC;

	bool m_bShowCollider;

	void Update();
	void Render();
public:
	void CreateBackDC();
	void Init(HWND _hWnd);
	void GameLoop();
	HWND GethWnd() { return m_hWnd; }
	HDC GetMainDC() { return m_hDC; }
	HDC GetBackDC() { return m_hBackDC; }
	void Terminate();
	bool IsShowCollider() { return m_bShowCollider; }
	void SetShowCollider(bool _bShowCollider) { m_bShowCollider = _bShowCollider; }
};

