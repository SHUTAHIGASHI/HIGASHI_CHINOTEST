#include "SceneTitleMenu.h"
#include "StageDirecting.h"
#include "SceneManager.h"
#include "SceneMain.h"
#include "SceneOption.h"
#include "SceneHowTo.h"
#include "SceneCredit.h"
#include "SceneModeSelect.h"

namespace
{
	// ���t���[���`��ʒu
	constexpr float kFramePosX = Game::kScreenWidthHalf;
	constexpr float kFramePosY = Game::kScreenHeightHalf - 100.0f;
	// ���摜�̍��E�T�C�Y
	constexpr float kFrameSizeX = 650.0f;
	constexpr float kFrameSizeY = 350.0f;
	// �����̖��O�摜�̕`��ʒu
	constexpr float kShiftNameSizeX = Game::kScreenWidthHalf + 500.0f;
	constexpr float kShiftNameSizeY = Game::kScreenHeightHalf - 50.0f;

	// �^�C�g�����S�`��ʒu
	constexpr float kLogoDrawPosX = Game::kScreenWidthHalf;
	constexpr float kLogoDrawPosY = 220.0f;
	// �e�L�X�g�`��ʒu
	constexpr float kTextDrawPosY = Game::kScreenHeightHalf + 200.0f;
	constexpr float kTextDrawSpace = Game::kFontSize + 10;
	// �Ȗ��ړ����x
	constexpr float kMusicNameMoveSpeed = 2.0f;
	// �I���\���ڂ̐�
	constexpr int kSelectItemNum = 5 - 1;
	// �e�L�X�g
	const char* const kTextStart = "�Q�[���X�^�[�g";
	const char* const kTextHowto = "�����т���";
	const char* const kTextSetting = "�ݒ�";
	const char* const kTextCredit = "�N���W�b�g";
	const char* const kTextGameEnd = "�I��";
	const char* const kTextMusicName = "��.�u I.C.E �v- ���O�͖��������ł��B";
}

SceneTitleMenu::SceneTitleMenu(SceneManager& manager) : Scene(manager),
m_updateFunc(&SceneTitleMenu::NormalUpdate),
m_countFrame(0),
m_musicNameDrawPos(),
m_selectedPos(0),
m_selectedItemName(),
m_hCursorImg(-1),
m_hTitleLogo(-1),
m_mousePos(),
m_isCursorRanged(false),
m_pStage(std::make_shared<StageDirecting>())
{
	m_musicNameDrawPos = VGet(Game::kScreenWidth, Game::kScreenHeight - 60.0f, 0.0f);
	m_hCursorImg = LoadGraph("Data/ImageData/chalk.png");
	m_hTitleLogo = LoadGraph("Data/ImageData/GAME_TITLE.png");
}

SceneTitleMenu::~SceneTitleMenu()
{
	DeleteGraph(m_hCursorImg);
	DeleteGraph(m_hTitleLogo);
}

void SceneTitleMenu::Update(const InputState& input)
{
	m_countFrame++;

	m_mousePos = input.GetMousePos();

	m_pStage->Update();
	MusicNameLoop();

	(this->*m_updateFunc)(input);
}

void SceneTitleMenu::Draw()
{
	// �X�e�[�W�w�i�`��
	m_pStage->Draw();
	// �^�C�g�����S�`��
	DrawRotaGraphF(static_cast<float>(Game::kScreenWidthHalf), Game::kGameHeightHalf, 1.0, 0.0, m_hTitleLogo, true);

	// �e�L�X�g�`��
	DrawMenuText();
	// �Ȗ��`��
	SetFontSize(32);
	DrawFormatStringF(m_musicNameDrawPos.x, m_musicNameDrawPos.y, Game::kColorWhite, "%s", kTextMusicName);
	SetFontSize(Game::kFontSize);
}

std::string SceneTitleMenu::GetCurrentText(int textNum)
{
	std::string text;

	if (textNum == 0)
	{
		text = kTextStart;
	}
	else if (textNum == 1)
	{
		text = kTextHowto;
	}
	else if (textNum == 2)
	{
		text = kTextSetting;
	}
	else if (textNum == 3)
	{
		text = kTextCredit;
	}
	else if (textNum == 4)
	{
		text = kTextGameEnd;
	}

	return text;
}

