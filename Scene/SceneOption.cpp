#include "SceneOption.h"
#include "SceneManager.h"
#include "SoundManager.h"

namespace
{
	// オプション画面描画座標
	constexpr int kMenuWidth = 200;
	constexpr int kMenuHeight = 200;
	// テキスト描画位置
	constexpr float kTextDrawPosY = Game::kScreenHeightHalf - 80.0f;
	// テキスト描画間隔
	constexpr float kTextDistance = 70.0f;
	// サウンドテキストの間隔
	constexpr float kSoundTextDistance = 230.0f;

	// 音量変化量
	constexpr int kVolumeChangeNum = 10;

	// 選択可能項目の数
	constexpr int kSelectItemNum = 3;
	// テキスト
	const char* const kTextScene = "～設定～";
	const char* const kTextReturn = "閉じる";
	const char* const kTextBGM = "音楽";
	const char* const kTextSE = "効果音";
	const char* const kTextSave = "保存して閉じる";
}

SceneOption::SceneOption(SceneManager& manager) :
	Scene(manager),
	m_countFrame(0),
	m_volumeBGM(0),
	m_volumeSE(0),
	m_selectedPos(0),
	m_selectedItemName(),
	m_hBgFrame(-1),
	m_hMusicVolImg(-1),
	m_hCursor(-1),
	m_isCursorRanged(false),
	m_isVolumeChangeMode(false)
{
	m_hBgFrame = LoadGraph("Data/ImageData/OptionBg.png");
	m_hMusicVolImg = LoadGraph("Data/ImageData/soundVol.png");
	m_hCursor = LoadGraph("Data/ImageData/Chalk.png");

	Init();
}

SceneOption::~SceneOption()
{
	DeleteGraph(m_hBgFrame);
	DeleteGraph(m_hMusicVolImg);
	DeleteGraph(m_hCursor);
}

void SceneOption::Init()
{
	m_volumeSE =  SoundManager::GetInstance().GetSEVolume();
	m_volumeBGM = SoundManager::GetInstance().GetBGMVolume();
	m_exVolumeBGM = m_volumeBGM;
	m_exVolumeSE = m_volumeSE;
}

void SceneOption::Update(const InputState& input)
{
	int t = 0;
	/*if (input.IsTriggered(InputType::left))
	{
		t = GetMouseWheelRotVol();
	}
	if (input.IsTriggered(InputType::right))
	{
		t = GetMouseWheelRotVol();
	}*/

	m_countFrame++;
	if (m_countFrame > 600)
	{
		m_countFrame = 0;
	}

	if (input.IsTriggered(InputType::pause))
	{
		m_Manager.PopScene();
		return;
	}

	if (m_isVolumeChangeMode)
	{
		ChangeVolume(input);
	}
	else
	{
		CursorUpdate(input);
	}

	if (input.IsTriggered(InputType::select) && m_isCursorRanged)
	{
		OnSelect();
	}
}

void SceneOption::Draw()
{
	int drawX = Game::kScreenWidthHalf - kMenuWidth, drawY = Game::kScreenHeightHalf - kMenuHeight;
	int drawX2 = Game::kScreenWidthHalf + kMenuWidth, drawY2 = Game::kScreenHeightHalf + kMenuHeight;

	DrawRotaGraph(Game::kScreenWidthHalf, Game::kScreenHeightHalf, 1.0, 0.0, m_hBgFrame, true);

	DrawMenuText();
}

void SceneOption::ChangeVolume(const InputState& input)
{
	if (m_selectedPos == 1)
	{
		ControllVolume(input, m_volumeBGM);
	}
	else if (m_selectedPos == 2)
	{
		ControllVolume(input, m_volumeSE);
	}
}

void SceneOption::ControllVolume(const InputState& input, int& volume)
{
	if (input.IsTriggered(InputType::right))
	{
		volume += kVolumeChangeNum;
		if (volume > 100) volume = 100;
		SetVolumeInfo();
	}
	if (input.IsTriggered(InputType::left))
	{
		volume -= kVolumeChangeNum;
		if (volume < 0) volume = 0;
		SetVolumeInfo();
	}
}

void SceneOption::SetVolumeInfo()
{
	SoundManager::GetInstance().SetSEVolume(m_volumeSE);
	SoundManager::GetInstance().SetBGMVolume(m_volumeBGM);
}

