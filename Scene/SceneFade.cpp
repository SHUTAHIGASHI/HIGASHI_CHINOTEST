#include "SceneFade.h"
#include "SceneManager.h"

namespace
{
	// 画像拡大率
	constexpr double kGraphScaleMin = 0.2;
	constexpr double kGraphScaleMax = 3.5;
	constexpr double kGraphScaleNum = 0.1;
}

SceneFade::SceneFade(SceneManager& manager):
	Scene(manager),
	m_updateFunc(&SceneFade::CloseUpdate),
	m_isFadeClose(false),
	m_isFadeOpen(false),
	m_hFadeImg(-1),
	m_imgScale(kGraphScaleMin)
{
	// フェード処理用画像
	m_hFadeImg = LoadGraph("Data/ImageData/Manju_Chino.png");
	GetGraphSize(m_hFadeImg, &m_graphSizeX, &m_graphSizeY);
}

SceneFade::~SceneFade()
{
	DeleteGraph(m_hFadeImg);
}

void SceneFade::Update(const InputState& input)
{
	(this->*m_updateFunc)();
}

void SceneFade::Draw()
{
	// フェード処理
	DrawRotaGraph(Game::kScreenWidthHalf, Game::kScreenHeightHalf, m_imgScale, 0.0, m_hFadeImg, true);
}

void SceneFade::CloseUpdate()
{
	m_imgScale += kGraphScaleNum;

	if (m_imgScale > kGraphScaleMax)
	{
		m_imgScale = kGraphScaleMax;
		m_isFadeClose = true;
		m_updateFunc = &SceneFade::OpenUpdate;
	}
}

void SceneFade::OpenUpdate()
{
	m_imgScale -= kGraphScaleNum;

	if (m_imgScale < kGraphScaleMin)
	{
		m_imgScale = kGraphScaleMin;
		m_isFadeOpen = true;
	}
}
