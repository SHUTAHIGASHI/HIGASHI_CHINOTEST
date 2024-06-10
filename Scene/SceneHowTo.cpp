#include "SceneHowTo.h"
#include "SceneManager.h"

namespace
{
	const char* const kTextBack = "クリックで戻ります。";
}

SceneHowTo::SceneHowTo(SceneManager& manager):
	Scene(manager),
	m_countFrame(0),
	m_hImg(-1),
	m_pos()
{
	m_hImg = LoadGraph("Data/ImageData/HowTo.png");
}

SceneHowTo::~SceneHowTo()
{
	DeleteGraph(m_hImg);
}

void SceneHowTo::Update(const InputState& input)
{
	m_countFrame++;
	if (m_countFrame > 10000)
	{
		m_countFrame = 0;
	}

	if (input.IsTriggered(InputType::select))
	{
		m_Manager.PopScene();
	}
}

void SceneHowTo::Draw()
{
	DrawExtendGraphF(0.0f, 0.0f, Game::kScreenWidth, Game::kScreenHeight, m_hImg, true);
	float stringLength = static_cast<float>(GetDrawFormatStringWidth(kTextBack));
	if ((m_countFrame / 10) % 6 != 0)
	{
		DrawFormatStringF(Game::kScreenWidthHalf - (stringLength / 2), Game::kScreenHeight - 70, Game::kColorCyan, "%s", kTextBack);
	}
}
