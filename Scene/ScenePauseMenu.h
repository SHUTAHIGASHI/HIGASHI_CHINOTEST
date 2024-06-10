#pragma once
#include "Scene.h"
#include <memory>
#include <string>

class ScenePauseMenu :
    public Scene
{
public:
    ScenePauseMenu(SceneManager& manager);
    virtual ~ScenePauseMenu();

    void Update(const InputState& input);
    void Draw();

private: // �v���C�x�[�g�֐�
    std::string GetCurrentText(int textNum);
    void DrawMenuText();
    // ���ڑI����
    void CursorUpdate(const InputState& input);

private: // �ϐ�
    // ���t���[���J�E���g
    int m_countFrame;
    // �I�𒆂̍���
    int m_selectedPos;
    // �I�𒆂̍��ږ�
    std::string m_selectedItemName;
    // �J�[�\���摜
    int m_hCursorImg; 
    // �J�[�\�����g���ɂ��邩�ǂ���
    bool m_isCursorRanged;
};