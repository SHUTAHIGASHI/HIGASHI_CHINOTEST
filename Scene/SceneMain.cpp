#include "SceneMain.h"
#include "SceneManager.h"
#include "StageDirecting.h"
#include "Player.h"
#include "SubjectManager.h"
#include "GameDataManager.h"
#include "ScenePauseMenu.h"
#include "SceneResult.h"
#include "SceneModeSelect.h"
#include "SoundManager.h"

namespace
{
	// �c��b���`��ʒu
	constexpr float kTimeDrawPosX = Game::kScreenWidthHalf - 500.0f;
	constexpr float kTimeDrawPosY = Game::kScreenHeightHalf - 320.0f;
	// ���J�n�O�̃J�E���g�_�E��
	constexpr int kIdlingTime = 60 * 6;
	// ���I�����̃J�E���g�_�E��
	constexpr int kEndTime = 60 * 2;
	// ��萔�w�胂�[�h�̖�萔
	constexpr int kQuestionNum = 15;
	// ���Ԑ������[�h�̎�������
	constexpr int kGameTimeMax = 60 * 30;
	// �񓚌�̊Ԋu����
	constexpr int kAnsweredDelay = 60 * 2;
	// �����\���̈ʒu
	constexpr float kCorrectTextDrawPosX = Game::kScreenWidthHalf + 400.0f;
	constexpr float kCorrectTextDrawPosY = Game::kGameHeightHalf - 20.0f;
	// �`�悷��e�L�X�g
	const char* const kCorrectText = "�����I";
	const char* const kIncorrectText = "�s����";
	const char* const kStopText = "�����܂ŁI�I";
	// ���������`��ʒu
	constexpr float kSoughtTextDrawPosX = Game::kScreenWidthHalf;
	constexpr float kSoughtTextDrawPosY = Game::kGameHeightHalf + 300.0f;
	// ��������
	const char* const kSoughtText = "( �M�́M)";
}

SceneMain::SceneMain(SceneManager& manager):
	Scene(manager),
	m_updateFunc(&SceneMain::SceneStartUpdate),
	m_drawFunc(&SceneMain::SceneStartDraw),
	m_drawInfoFunc(&SceneMain::TimeLimitDraw),
	m_gameMode(GameMode::empty),
	m_correct(0),
	m_incorrect(0),
	m_IdlingTime(kIdlingTime),
	m_endTime(0),
	m_gameTime(0),
	m_attackTime(0),
	m_questionNum(0),
	m_answerNum(0),
	m_answeredNum(0),
	m_answeredDelay(0),
	m_isModeSelected(false),
	m_isAnswering(false),
	m_isDrawSought(false),
	m_isEnd(false),
	m_pStage(std::make_shared<StageDirecting>()),
	m_pSubjectManager(std::make_shared<SubjectManager>()),
	m_pPlayer(std::make_shared<Player>())
{
	// �v�f�}�l�[�W���[�ɃV�[�����C�����Z�b�g
	m_pSubjectManager->SetMain(this);
	// �v���C���[�ɃV�[�����C��/�v�f�}�l�[�W���[���Z�b�g
	m_pPlayer->SetMain(this);
	m_pPlayer->SetSubjectManager(m_pSubjectManager.get());
}
 
SceneMain::~SceneMain()
{
	// �Q�[���|�C���g�ۑ�
	//GameDataManager::GetInstance().SetGameScore(m_correct, m_questionNum);
}

void SceneMain::Update(const InputState& input)
{
	if (input.IsTriggered(InputType::pause))
	{
		m_Manager.PushScene(new ScenePauseMenu(m_Manager));
	}

	// �Q�[���I������
	CheckGameEnd();
	// �펞���s����X�V����
	AlwaysUpdate(input);

	// �X�V�����̃����o�֐��|�C���^
	(this->*m_updateFunc)(input);
}

void SceneMain::Draw()
{
	DrawFormatString(0, 0, 0xffffff, "%d", m_correct);

	m_pStage->Draw();
	(this->*m_drawFunc)();
}

void SceneMain::OnCorrect()
{
	m_correct++;
	m_correctText = kCorrectText;
	m_pStage->ChangeAnim("smile");
	SoundManager::GetInstance().PlaySE(SoundType::correct);
	OnResponse();
}

void SceneMain::OnIncorrect()
{
	m_incorrect++;
	m_correctText = kIncorrectText;
	m_pStage->ChangeAnim("sad");
	SoundManager::GetInstance().PlaySE(SoundType::incorrect);
	OnResponse();
}

void SceneMain::AlwaysUpdate(const InputState& input)
{
	m_pStage->Update();
	if (!m_isEnd)
	{
		m_pPlayer->Update(input);
	}
}

