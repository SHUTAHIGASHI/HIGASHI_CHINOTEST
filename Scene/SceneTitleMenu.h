#pragma once
#include "Scene.h"
#include <string>
#include <memory>
#include "Game.h"

class StageDirecting;

class SceneTitleMenu :
    public Scene
{
public:
    SceneTitleMenu(SceneManager& manager);
    virtual ~SceneTitleMenu();

    void Update(const InputState& input);
    void Draw();

private: // �v���C�x�[�g�֐�
    // ������̍X�V
    std::string GetCurrentText(int textNum);
    void DrawMenuText();
    // �Ȗ����[�v����
    void MusicNameLoop();
    // ���ڑI����
    void CursorUpdate(const InputState& input);
    // �^�C�g���I��������
    void OnSceneEnd();

    using m_tUpdateFunc = void (SceneTitleMenu::*) (const InputState& input);
    m_tUpdateFunc m_updateFunc = nullptr;
    // �^�C�g����ʍX�V����
    void NormalUpdate(const InputState& input);

private: // �V�[���S�̂̊Ǘ��ϐ�
    // ���t���[���J�E���g�p
    int m_countFrame;

private: // �V�[�������̊Ǘ��ϐ�
    // �Ȗ��\���ʒu
    VECTOR m_musicNameDrawPos;    
    // �I�𒆂̍���
    int m_selectedPos;
    // �I�𒆂̍��ږ�
    std::string m_selectedItemName;
    // �J�[�\���摜
    int m_hCursorImg;
    // �^�C�g�����S�摜
    int m_hTitleLogo;
    // �J�[�\���ʒu
    MousePos m_mousePos;
    // �J�[�\�����g���ɂ��邩�ǂ���
    bool m_isCursorRanged;
private:
    // �w�i
    std::shared_ptr<StageDirecting> m_pStage;
};
