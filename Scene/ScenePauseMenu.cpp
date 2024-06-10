#include "ScenePauseMenu.h"
#include "Game.h"
#include "SceneManager.h"
#include "SceneOption.h"
#include "SceneTitleMenu.h"
#include "SceneMain.h"

namespace
{
	// 選択可能項目の数
	constexpr int kSelectItemNum = 3;
	// テキスト
	const char* const kTextPause = "～ポーズ～";
	const char* const kTextReturn = "戻る";
	const char* const kTextRestart = "再テスト？";
	const char* const kTextSetting = "設定";
	const char* const kTextGameEnd = "タイトルへ";
	// テキスト間隔
	constexpr float kTextDistance = Game::kFontSize + 20;
	// 項目描画位置
	constexpr float kTextDrawPosY = Game::kGameHeightHalf - Game::kFontSize;
}

ScenePauseMenu::ScenePauseMenu(SceneManager& manager) :
	Scene(manager),
	m_countFrame(0),
	m_selectedPos(0),
	m_selectedItemName(),
	m_hCursorImg(-1),
	m_isCursorRanged(false)
{
	m_hCursorImg = LoadGraph("Data/ImageData/chalk.png");
}

ScenePauseMenu::~ScenePauseMenu()
{
	DeleteGraph(m_hCursorImg);
}

void ScenePauseMenu::Update(const InputState& input)
{
	m_countFrame++;
	if (m_countFrame > 600)
	{
		m_countFrame = 0;
	}

	if (input.IsTriggered(InputType::pause))
	{
		SoundManager::GetInstance().RestartCurrentBGM();
		m_Manager.PopScene();
		return;
	}

	CursorUpdate(input);

	if (input.IsTriggered(InputType::select) && m_isCursorRanged)
	{
		SoundManager::GetInstance().PlaySE(SoundType::select);

		if (m_selectedPos == 0)
		{
			SoundManager::GetInstance().RestartCurrentBGM();
			m_Manager.PopScene();
		}
		else if (m_selectedPos == 1)
		{
			m_Manager.ChangeScene(new SceneMain(m_Manager));
		}
		else if (m_selectedPos == 2)
		{
			m_Manager.PushScene(new SceneOption(m_Manager));
		}
		else if (m_selectedPos == 3)
		{
			m_Manager.ChangeScene(new SceneTitleMenu(m_Manager));
		}
		return;
	}
}

void ScenePauseMenu::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	
	DrawMenuText();
}

std::string ScenePauseMenu::GetCurrentText(int textNum)
{
	std::string text;

	
	if (textNum == 0)
	{
		text = kTextReturn;
	}
	else if (textNum == 1)
	{
		text = kTextRestart;
	}
	else if (textNum == 2)
	{
		text = kTextSetting;
	}
	else if (textNum == 3)
	{
		text = kTextGameEnd;
	}

	return text;
}

void ScenePauseMenu::DrawMenuText()
{
	float drawX = 0.0f, drawY = 0.0f;
	drawX = static_cast<float>(Game::kScreenWidthHalf - (GetDrawFormatStringWidth(kTextPause) / 2));
	drawY = Game::kGameHeightHalf - 100.0f;
	DrawStringF(drawX, drawY, kTextPause, 0xffffff);

	for (int i = 0; i <= kSelectItemNum; i++)
	{
		std::string tSelectedItemName;
		tSelectedItemName = GetCurrentText(i);
		drawX = static_cast<float>(Game::kScreenWidthHalf - (GetDrawFormatStringWidth(tSelectedItemName.c_str()) / 2));
		drawY = static_cast<float>(kTextDrawPosY) + (i * kTextDistance);

		DrawFormatStringF(drawX, drawY, Game::kColorGray, "%s", tSelectedItemName.c_str());
	}

	m_selectedItemName = GetCurrentText(m_selectedPos);
	int textLength = GetDrawFormatStringWidth(m_selectedItemName.c_str());
	drawX = static_cast<float>(Game::kScreenWidthHalf - (textLength / 2));
	drawY = static_cast<float>(kTextDrawPosY) + (m_selectedPos * kTextDistance);
	DrawFormatStringF(drawX, drawY - 2, Game::kColorWhite, "%s", m_selectedItemName.c_str());

	if ((m_countFrame / 10) % 6 != 0)
	{
		DrawRotaGraphF(drawX - Game::kFontSize, drawY + 25.0f, 0.2, 0.0, m_hCursorImg, true);
		DrawRotaGraphF(drawX + textLength + Game::kFontSize, drawY + 25.0f, 0.2, 0.0, m_hCursorImg, true);
	}
}

void ScenePauseMenu::CursorUpdate(const InputState& input)
{
	m_isCursorRanged = false;
	int buttonPosX = 0, buttonPosY = Game::kScreenHeightHalf;
	std::string tText;
	for (int i = 0; i <= kSelectItemNum; i++)
	{
		tText = GetCurrentText(i);
		int textLength = GetDrawFormatStringWidth(tText.c_str());
		buttonPosX = static_cast<int>(Game::kScreenWidthHalf - (textLength / 2));
		buttonPosY = static_cast<int>(kTextDrawPosY + (kTextDistance * i));

		if (input.GetMousePos().x > buttonPosX && input.GetMousePos().x < buttonPosX + textLength
			&& input.GetMousePos().y > buttonPosY && input.GetMousePos().y < buttonPosY + Game::kFontSize)
		{
			m_isCursorRanged = true;
			m_selectedPos = i;
		}
	}
}