void SceneMain::InitGameMode()
{
	if (m_gameMode == GameMode::QUESTIONLIMIT)
	{
		m_questionNum = kQuestionNum;
		m_drawInfoFunc = &SceneMain::QuestionLimitDraw;
	}
	else if (m_gameMode == GameMode::TIMELIMIT)
	{
		m_gameTime = kGameTimeMax;
		m_drawInfoFunc = &SceneMain::TimeLimitDraw;
	}
	else if (m_gameMode == GameMode::ALLCHALLENGE)
	{
		m_questionNum = m_pSubjectManager->GetSubjectNum();
		m_drawInfoFunc = &SceneMain::AllChallengeDraw;
	}

	m_drawFunc = &SceneMain::IdlingDraw;
	m_updateFunc = &SceneMain::IdlingUpdate;

	SoundManager::GetInstance().PlaySE(SoundType::idle);
}

void SceneMain::OnAnswerIsSought()
{
	m_isDrawSought = true;
}

void SceneMain::OnResponse()
{
	m_answeredNum++;
	PlayerSoundSubType(m_pSubjectManager->GetSubjectType());
	m_answeredDelay = kAnsweredDelay;
	m_updateFunc = &SceneMain::AnsweredUpdate;
	m_isAnswering = false;
}

void SceneMain::OnChangeAnswering()
{
	if (m_isEnd)
	{
		return;
	}
	// ����������
	if (m_gameMode == GameMode::TIMELIMIT) m_questionNum++;
	m_answerNum++;
	m_updateFunc = &SceneMain::AnsweringUpdate;
	m_drawFunc = &SceneMain::NormalDraw;
	m_isAnswering = true;
	m_isDrawSought = false;
	// ����ύX
	m_pSubjectManager->OnSubChange();
	// �ӂ�
	SoundManager::GetInstance().PlaySE(SoundType::humu);
}

void SceneMain::OnGameEnd()
{
	m_endTime = kEndTime;
	m_isEnd = true;
	m_updateFunc = &SceneMain::SceneEndUpdate;
	m_drawFunc = &SceneMain::SceneEndDraw;
}

void SceneMain::CheckGameEnd()
{
	if (m_isEnd) return;

	if(m_gameMode == GameMode::TIMELIMIT)
	{
		if (m_gameTime <= 0)
		{
			OnGameEnd();
		}
	}
	else if (m_gameMode == GameMode::QUESTIONLIMIT || m_gameMode == GameMode::ALLCHALLENGE)
	{
		if (m_answeredNum >= m_questionNum)
		{
			OnGameEnd();
		}
	}
	else
	{
		return;
	}
}

void SceneMain::PlayerSoundSubType(SubjectType subType)
{
	if (subType == SubjectType::CHINO)
	{
		SoundManager::GetInstance().PlaySE(SoundType::chino);
	}
	else if (subType == SubjectType::MYU)
	{
		SoundManager::GetInstance().PlaySE(SoundType::myu);
	}
	else if (subType == SubjectType::NEFFY)
	{
		SoundManager::GetInstance().PlaySE(SoundType::neffy);
	}
	else if (subType == SubjectType::NINA)
	{
		SoundManager::GetInstance().PlaySE(SoundType::nina);
	}
	else if (subType == SubjectType::RARA)
	{
		SoundManager::GetInstance().PlaySE(SoundType::rara);
	}
	else if (subType == SubjectType::VITTE)
	{
		SoundManager::GetInstance().PlaySE(SoundType::vitte);
	}
	else if (subType == SubjectType::SOUGHT)
	{
		OnAnswerIsSought();
	}
}

void SceneMain::SceneStartUpdate(const InputState& input)
{
	if (!m_isModeSelected)
	{
		// ���[�h�I���V�[�����s
		m_Manager.PushScene(new SceneModeSelect(m_Manager));
		// ���[�h�I���ς݂ɂ���
		m_isModeSelected = true;
	}
	else
	{
		// �I�����ꂽ�Q�[�����[�h�擾
		m_gameMode = GameDataManager::GetInstance().GetGameMode();
		// ���[�h�I���ɉ�����������
		InitGameMode();
	}
}

void SceneMain::IdlingUpdate(const InputState& input)
{
	m_IdlingTime--;
	if (m_IdlingTime < 0)
	{
		m_IdlingTime = 0;
		OnChangeAnswering();
	}

	m_pStage->ChangeAnim("normal");
}

void SceneMain::AnsweringUpdate(const InputState& input)
{
	m_pStage->ChangeAnim("normalFinger");
	m_gameTime--;
	m_attackTime++;
}

void SceneMain::AnsweredUpdate(const InputState& input)
{
	m_answeredDelay--;

	if (m_answeredDelay < 0)
	{
		m_answeredDelay = 0;
		OnChangeAnswering();
	}
}

