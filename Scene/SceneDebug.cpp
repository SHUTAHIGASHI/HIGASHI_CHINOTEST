#include "SceneDebug.h"
#include "Game.h"
#include "SceneManager.h"
#include "SceneMain.h"
#include "SceneTitleMenu.h"
#include "ScenePauseMenu.h"
#include "SceneCredit.h"
#include "SceneResult.h"

namespace
{
	// 選択可能項目の数
	constexpr int kSelectItemNum = 5;
	// テキスト
	const char* const kTextGameMain = "メイン";
	const char* const kTextGameTitleMenu = "タイトル";
	const char* const kTextGamePause = "ポーズ";
	const char* const kTextCredit = "クレジット";
	const char* const kTextGameOver = "オーバー";
	const char* const kTextGameEnd = "終了";
}

SceneDebug::SceneDebug(SceneManager& manager) :
	Scene(manager),
	m_selectedPos(0),
	m_selectedItemName()
{
}

SceneDebug::~SceneDebug()
{
}

void SceneDebug::Update(const InputState& input)
{
	if (input.IsTriggered(InputType::back))
	{
		m_Manager.GameEnd();
		return;
	}

	if (input.IsTriggered(InputType::select))
	{
		SoundManager::GetInstance().PlaySE(SoundType::select);

		if (m_selectedPos == 0)
		{
			m_Manager.ChangeScene(new SceneMain(m_Manager));
		}
		else if (m_selectedPos == 1)
		{
			m_Manager.ChangeScene(new SceneTitleMenu(m_Manager));
		}
		else if (m_selectedPos == 2)
		{
			m_Manager.PushScene(new ScenePauseMenu(m_Manager));
		}
		else if (m_selectedPos == 3)
		{
			m_Manager.ChangeScene(new SceneCredit(m_Manager));
		}
		else if (m_selectedPos == 4)
		{
			m_Manager.PushScene(new SceneResult(m_Manager));
		}
		else
		{
			m_Manager.GameEnd();
		}
		return;
	}

	if (input.IsTriggered(InputType::up))
	{
		m_selectedPos--;
		if (m_selectedPos < 0) m_selectedPos = kSelectItemNum;
	}
	else if (input.IsTriggered(InputType::down))
	{
		m_selectedPos++;
		if (m_selectedPos > kSelectItemNum) m_selectedPos = 0;
	}

	UpdateText();
}

void SceneDebug::Draw()
{
	DrawFormatString(100, 100, 0xffffff, "デバックシーン");
	DrawFormatString(Game::kScreenWidthHalf, Game::kScreenHeightHalf, 0xffff00, "%s", m_selectedItemName.c_str());
}

void SceneDebug::UpdateText()
{
	if (m_selectedPos == 0)
	{
		m_selectedItemName = kTextGameMain;
	}
	else if (m_selectedPos == 1)
	{
		m_selectedItemName = kTextGameTitleMenu;
	}
	else if (m_selectedPos == 2)
	{
		m_selectedItemName = kTextGamePause;
	}
	else if (m_selectedPos == 3)
	{
		m_selectedItemName = kTextCredit;
	}
	else if (m_selectedPos == 4)
	{
		m_selectedItemName = kTextGameOver;
	}
	else
	{
		m_selectedItemName = kTextGameEnd;
	}
}
