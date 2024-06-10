#include "SceneResult.h"
#include "SceneManager.h"
#include "SceneMain.h"
#include "SceneTitleMenu.h"
#include "StageDirecting.h"

namespace
{
	// �I�����̐�
	constexpr int kSelectItemNum = 1;
	// �`�悷��e�L�X�g
	const char* const kTextRestart = "�ăe�X�g�H";
	const char* const kTextTitle = "�^�C�g����";
	// �Q�[�����[�h�e�L�X�g
	const char* const kTextTimeLimit = "30�b�`�������W";
	const char* const kTextQuestionLimit = "15��`�������W";
	const char* const kTextAllChallenge = "�S��`�������W";

	// �I�����ڕ`��ʒu
	constexpr float kTextDrawPosY = Game::kGameHeightHalf + 90.0f;
	constexpr float kTextDistance = Game::kFontSize + 20.0f;
	// ���ʕ`��ʒu
	constexpr float kResultPosY = Game::kGameHeightHalf - 40.0f;
}

SceneResult::SceneResult(SceneManager& manager):
	Scene(manager),
	m_updateFunc(&SceneResult::NormalUpdate),
	m_gameModeText(),
	m_scoreNum(0),
	m_windowDrawPosX(0),
	m_windowDrawPosY(0),
	m_selectedPos(0),
	m_selectedItemName("EMPTY"),
	m_isCursorRanged(false),
	m_pStage(std::make_shared<StageDirecting>())
{
	m_windowDrawPosX = Game::kScreenWidthHalf;
	m_windowDrawPosY = Game::kScreenHeightHalf;

	SoundManager::GetInstance().PlaySE(SoundType::good);

	SetGameModeName();
	m_scoreNum = GameDataManager::GetInstance().GetGameScore();
	m_questionNum = GameDataManager::GetInstance().GetQuestionNum();
	m_attackTime = GameDataManager::GetInstance().GetGameTime();
}

SceneResult::~SceneResult()
{
}

void SceneResult::Update(const InputState& input)
{
	m_pStage->Update();

	//�X�V�����̃����o�֐��|�C���^
	(this->*m_updateFunc)(input);
}

void SceneResult::Draw()
{
	m_pStage->Draw();
	// ��萔�`��
	std::string drawText = std::to_string(m_questionNum) + "�⒆ : " + std::to_string(m_scoreNum) + "�␳���I";
	int textLength = GetDrawFormatStringWidth(drawText.c_str());
	DrawFormatStringF(static_cast<float>(Game::kScreenWidthHalf - (textLength / 2)), kResultPosY,
		0xffffff, "%s", drawText.c_str());

	if (GameDataManager::GetInstance().GetGameMode() != GameMode::TIMELIMIT)
	{
		// �^�C���`��
		std::string drawTime = "���Ȃ���" + std::to_string(m_attackTime / 60) + "�b�ŉ����܂����B";
		int timeLength = GetDrawFormatStringWidth(drawTime.c_str());
		DrawFormatStringF(static_cast<float>(Game::kScreenWidthHalf - (timeLength / 2)), kResultPosY + Game::kFontSize,
			0xffffff, "%s", drawTime.c_str());
	}
	DrawMenuText();
}

void SceneResult::DrawMenuText()
{
	// �V�[�����`��
	float drawX = 0.0f, drawY = 0.0f;
	drawX = static_cast<float>(Game::kScreenWidthHalf - (GetDrawFormatStringWidth(m_gameModeText.c_str()) / 2));
	drawY = Game::kGameHeightHalf - 160.0f;
	DrawStringF(drawX, drawY, m_gameModeText.c_str(), 0xffffff);

	// �S�Ă̑I�����ڕ`��
	for (int i = 0; i <= kSelectItemNum; i++)
	{
		std::string tSelectedItemName;
		tSelectedItemName = GetCurrentText(i);
		drawX = static_cast<float>(Game::kScreenWidthHalf - (GetDrawFormatStringWidth(tSelectedItemName.c_str()) / 2));
		drawY = static_cast<float>(kTextDrawPosY) + (i * kTextDistance);
		DrawFormatStringF(drawX, drawY, Game::kColorGray, "%s", tSelectedItemName.c_str());
	}

	// �I���ς݂̍��ڕ`��
	m_selectedItemName = GetCurrentText(m_selectedPos);
	drawX = static_cast<float>(Game::kScreenWidthHalf - (GetDrawFormatStringWidth(m_selectedItemName.c_str()) / 2));
	drawY = static_cast<float>(kTextDrawPosY) + (m_selectedPos * kTextDistance);
	DrawFormatStringF(drawX, drawY - 2, Game::kColorWhite, "%s", m_selectedItemName.c_str());
}

std::string SceneResult::GetCurrentText(int n)
{
	std::string text;

	if (n == 0)
	{
		text = kTextRestart;
	}
	else if (n == 1)
	{
		text = kTextTitle;
	}

	return text;
}

void SceneResult::CursorUpdate(const InputState& input)
{
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
			m_selectedPos = i;
		}
	}
}

void SceneResult::SetGameModeName()
{
	if (GameDataManager::GetInstance().GetGameMode() == GameMode::QUESTIONLIMIT)
	{
		m_gameModeText = kTextQuestionLimit;
	}
	else if (GameDataManager::GetInstance().GetGameMode() == GameMode::TIMELIMIT)
	{
		m_gameModeText = kTextTimeLimit;
	}
	else if (GameDataManager::GetInstance().GetGameMode() == GameMode::ALLCHALLENGE)
	{
		m_gameModeText = kTextAllChallenge;
	}
}

void SceneResult::NormalUpdate(const InputState& input)
{
	CursorUpdate(input);

	if (input.IsTriggered(InputType::select))
	{
		SoundManager::GetInstance().PlaySE(SoundType::select);
		if (m_selectedPos == 0)
		{
			m_Manager.ChangeScene(new SceneMain(m_Manager));
		}
		else
		{
			m_Manager.ChangeScene(new SceneTitleMenu(m_Manager));
		}
	}
}
