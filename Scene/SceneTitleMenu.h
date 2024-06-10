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

private: // プライベート関数
    // 文字列の更新
    std::string GetCurrentText(int textNum);
    void DrawMenuText();
    // 曲名ループ処理
    void MusicNameLoop();
    // 項目選択時
    void CursorUpdate(const InputState& input);
    // タイトル終了時処理
    void OnSceneEnd();

    using m_tUpdateFunc = void (SceneTitleMenu::*) (const InputState& input);
    m_tUpdateFunc m_updateFunc = nullptr;
    // タイトル画面更新処理
    void NormalUpdate(const InputState& input);

private: // シーン全体の管理変数
    // 毎フレームカウント用
    int m_countFrame;

private: // シーン装飾の管理変数
    // 曲名表示位置
    VECTOR m_musicNameDrawPos;    
    // 選択中の項目
    int m_selectedPos;
    // 選択中の項目名
    std::string m_selectedItemName;
    // カーソル画像
    int m_hCursorImg;
    // タイトルロゴ画像
    int m_hTitleLogo;
    // カーソル位置
    MousePos m_mousePos;
    // カーソルが枠内にあるかどうか
    bool m_isCursorRanged;
private:
    // 背景
    std::shared_ptr<StageDirecting> m_pStage;
};
