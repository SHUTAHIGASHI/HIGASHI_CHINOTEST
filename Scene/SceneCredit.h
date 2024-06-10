#pragma once
#include "Scene.h"
#include "Game.h"
#include <memory>
#include <string>

class SceneCredit :
    public Scene
{
public:
    SceneCredit(SceneManager& manager);
    virtual ~SceneCredit();

    // 更新
    void Update(const InputState& input);
    // 描画
    void Draw();

private: // プライベート関数
    // テキスト描画
    void DrawMenuText();
private: // 変数
    // 背景描画座標
    VECTOR m_bgPos;
    // 毎フレームカウント
    int m_countFrame;
    // スクロールのフレーム待機
    int m_scrollWaitFrame;
    // 背景画像
    int m_hCreditImg;
    // 画像サイズ
    int m_ClearGraphX;
    int m_ClearGraphY;
    // スクロールするかどうか
    bool m_isCanScroll;
    // テキスト描画判定
    bool m_isScrollEnd;
};
