#pragma once
#include <unordered_map>
#include <string>

enum class GameMode
{
	empty,
	QUESTIONLIMIT,
	TIMELIMIT,
	ALLCHALLENGE
};

/// <summary>
/// SEの管理を行うシングルトンクラス
/// </summary>
class GameDataManager
{
public:
	~GameDataManager();
	/// <summary>
	/// SoundManager使用者はGetInstance()を通した参照からしか利用できない
	/// </summary>
	/// <returns></returns>
	static GameDataManager& GetInstance()
	{
		// 唯一の実態
		static GameDataManager instance;
		// それの参照を返す
		return instance;
	}

	void SetGameMode(GameMode mode) { m_gameMode = mode; }
	void SetGameScore(int score, int qNum) { m_gameScore = score , m_questionNum = qNum; }
	void SetGameTime(int time) { m_attackTime = time; }

	GameMode GetGameMode() { return m_gameMode; }
	int GetGameScore() { return m_gameScore; }
	int GetQuestionNum() { return m_questionNum; }
	int GetGameTime() { return m_attackTime; }
private:
	// シングルトンパターンなのでコンストラクタはprivateに置く
	GameDataManager();
	// コピーも代入も禁止する
	GameDataManager(const GameDataManager&) = delete;			// コピーコンストラクタ
	void operator = (const GameDataManager&) = delete;		// 代入も禁止

private:
	// ゲームモード
	GameMode m_gameMode;
	// スコア
	int m_gameScore;
	// 問題数
	int m_questionNum;
	// ゲーム時間
	int m_attackTime;
};