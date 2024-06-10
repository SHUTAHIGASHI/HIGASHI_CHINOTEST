#include "UiHpBar.h"
#include "Game.h"
#include "Players.h"

namespace
{
	// ÉQÅ[ÉWÇÃç¿ïW
	constexpr int kGaugePosX = Game::kScreenWidthHalf;
	constexpr int kGaugePosY = 100;
	constexpr int kGaugeW = 100;
	constexpr int kGaugeH = 50;
	constexpr int kDrawPosDiff = 500;
}

UiHpBar::UiHpBar() :
	m_hBarImg(-1),
	m_drawX(0),
	m_drawY(0),
	m_drawW(0),
	m_drawH(0),
	m_currentHpRate(0.0f)
{
	m_hBarImg = LoadGraph("Data/ImageData/HpBarImg.png");
	Init();
}

UiHpBar::~UiHpBar()
{
	DeleteGraph(m_hBarImg);
}

void UiHpBar::Init()
{
	m_drawX = kGaugePosX - kDrawPosDiff;
	m_drawY = kGaugePosY;
}

void UiHpBar::Update()
{
	m_drawW = m_drawX + static_cast<int>(m_currentHpRate * 10);
	m_drawH = m_drawY + kGaugeH;
}

void UiHpBar::UpdateUIData(int hp)
{
	m_currentHpRate = (static_cast<float>(hp) / static_cast<float>(PlayerInfo::kHpMax)) * 100;
}

void UiHpBar::Draw()
{
	DrawBox(m_drawX, m_drawY, m_drawW, m_drawH, Game::kColorOrange, true);
	DrawRotaGraphF(kGaugePosX, kGaugePosY, 1, 0.0, m_hBarImg, true);
}
