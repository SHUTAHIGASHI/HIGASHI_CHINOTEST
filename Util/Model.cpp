#include "Model.h"

Model::Model():
	m_hModel(-1),
	m_AnimNo(-1),
	m_AnimIndex(0),
	m_AnimTotalTime(0.0f),
	m_AnimPlayTime(0.0f),
	m_pos(VGet(0.0f, 0.0f, 0.0f)),
	m_rotation(VGet(0.0f, 0.0f, 0.0f))
{
}

Model::~Model()
{
	// モデルハンドル削除
	MV1DeleteModel(m_hModel);
}

void Model::Init(int hModel)
{
	// モデルハンドル代入
	m_hModel = hModel;
}

void Model::Update()
{
	// 再生時間を進める
	m_AnimPlayTime += 1.0f;

	// 再生時間がアニメーションの総再生時間に達したら再生時間を０に戻す
	if (m_AnimPlayTime > m_AnimTotalTime)
	{
		m_AnimPlayTime = 0.0f;
	}

	// 再生時間をセットする
	MV1SetAttachAnimTime(m_hModel, m_AnimIndex, m_AnimPlayTime);
}

void Model::Draw()
{
	// モデル描画
	MV1DrawModel(m_hModel);
}

void Model::SetPosition(VECTOR pos)
{
	// 座標設定
	m_pos = pos;
	MV1SetPosition(m_hModel, m_pos);
}

void Model::SetScale(float size)
{
	// 拡大率設定
	MV1SetScale(m_hModel, VGet(size, size, size));
}

void Model::SetMotionType(int motionType)
{
	// 実行するモーション設定
	if (m_AnimNo == motionType) return;
	m_AnimNo = motionType;
	m_AnimIndex = MV1AttachAnim(m_hModel, motionType, -1);
	m_AnimTotalTime = MV1GetAttachAnimTotalTime(m_hModel, m_AnimIndex);
	m_AnimPlayTime = 0.0f;
}

void Model::SetDirection(VECTOR lookPos, float rota)
{
	// 方向設定
	lookPos.y -= 500.0f;
	MV1SetRotationZYAxis(m_hModel, VGet(0.0f, 0.0f, 1.0f), VSub(m_pos, lookPos), rota);
}

void Model::SetRotation(VECTOR rota)
{
	// 回転方向設定
	m_rotation = rota;
	MV1SetRotationXYZ(m_hModel, m_rotation);
}
