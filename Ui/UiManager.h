#pragma once
#include "Game.h"
#include <memory>
#include <vector>
#include "Players.h"

class SceneMain;
class UiPointBase;
class UiGetPoint;
class UiHpBar;
class UiStatus;
class Player;
class GameScore;

class UiManager
{
public:
	// コンストラクタ
	UiManager();
	// デストラクタ
	virtual ~UiManager();

	void SetPlayer(Player* player) { m_Player = player; }
	void SetScore(GameScore* score) { m_Score = score; }

	// 初期化
	void Init();
	// 更新
	void Update();
	// 描画
	void Draw();
	// 不要なUI削除処理
	void DeleteUI();
	// 加速時の処理
	void OnBoost(BoostLevel type);
	// ポイント獲得時の処理
	void OnPointGet();
	// ポイント喪失時の処理
	void OnPointLost();
private:
	// 常設UIの生成
	void CreateUI();
	// データのロード
	void LoadData();
	// 表示する情報の同期
	void UIinfoUpdate();
	// 現在のレベルから対応する画像ハンドルの取得
	int GetHandle(BoostLevel type);

private:
	// 画像ハンドル
	int m_hUltraImg;
	int m_hSuperImg;
	int m_hHyperImg;

private:
	// ブースト時にレベルを一時的に描画する
	//todo ブーストUI削除
	
	// 獲得したポイントを一時的に描画する
	UiPointBase* m_PointUI;
	// 常設Ui
	UiHpBar* m_HpBar;
	UiStatus* m_StatusUI;

	// プレイヤー
	Player* m_Player;
	// ゲームスコア
	GameScore* m_Score;
};

