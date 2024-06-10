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
	// テキスト描画
	void DrawMenuText();
	// 指定したテキストを返す
	std::string GetCurrentText(int n);
	// 項目選択時
	void CursorUpdate(const InputState& input);
	// ゲームモード名設定
	void SetGameModeName();

	// メンバ関数ポインタ(更新)
	using m_tUpdateFunc = void (SceneResult::*) (const InputState& input);
	m_tUpdateFunc m_updateFunc = nullptr;
	void NormalUpdate(const InputState& input);

private:
	// 描画するゲームモードテキスト
	std::string m_gameModeText;
	// 描画するスコア
	int m_scoreNum;
	int m_questionNum;
	int m_attackTime;
	// ゲームオーバーウィンドウの描画座標
	float m_windowDrawPosX;
	float m_windowDrawPosY;
	// 選択中の項目
	int m_selectedPos;
	// 選択中の項目名
	std::string m_selectedItemName;
	// カーソルが枠内にあるかどうか
	bool m_isCursorRanged;
	// 教室背景描画
	std::shared_ptr<StageDirecting> m_pStage;
};

