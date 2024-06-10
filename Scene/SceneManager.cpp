#include "SceneManager.h"
#include "Scene.h"
#include "SceneFade.h"
#include "SoundManager.h"

void SceneManager::ChangeScene(Scene* scene)
{
	m_updateFunc = &SceneManager::FadeCloseUpdate;
	m_NextScene = scene;
	m_Fade = new SceneFade(*this);
}

void SceneManager::PushScene(Scene* scene)
{
	m_Scene.push_front(scene);			//1個増える
}

void SceneManager::PopScene()
{
	//ポップの結果、シーンが0にならないようにする
	if (m_Scene.size() > 1)
	{
		delete m_Scene.front();
		m_Scene.pop_front();
	}
}

void SceneManager::Update(const InputState& input)
{
	(this->*m_updateFunc)(input);
}

void SceneManager::Draw()
{
	for (int i = static_cast<int>(m_Scene.size() - 1); i >= 0; --i)
	{
		m_Scene[i]->Draw();
	}

	if (m_Fade != nullptr)
	{
		m_Fade->Draw();
	}
}

void SceneManager::GameEnd()
{
	ClearAllScene();

	m_isEnd = true;
}

void SceneManager::ClearAllScene()
{
	//シーンスタックが空ではなかったら...
	if (!m_Scene.empty())
	{
		// 現在実行中のシーンをすべて削除
		for (auto& scenes : m_Scene)
		{
			delete scenes;
		}
		m_Scene.clear();
	}
}

// シーンの通常更新処理
void SceneManager::SceneNormalUpdate(const InputState& input)
{
	// シーン配列の先頭だけ更新
	m_Scene.front()->Update(input);
}

// シーン変更時の更新処理
void SceneManager::FadeOpenUpdate(const InputState& input)
{
	// フェードシーンの更新
	m_Fade->Update(input);

	if (m_Fade->IsFadeOpen())
	{
		m_updateFunc = &SceneManager::SceneNormalUpdate;
		delete m_Fade;
		m_Fade = nullptr;
	}	
}

void SceneManager::FadeCloseUpdate(const InputState& input)
{
	// フェードシーンの更新
	m_Fade->Update(input);

	if (m_Fade->IsFadeClose())
	{
		// フェード処理を開くほうに変更
		m_updateFunc = &SceneManager::FadeOpenUpdate;
		// 既存のシーンを削除
		ClearAllScene();
		// 新しいシーン作成
		m_Scene.push_front(m_NextScene);
		// 次のシーンとして保存していた中身を削除
		m_NextScene = nullptr;
	}
}
