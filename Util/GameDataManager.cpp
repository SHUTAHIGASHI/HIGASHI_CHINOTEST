#include "GameDataManager.h"

GameDataManager::~GameDataManager()
{
}

GameDataManager::GameDataManager():
	m_gameMode(GameMode::TIMELIMIT),
	m_gameScore(0),
	m_questionNum(0),
	m_attackTime(0)
{
}