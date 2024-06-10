#pragma once
#include "Scene.h"
#include <string>

enum class GameMode;

class SceneModeSelect :
    public Scene
{
public:
    SceneModeSelect(SceneManager& manager);
    virtual ~SceneModeSelect();

    void Update(const InputState& input);
    void Draw();

private:
    std::string GetCurrentText(int textNum);
    void DrawMenuText();
    // ���ڑI����
    void CursorUpdate(const InputState& input);
private:
    // ���t���[���J�E���g
    int m_countFrame;
    // �I�������Q�[�����[�h
    GameMode m_gameMode;
    // �I���ς݂̍���
    std::string m_selectedItemName;
    int m_selectedPos;
    // �J�[�\���摜
    int m_hCursorImg;
    // �J�[�\�����g���ɂ��邩�ǂ���
    bool m_isCursorRanged;
};

