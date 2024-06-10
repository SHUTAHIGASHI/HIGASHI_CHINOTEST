#pragma once
#include "Scene.h"
#include <memory>
#include "GameDataManager.h"
#include "Subject.h"

class StageDirecting;
class Player;
class SubjectManager;

enum class SubjectType;

class SceneMain :
    public Scene
{
public:
    // �R���X�g���N�^
    SceneMain(SceneManager& manager);
    // �f�X�g���N�^
    virtual ~SceneMain();

    // �X�V����
    void Update(const InputState& input);
    // �`�揈��
    void Draw();

    // ��萳���̏���
    void OnCorrect();
    // ���s�����̏���
    void OnIncorrect();

    // �񓚒����ǂ����擾
    bool IsAnswering() { return m_isAnswering; }

private:
    // �펞���s����X�V����
    void AlwaysUpdate(const InputState& input);
    // �Q�[�����[�h�ɉ�����������
    void InitGameMode();
    // �𓚂������̂Ƃ�
    void OnAnswerIsSought();
    // �񓚌�̏���
    void OnResponse();
    // �񓚒��̏����ֈڍs
    void OnChangeAnswering();
    // �Q�[���I�����̏���
    void OnGameEnd();
    // �Q�[���I������
    void CheckGameEnd();
    // ��ނɑΉ������T�E���h���Đ�
    void PlayerSoundSubType(SubjectType subType);

    // �����o�֐��|�C���^(�X�V)
    using m_tUpdateFunc = void (SceneMain::*) (const InputState& input);
    m_tUpdateFunc m_updateFunc = nullptr;
    void SceneStartUpdate(const InputState& input); // �V�[���J�n���̏���
    void IdlingUpdate(const InputState& input);     // �ҋ@���̍X�V����
    void AnsweringUpdate(const InputState& input);  // �񓚒��̍X�V����
    void AnsweredUpdate(const InputState& input);   // �񓚌�̍X�V����
    void SceneEndUpdate(const InputState& input);   // �V�[���I�����̏���

    // �����o�֐��|�C���^(�`��)
    using m_tDrawFunc = void (SceneMain::*) ();
    m_tDrawFunc m_drawFunc = nullptr;
    void SceneStartDraw();
    void IdlingDraw();
    void NormalDraw();
    void SceneEndDraw();

    // �����o�֐��|�C���^(�Q�[�����`��)
    using m_tDrawInfoFunc = void (SceneMain::*) ();
    m_tDrawInfoFunc m_drawInfoFunc = nullptr;
    void QuestionLimitDraw();
    void TimeLimitDraw();
    void AllChallengeDraw();

private:
    // �Q�[�����[�h
    GameMode m_gameMode;
    // �Q�[���|�C���g
    int m_correct;
    int m_incorrect;
    // ���J�n�O�̃J�E���g�_�E��
    int m_IdlingTime;
    // ���I�����̃J�E���g�_�E��
    int m_endTime;
    // ��������
    int m_gameTime;
    int m_attackTime;
    // ���v��萔
    int m_questionNum;
    // ��萔
    int m_answerNum;
    // �񓚍ς݂̖�萔
    int m_answeredNum;
    // �񓚌�̒x������
    int m_answeredDelay;
    // ���[�h�I��
    bool m_isModeSelected;
    // �񓚒����ǂ���
    bool m_isAnswering;
    // ������`�悷�邩�ǂ���
    bool m_isDrawSought;
    // �I�������ς݂��ǂ���
    bool m_isEnd;
    // �ҋ@���̐�������
    std::string m_correctText;

private:
    std::shared_ptr<StageDirecting> m_pStage;
    std::shared_ptr<SubjectManager> m_pSubjectManager;
    std::shared_ptr<Player> m_pPlayer;
};

