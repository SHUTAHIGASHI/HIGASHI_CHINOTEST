#pragma once
#include "Scene.h"
#include <string>
#include <memory>
#include "Game.h"

class StageDirecting;

class SceneResult :
	public Scene
{
public:
	SceneResult(SceneManager& manager);
	virtual ~SceneResult();

	void Update(const InputState& input);
	void Draw();

private:
	// �e�L�X�g�`��
	void DrawMenuText();
	// �w�肵���e�L�X�g��Ԃ�
	std::string GetCurrentText(int n);
	// ���ڑI����
	void CursorUpdate(const InputState& input);
	// �Q�[�����[�h���ݒ�
	void SetGameModeName();

	// �����o�֐��|�C���^(�X�V)
	using m_tUpdateFunc = void (SceneResult::*) (const InputState& input);
	m_tUpdateFunc m_updateFunc = nullptr;
	void NormalUpdate(const InputState& input);

private:
	// �`�悷��Q�[�����[�h�e�L�X�g
	std::string m_gameModeText;
	// �`�悷��X�R�A
	int m_scoreNum;
	int m_questionNum;
	int m_attackTime;
	// �Q�[���I�[�o�[�E�B���h�E�̕`����W
	float m_windowDrawPosX;
	float m_windowDrawPosY;
	// �I�𒆂̍���
	int m_selectedPos;
	// �I�𒆂̍��ږ�
	std::string m_selectedItemName;
	// �J�[�\�����g���ɂ��邩�ǂ���
	bool m_isCursorRanged;
	// �����w�i�`��
	std::shared_ptr<StageDirecting> m_pStage;
};

