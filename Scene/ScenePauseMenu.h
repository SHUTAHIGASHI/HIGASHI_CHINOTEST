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

private: // プライベート関数
    std::string GetCurrentText(int textNum);
    void DrawMenuText();
    // 項目選択時
    void CursorUpdate(const InputState& input);

private: // 変数
    // 毎フレームカウント
    int m_countFrame;
    // 選択中の項目
    int m_selectedPos;
    // 選択中の項目名
    std::string m_selectedItemName;
    // カーソル画像
    int m_hCursorImg; 
    // カーソルが枠内にあるかどうか
    bool m_isCursorRanged;
};
