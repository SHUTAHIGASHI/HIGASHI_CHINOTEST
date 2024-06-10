#pragma once
#include "Game.h"

class SceneMain;
class SubjectManager;

class Player
{
public:
	// コンストラクタ
	Player();
	// デストラクタ
	virtual ~Player();
	// シーンメインのセット
	void SetMain(SceneMain* main) { m_pMain = main; }
	// 要素マネージャーのセット
	void SetSubjectManager(SubjectManager* subManager) { m_pSubjectManager = subManager; }

	// 更新
	void Update(const InputState& input);
	// 描画
	void Draw();

private:
	// ボタン位置設定
	void SetButtonPos();
	// ボタンの範囲チェック
	bool ButtonRangeCheck(float posX, float posY);
	// ボタンサイズリセット
	void AllButtonSizeReset();
	// 選択時の処理
	void CorsorUpdate(const InputState& input);

private:
	// ボタンサイズ
	double m_chinoButtonSize;
	double m_notChinoButtonSize;
	double m_soughtButtonSize;

	// 各ボタンの画像ハンドル
	int m_hChinoButton;
	int m_hNotChinoButton;
	int m_hSoughtButton;

	// ボタン位置
	VECTOR m_ChinoButtonPos;
	VECTOR m_NotChinoButtonPos;
	VECTOR m_SoughtButtonPos;

	// カーソル位置
	MousePos m_mousePos;

private:
	SceneMain* m_pMain;
	SubjectManager* m_pSubjectManager;
};