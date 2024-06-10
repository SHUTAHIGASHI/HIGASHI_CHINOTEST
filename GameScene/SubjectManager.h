#pragma once
#include <vector>
#include "Subject.h"

class SceneMain;

struct SubjectData;

class SubjectManager
{
public:
	// コンストラクタ
	SubjectManager();
	// デストラクタ
	virtual ~SubjectManager();

	// シーンメインのポインタセット
	void SetMain(SceneMain* main) { m_pMain = main; }

	// 描画
	void Draw();
	// 要素の変更
	void OnSubChange();
	// ちの先が選択されたとき
	void OnChino();
	// ちの先じゃないが選択されたとき
	void OnNotChino();
	// 操桃が選択されたとき
	void OnSought();

	// 全要素数を取得
	int GetSubjectNum();
	// 要素種類を取得
	SubjectType GetSubjectType() { return m_currentSubjectData->subType; }
private:
	// 全ての要素の読み込み
	void LoadAllSubject();
	// ランダムで要素を取得
	SubjectData* GetRandSubject();
	// 全ての要素の状態リセット
	void AllSubjectReset();

private:
	// 現在の要素データ
	SubjectData* m_currentSubjectData;
	// 全ての要素データ
	std::vector<SubjectData> m_subjects;

private:
	// シーンメインのポインタ
	SceneMain* m_pMain;
};
