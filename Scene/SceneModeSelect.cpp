#include "SceneModeSelect.h"
#include "SceneManager.h"
#include "SceneTitleMenu.h"
#include "Game.h"

namespace
{
	// 項目数
	constexpr int kSelectItemNum = 3 - 1;
	// テキスト
	const char* const kTextStart = "モード選択";
	const char* const kTextTimeLimit = "30秒チャレンジ";
	const char* const kTextQuestionLimit = "15問チャレンジ";
	const char* const kTextAllChallenge = "全問チャレンジ";
	// テキスト描画位置
	constexpr float kTextDrawPosY = Game::kGameHeightHalf - 50.0f;
	// テキスト間隔
	constexpr float kTextDistance = 75.0f;
}

SceneModeSelect::SceneModeSelect(SceneManager& manager):
	Scene(manager),
	m_countFrame(0),
	m_gameMode(),
	m_selectedItemName(),
	m_selectedPos(0),
	m_hCursorImg(-1),
	m_isCursorRanged(false)
{
	m_hCursorImg = LoadGraph("Data/ImageData/chalk.png");
}

SceneModeSelect::~SceneModeSelect()
{
	DeleteGraph(m_hCursorImg);
}

void SceneModeSelect::Update(const InputState& input)
{
	m_countFrame++;
	if (m_countFrame > 10000)
	{
		m_countFrame = 0;
	}

	if (input.IsTriggered(InputType::pause))
	{
		m_Manager.ChangeScene(new SceneTitleMenu(m_Manager));
	}

	CursorUpdate(input);

	if (input.IsTriggered(InputType::select) && m_isCursorRanged)
	{
		if (m_selectedPos == 0)
		{
			GameDataManager::GetInstance().SetGameMode(GameMode::TIMELIMIT);
		}
		else if (m_selectedPos == 1)
		{
			GameDataManager::GetInstance().SetGameMode(GameMode::QUESTIONLIMIT);
		}
		else if (m_selectedPos == 2)
		{
			GameDataManager::GetInstance().SetGameMode(GameMode::ALLCHALLENGE);
		}

		SoundManager::GetInstance().PlaySE(SoundType::select);
		m_Manager.PopScene();

		return;
	}
}

void SceneModeSelect::Draw()
{
	DrawMenuText();
}

std::string SceneModeSelect::GetCurrentText(int textNum)
{
	std::string text;

	if (textNum == 0)
	{
		text = kTextTimeLimit;
	}
	else if (textNum == 1)
	{
		text = kTextQuestionLimit;
	}
	else if (textNum == 2)
	{
		text = kTextAllChallenge;
	}

	return text;
}

void SceneModeSelect::DrawMenuText()
{
	int drawX = 0, drawY = 0;
	drawX = static_cast<int>(Game::kScreenWidthHalf - (GetDrawFormatStringWidth(kTextStart) / 2));
	drawY = static_cast<int>(kTextDrawPosY - 100.0f);
	DrawString(drawX, drawY, kTextStart, 0xffffff);

	drawX = 0, drawY = static_cast<int>(Game::kScreenHeightHalf);
	std::string tText;
	for (int i = 0; i <= kSelectItemNum; i++)
	{
		tText = GetCurrentText(i);
		drawX = static_cast<int>(Game::kScreenWidthHalf - (GetDrawFormatStringWidth(tText.c_str()) / 2));
		drawY = static_cast<int>(kTextDrawPosY + (i * kTextDistance));
		DrawFormatString(drawX, drawY, Game::kColorGray, "%s", tText.c_str());
	}

	m_selectedItemName = GetCurrentText(m_selectedPos);
	int textLength = GetDrawFormatStringWidth(m_selectedItemName.c_str());
	drawX = static_cast<int>(Game::kScreenWidthHalf - (textLength / 2));
	drawY = static_cast<int>(kTextDrawPosY + (m_selectedPos * kTextDistance));
	DrawFormatString(drawX, drawY - 2, Game::kColorWhite, "%s", m_selectedItemName.c_str());

	if ((m_countFrame / 10) % 6 != 0)
	{
		DrawRotaGraph(drawX - Game::kFontSize, drawY + 25, 0.2, 0.0, m_hCursorImg, true);
		DrawRotaGraph(drawX + textLength + Game::kFontSize, drawY + 25, 0.2, 0.0, m_hCursorImg, true);
	}
}

void SceneModeSelect::CursorUpdate(const InputState& input)
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
