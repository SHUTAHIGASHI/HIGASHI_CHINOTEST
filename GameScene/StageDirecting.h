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
	// コンストラクタ
	StageDirecting();
	// デストラクタ
	virtual ~StageDirecting();

	// 更新
	void Update();
	// 描画
	void Draw();

	// アニメーション変更
	void ChangeAnim(std::string animName);

private:
	// データ読み込み
	void LoadData();
	// アニメーションの更新
	void AnimUpdate();
	// ミニキャラのアニメーション更新
	void MiniCharaAnimUpdate();
	// ミニキャラをランダムセット
	void SetRandMiniChara();

private:
	// 毎フレームカウント
	int m_countFrame;
	// 教室背景
	int m_hBackground;
	int m_hBackground2;
	// ステージ背景イラスト
	int m_hKokuban;
	// ちの先画像
	int m_hChinoImg;
	// ちの先の状態の名前
	std::string m_chinoAnimName;

	// ちの先画像の描画範囲
	VECTOR m_chinoImgDrawPos;
	// ミニキャラ画像
	std::vector<int> m_hMiniCharaImg;
	int m_hDrawMiniCharaImg;
	// ミニキャラ画像の描画範囲
	VECTOR m_miniCharaDrawPos;
	// ミニキャラ画像の描画範囲
	VECTOR m_miniCharaImgPos;
};

