#pragma once
#include "Scene.h"
enum class SCENE_TYPE
{
	TITLE,
	GAME,
	EDITOR,
	END,
};

class Scene;
class SceneManager
{
	SINGLETON(SceneManager)
private:
	Scene*			m_arrScene[static_cast<int>(SCENE_TYPE::END)];
	SCENE_TYPE		m_eCurScene;
	SCENE_TYPE		m_eRequestedScene;
public:
	void Init();
	void Update();
	void Render(HDC _memDC);

	void SceneChange(SCENE_TYPE _eSceneType);
	void RequestSceneChange(SCENE_TYPE _eSceneType);
	void ProcessSceneChange();

	Scene* GetCurScene() {
		if (m_eCurScene == SCENE_TYPE::END)
			return nullptr;
		return m_arrScene[static_cast<int>(m_eCurScene)];
	}
};