void SceneMain::SceneEndUpdate(const InputState& input)
{
	m_endTime--;
	if (m_endTime < 0)
	{
		GameDataManager::GetInstance().SetGameScore(m_correct, m_questionNum);
		GameDataManager::GetInstance().SetGameTime(m_attackTime);
		m_Manager.ChangeScene(new SceneResult(m_Manager));
	}
}

void SceneMain::SceneStartDraw()
{
}

void SceneMain::IdlingDraw()
{
	m_pPlayer->Draw();
	SetFontSize(75);
	// �c�莞�ԕ`��
	if (m_IdlingTime / 60 == 0)
	{
		std::string time = "�J�n�I";
		int textLength = GetDrawFormatStringWidth(time.c_str());
		DrawFormatStringF(static_cast<float>(Game::kScreenWidthHalf - (textLength / 2)), Game::kGameHeightHalf - 50.0f,
			0xffffff, "%s", time.c_str());
	}
	else
	{
		if (m_IdlingTime != kIdlingTime)
		{
			// �e�L�X�g�`��
			std::string timeText = "�Q�[���J�n�܂�";
			int textLength = GetDrawFormatStringWidth(timeText.c_str());
			DrawFormatStringF(static_cast<float>(Game::kScreenWidthHalf - (textLength / 2)), Game::kGameHeightHalf - 100.0f,
				0xffffff, "%s", timeText.c_str());
			// �^�C���`��
			std::string time = std::to_string(m_IdlingTime / 60) + " �b";
			textLength = GetDrawFormatStringWidth(time.c_str());
			DrawFormatStringF(static_cast<float>(Game::kScreenWidthHalf - (textLength / 2)), Game::kGameHeightHalf,
				0xffffff, "%s", time.c_str());
		}
	}
	SetFontSize(Game::kFontSize);
}

void SceneMain::NormalDraw()
{
	m_pSubjectManager->Draw();
	m_pPlayer->Draw();

	(this->*m_drawInfoFunc)();

	// �����`��
	if (m_answeredDelay > 0)
	{
		SetFontSize(60);
		int textLength = GetDrawFormatStringWidth(m_correctText.c_str());
		DrawFormatStringF(kCorrectTextDrawPosX - (textLength / 2), kCorrectTextDrawPosY,
			0xffffff, "%s", m_correctText.c_str());
		// ���������̕`��
		if (m_isDrawSought)
		{
			int soughtTextLength = GetDrawFormatStringWidth(kSoughtText);
			DrawFormatStringF(kSoughtTextDrawPosX - (soughtTextLength / 2), kSoughtTextDrawPosY,
				0xffffff, "%s", kSoughtText);
		}
		SetFontSize(Game::kFontSize);
	}
}

void SceneMain::SceneEndDraw()
{
	// �����܂ŕ`��
	SetFontSize(60);
	std::string drawText = kStopText;
	int textLength = GetDrawFormatStringWidth(drawText.c_str());
	DrawFormatStringF(static_cast<float>(Game::kScreenWidthHalf - (textLength / 2)), Game::kGameHeightHalf,
		0xffffff, "%s", drawText.c_str());
	SetFontSize(Game::kFontSize);
}

void SceneMain::QuestionLimitDraw()
{
	// �������`��
	SetFontSize(60);
	std::string score = std::to_string(m_questionNum) + "�⒆" + std::to_string(m_answerNum) + "���";
	int textLength = GetDrawFormatStringWidth(score.c_str());
	DrawFormatStringF(kTimeDrawPosX - (textLength / 2), kTimeDrawPosY,
		0xffffff, "%s", score.c_str());
	SetFontSize(Game::kFontSize);
}

void SceneMain::TimeLimitDraw()
{
	// �c�莞�ԕ`��
	SetFontSize(75);
	std::string time = "�c�� " + std::to_string(m_gameTime / 60) + " �b";
	int textLength = GetDrawFormatStringWidth(time.c_str());
	DrawFormatStringF(kTimeDrawPosX - (textLength / 2), kTimeDrawPosY,
		0xffffff, "%s", time.c_str());
	SetFontSize(Game::kFontSize);
}

void SceneMain::AllChallengeDraw()
{
	// �������`��
	SetFontSize(60);
	std::string score = std::to_string(m_questionNum) + "�⒆" + std::to_string(m_answerNum) + "���";
	int textLength = GetDrawFormatStringWidth(score.c_str());
	DrawFormatStringF(kTimeDrawPosX - (textLength / 2), kTimeDrawPosY,
		0xffffff, "%s", score.c_str());
	SetFontSize(Game::kFontSize);
}
