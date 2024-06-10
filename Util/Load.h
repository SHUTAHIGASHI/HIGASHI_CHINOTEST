#pragma once
#include <unordered_map>
#include <string>
#include "Subject.h"

class Load
{
public:
	~Load();
	/// <summary>
	/// SoundManager使用者はGetInstance()を通した参照からしか利用できない
	/// </summary>
	/// <returns></returns>
	static Load& GetInstance()
	{
		// 唯一の実態
		static Load instance;

		// それの参照を返す
		return instance;
	}

	/// <summary>
	/// 全てのデータをロードする
	/// </summary>
	void AllLoadData();

	/// <summary>
	/// 全てのデータを削除する
	/// </summary>
	void AllDeleteData();
	
	/// <summary>
	/// ハンドルを取得する
	/// </summary>
	/// <param name="key">ロードデータのキー</param>
	/// <returns>ハンドル</returns>
	int GetHandle(std::string key)
	{
		return m_data[key];
	}

	// 要素データ全て取得
	std::vector<SubjectData> GetAllData()
	{
		return m_subjects;
	}
private:
	//ロードデータをunordered_mapで管理
	std::unordered_map<std::string, int> m_data;

	std::vector<SubjectData> m_subjects;

	// シングルトンパターンなのでコンストラクタはprivateに置く
	Load() {};

	// コピーも代入も禁止する
	Load(const Load&) = delete;			// コピーコンストラクタ
	void operator = (const Load&) = delete;		// 代入も禁止
};

