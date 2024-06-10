#include "UiManager.h"
#include "SceneMain.h"
#include "UiStatus.h"
#include "UiHpBar.h"
#include "UiGetPoint.h"
#include "UiLostPoint.h"
#include "Player.h"
#include "GameScore.h"

namespace
{
	constexpr int kUISpaceNum = 125;
}

UiManager::UiManager():
	m_hUltraImg(-1),
	m_hSuperImg(-1),
	m_hHyperImg(-1),
	m_PointUI(nullptr),
	m_HpBar(nullptr),
	m_StatusUI(nullptr),
	m_Player(nullptr),
	m_Score(nullptr)
{
}

UiManager::~UiManager()
{
	DeleteGraph(m_hUltraImg);
	DeleteGraph(m_hSuperImg);
	DeleteGraph(m_hHyperImg);

	delete m_HpBar;
	delete m_StatusUI;
}

void UiManager::Init()
{
	// データのロード
	LoadData();
	// UI生成
	CreateUI();
}

void UiManager::Update()
{	
	UIinfoUpdate();

	if (m_PointUI != nullptr) m_PointUI->Update();
	m_HpBar->Update();

	DeleteUI();
}

void UiManager::Draw()
{
	if (m_PointUI != nullptr) m_PointUI->Draw();
	m_HpBar->Draw();
	m_StatusUI->Draw();
}

void UiManager::DeleteUI()
{
	// 処理が一通り終わったら削除
	if (m_PointUI != nullptr)
	{
		if (m_PointUI->IsDelete())
		{
			delete m_PointUI;
			m_PointUI = nullptr;
		}
	}
}

void UiManager::OnBoost(BoostLevel type)
{
	int tHandle = GetHandle(type);
	//m_OnBoostUI.push_back(std::make_shared<UiBoost>(tHandle));
}

void UiManager::OnPointGet()
{
	if (m_PointUI != nullptr)
	{
		delete m_PointUI;
	}

	m_PointUI = new UiGetPoint(m_Score->GetNextPoint());
}

void UiManager::OnPointLost()
{
	if (m_PointUI != nullptr)
	{
		delete m_PointUI;
	}

	m_PointUI = new UiLostPoint(m_Score->GetNextLostPoint());
}

void UiManager::CreateUI()
{
	m_HpBar = new UiHpBar();
	m_StatusUI = new UiStatus();
}

void UiManager::LoadData()
{
	m_hUltraImg = LoadGraph("Data/ImageData/ULTRAtext.png");
	m_hSuperImg = LoadGraph("Data/ImageData/SUPERtext.png");
	m_hHyperImg = LoadGraph("Data/ImageData/HYPERtext.png");
}

void UiManager::UIinfoUpdate()
{
	m_HpBar->UpdateUIData(m_Player->GetPlayerHP());
	m_StatusUI->UpdateUiData(static_cast<int>(m_Player->GetBoostLevel()), m_Score->GetGamePoint());
}

int UiManager::GetHandle(BoostLevel type)
{
	int tHandle = -1;

	if (type == BoostLevel::Level1)
	{
		tHandle = m_hUltraImg;
	}
	else if (type == BoostLevel::Level2)
	{
		tHandle = m_hSuperImg;
	}
	else if (type == BoostLevel::Level3)
	{
		tHandle = m_hHyperImg;
	}

	return tHandle;
}