void SceneTitleMenu::DrawMenuText()
{
	int drawX = 0, drawY = static_cast<int>(Game::kScreenHeightHalf);
	std::string tText;
	for (int i = 0; i <= kSelectItemNum; i++)
	{
		tText = GetCurrentText(i);
		drawX = static_cast<int>(Game::kScreenWidthHalf - (GetDrawFormatStringWidth(tText.c_str()) / 2));
		drawY = static_cast<int>(kTextDrawPosY + (kTextDrawSpace * i));
		DrawFormatString(drawX, drawY, Game::kColorGray, "%s", tText.c_str());
	}

	m_selectedItemName = GetCurrentText(m_selectedPos);
	int textLength = GetDrawFormatStringWidth(m_selectedItemName.c_str());
	drawX = static_cast<int>(Game::kScreenWidthHalf - (textLength / 2));
	drawY = static_cast<int>(kTextDrawPosY + (kTextDrawSpace * m_selectedPos));
	DrawFormatString(drawX, drawY - 2, Game::kColorWhite, "%s", m_selectedItemName.c_str());

	if ((m_countFrame / 10) % 6 != 0)
	{
		DrawRotaGraph(drawX - Game::kFontSize, drawY + 25, 0.2, 0.0, m_hCursorImg, true);
		DrawRotaGraph(drawX + textLength + Game::kFontSize, drawY + 25, 0.2, 0.0, m_hCursorImg, true);
	}
}

void SceneTitleMenu::MusicNameLoop()
{
	m_musicNameDrawPos.x -= kMusicNameMoveSpeed;

	int textLength = GetDrawFormatStringWidth(kTextMusicName);
	if (m_musicNameDrawPos.x + textLength < 0)
	{
		m_musicNameDrawPos.x = Game::kScreenWidth;
	}
}

void SceneTitleMenu::CursorUpdate(const InputState& input)
{
	m_isCursorRanged = false;

	int buttonPosX = 0, buttonPosY = Game::kScreenHeightHalf;
	std::string tText;
	for (int i = 0; i <= kSelectItemNum; i++)
	{
		tText = GetCurrentText(i);
		int textLength = GetDrawFormatStringWidth(tText.c_str());
		buttonPosX = static_cast<int>(Game::kScreenWidthHalf - (textLength / 2));
		buttonPosY = static_cast<int>(kTextDrawPosY + (kTextDrawSpace * i));

		if (input.GetMousePos().x > buttonPosX && input.GetMousePos().x < buttonPosX + textLength
			&& input.GetMousePos().y > buttonPosY && input.GetMousePos().y < buttonPosY + Game::kFontSize)
		{
			m_isCursorRanged = true;
			m_selectedPos = i;
		}
	}
}

void SceneTitleMenu::OnSceneEnd()
{
	if (m_selectedPos == 0)
	{
		m_Manager.ChangeScene(new SceneMain(m_Manager));
	}
	else if (m_selectedPos == 1)
	{
		m_Manager.PushScene(new SceneHowTo(m_Manager));
	}
	else if (m_selectedPos == 2)
	{
		m_Manager.PushScene(new SceneOption(m_Manager));
	}
	else if (m_selectedPos == 3)
	{
		m_Manager.PushScene(new SceneCredit(m_Manager));
	}
	else if (m_selectedPos == 4)
	{
		m_Manager.GameEnd();
	}
	return;
}

void SceneTitleMenu::NormalUpdate(const InputState& input)
{
	CursorUpdate(input);

	if (input.IsTriggered(InputType::select) && m_isCursorRanged)
	{
		SoundManager::GetInstance().PlaySE(SoundType::select);
		OnSceneEnd();
		return;
	}

	m_musicNameDrawPos.x -= 3.0f;
	float textLength = static_cast<float>(GetDrawFormatStringWidth(kTextMusicName));
	if ((m_musicNameDrawPos.x + textLength) < 0.0f)
	{
		m_musicNameDrawPos.x = Game::kScreenWidth;
	}
}