void SceneOption::ResetVolumeInfo()
{
	SoundManager::GetInstance().SetSEVolume(m_exVolumeSE);
	SoundManager::GetInstance().SetBGMVolume(m_exVolumeBGM);
}

void SceneOption::DrawSoundBar(float drawX, float drawY , int volume)
{
	int barColorBGM = 0xffffff, barColorSE = 0xffffff;
	if (m_selectedPos == 1) barColorBGM = Game::kColorCyan;
	if (m_selectedPos == 2) barColorSE = Game::kColorCyan;

	for (int i = 0; i < 10; i++)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 75);
		DrawRotaGraphF(drawX + (i * 40), drawY + 25.0f, 0.2, 0.0, m_hMusicVolImg, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	int n = 0;
	n = volume / kVolumeChangeNum;
	for (int i = 0; i < n; i++)
	{
		DrawRotaGraphF(drawX + (i * 40), drawY + 25.0f, 0.2, 0.0, m_hMusicVolImg, true);
	}
}

void SceneOption::DrawMenuText()
{
	float drawX = 0.0f, drawY = 0.0f;
	drawX = static_cast<float>(Game::kScreenWidthHalf - (GetDrawFormatStringWidth(kTextScene) / 2));
	drawY = Game::kScreenHeightHalf - 160.0f;
	DrawStringF(drawX, drawY, kTextScene, 0xffffff);

	for (int i = 0; i <= kSelectItemNum; i++)
	{
		if (m_isVolumeChangeMode)
		{
			if (i == m_selectedPos) continue;
		}

		std::string tSelectedItemName;
		tSelectedItemName = GetCurrentText(i);
		int textLength = GetDrawFormatStringWidth(tSelectedItemName.c_str());
		drawX = static_cast<float>(Game::kScreenWidthHalf - ( textLength / 2));
		drawY = static_cast<float>(kTextDrawPosY) + (i * kTextDistance);

		DrawFormatStringF(drawX, drawY, Game::kColorGray, "%s", tSelectedItemName.c_str());
	}

	m_selectedItemName = GetCurrentText(m_selectedPos);
	drawX = static_cast<float>(Game::kScreenWidthHalf - (GetDrawFormatStringWidth(m_selectedItemName.c_str()) / 2));
	drawY = static_cast<float>(kTextDrawPosY) + (m_selectedPos * kTextDistance);
	if (m_isVolumeChangeMode)
	{
		int* volume = 0;
		if (m_selectedPos == 1) volume = &m_volumeBGM;
		else if (m_selectedPos == 2)volume = &m_volumeSE;
		DrawSoundBar(Game::kScreenWidthHalf - 180.0f, drawY, *volume);
		if (m_selectedPos == 1 || m_selectedPos == 2) return;
	}
	if ((m_countFrame / 10) % 6 != 0)
	{
		DrawFormatStringF(drawX, drawY - 2, Game::kColorWhite, "%s", m_selectedItemName.c_str());
		DrawRotaGraphF(drawX - Game::kFontSize, drawY + 25, 0.2, 0.0, m_hCursor, true);
	}
}

void SceneOption::CursorUpdate(const InputState& input)
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

void SceneOption::OnSelect()
{
	if (m_selectedPos == 0)
	{
		ResetVolumeInfo();
		SoundManager::GetInstance().PlaySE(SoundType::select);
		m_Manager.PopScene();
	}
	else if (m_selectedPos == 1 || m_selectedPos == 2)
	{
		if (!m_isVolumeChangeMode)
		{
			m_isVolumeChangeMode = true;
		}
		else
		{
			m_isVolumeChangeMode = false;
		}
	}
	else if (m_selectedPos == 3)
	{
		SoundManager::GetInstance().PlaySE(SoundType::select);
		m_Manager.PopScene();
	}
}

std::string SceneOption::GetCurrentText(int textNum)
{
	std::string text;

	if (textNum == 0)
	{
		text = kTextReturn;
	}
	else if (textNum == 1)
	{
		text = kTextBGM;
	}
	else if (textNum == 2)
	{
		text = kTextSE;
	}
	else if (textNum == 3)
	{
		text = kTextSave;
	}

	return text;
}