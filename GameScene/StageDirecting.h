#pragma once
#include <string>
#include <vector>
#include "Game.h"

enum class ChinoType
{
	normal,
	normalFinger,
	mouseFinger,
	smile,
	sad
};

class StageDirecting
{
public:
	// �R���X�g���N�^
	StageDirecting();
	// �f�X�g���N�^
	virtual ~StageDirecting();

	// �X�V
	void Update();
	// �`��
	void Draw();

	// �A�j���[�V�����ύX
	void ChangeAnim(std::string animName);

private:
	// �f�[�^�ǂݍ���
	void LoadData();
	// �A�j���[�V�����̍X�V
	void AnimUpdate();
	// �~�j�L�����̃A�j���[�V�����X�V
	void MiniCharaAnimUpdate();
	// �~�j�L�����������_���Z�b�g
	void SetRandMiniChara();

private:
	// ���t���[���J�E���g
	int m_countFrame;
	// �����w�i
	int m_hBackground;
	int m_hBackground2;
	// �X�e�[�W�w�i�C���X�g
	int m_hKokuban;
	// ���̐�摜
	int m_hChinoImg;
	// ���̐�̏�Ԃ̖��O
	std::string m_chinoAnimName;

	// ���̐�摜�̕`��͈�
	VECTOR m_chinoImgDrawPos;
	// �~�j�L�����摜
	std::vector<int> m_hMiniCharaImg;
	int m_hDrawMiniCharaImg;
	// �~�j�L�����摜�̕`��͈�
	VECTOR m_miniCharaDrawPos;
	// �~�j�L�����摜�̕`��͈�
	VECTOR m_miniCharaImgPos;
};

