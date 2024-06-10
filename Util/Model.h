#pragma once
#include "Game.h"

class Model
{
public:
	// コンストラクタ
	Model();
	// デストラクタ
	virtual ~Model();

	// 初期化
	void Init(int hModel);
	// 更新(アニメーション使用時のみ)
	void Update();
	// 描画
	void Draw();

	/* setter */
	void SetPosition(VECTOR pos);		// 座標
	void SetScale(float size);			// 拡大
	void SetMotionType(int);			// モーションタイプ
	void SetDirection(VECTOR lookPos, float rota);	// 向き
	void SetRotation(VECTOR);			// 回転

private:
	// モデルハンドル
	int m_hModel;

	// アニメーション
	int m_AnimNo;
	int m_AnimIndex;
	float m_AnimTotalTime;
	float m_AnimPlayTime;

	// 表示位置座標
	VECTOR m_pos;
	// 回転
	VECTOR m_rotation;
};

