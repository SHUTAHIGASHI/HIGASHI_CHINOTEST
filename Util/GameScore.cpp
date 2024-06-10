#include "GameScore.h"

namespace
{
	// ポイント数値
	constexpr int kPointNum = 100;
	constexpr int kPointDiffNum = 50;
	// ポイント最大値
	constexpr int kScorePointMax = 999999;
}

GameScore::GameScore():
	m_gamePoint(0),
	m_nextGamePoint(kPointNum)
{
}

GameScore::~GameScore()
{
}

void GameScore::AddPoint()
{
	m_gamePoint += m_nextGamePoint;
	if (m_gamePoint > kScorePointMax)
	{
		m_gamePoint = kScorePointMax;
	}
}

void GameScore::SubPoint()
{
	m_gamePoint -= (m_nextGamePoint / 2);
	if (m_gamePoint < 0)
	{
		m_gamePoint = 0;
	}
}

void GameScore::OnChangeBoostLevel(BoostLevel level)
{
	m_nextGamePoint = kPointNum + (kPointDiffNum * static_cast<int>(level));
}
