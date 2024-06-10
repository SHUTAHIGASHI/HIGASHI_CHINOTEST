#include "StageDirecting.h"

namespace
{
	// 黒板フレーム描画位置
	constexpr float kFramePosX = Game::kScreenWidthHalf;
	constexpr float kFramePosY = Game::kScreenHeightHalf - 100.0f;
	// 黒板画像の左右サイズ
	constexpr float kFrameSizeX = 650.0f;
	constexpr float kFrameSizeY = 350.0f;
	// ちのせん描画位置
	constexpr float kChinoPosX = static_cast<float>(Game::kScreenWidthHalf - 550.0f);
	constexpr float kChinoPosY = static_cast<float>(Game::kScreenHeightHalf + 200.0f);
	// ちのせんアニメーションサイズ
	constexpr float kChinoImgSizeY = Game::kChipSize * 2;
	// ちのせん拡大率
	constexpr double kChinosenScale = 0.65;
	// ちのせんアニメーションの更新フレーム数
	constexpr int kChinosenUpdateFrameNum = 30;

	// ミニキャラチップサイズ
	constexpr float kMiniCharaChipSize = 480.0f;
	constexpr float kMiniCharaDrawChipSize = 180.0f;
	// ミニキャラ移動速度
	constexpr float kMiniCharaMoveSpeed = 6.0f;
	// ミニキャラ描画位置
	constexpr float kMiniCharaDrawPosX = Game::kScreenWidth + kMiniCharaChipSize;
	constexpr float kMiniCharaDrawPosY = Game::kScreenHeight - 80.0f;
	// ミニキャラアニメーションの更新フレーム数
	constexpr int kMiniCharaUpdateFrameNum = 10;
}

StageDirecting::StageDirecting():
	m_hBackground(-1),
	m_hKokuban(-1),
	m_hChinoImg(-1),
	m_chinoAnimName("Normal"),
	m_chinoImgDrawPos(VGet(0.0f, 0.0f, 0.0f)),
	m_miniCharaDrawPos(VGet(kMiniCharaDrawPosX, kMiniCharaDrawPosY, 0.0f)),
	m_miniCharaImgPos(VGet(0.0f, 0.0f, 0.0f)),
	m_hMiniCharaImg(),
	m_hDrawMiniCharaImg(-1)
{
	// データ読み込み
	LoadData();
	SetRandMiniChara();
}

StageDirecting::~StageDirecting()
{
	// それぞれの画像データ削除
	DeleteGraph(m_hBackground);
	DeleteGraph(m_hBackground2);
	DeleteGraph(m_hKokuban);
	DeleteGraph(m_hChinoImg);

	// ミニキャラデータ削除
	for (auto& miniMem : m_hMiniCharaImg)
	{
		DeleteGraph(miniMem);
	}
	m_hMiniCharaImg.clear();
}

void StageDirecting::Update()
{
	m_countFrame++;
	if (m_countFrame > 6000)
	{
		m_countFrame = 0;
	}

	AnimUpdate();
	MiniCharaAnimUpdate();
}

void StageDirecting::Draw()
{
	// 背景描画
	DrawExtendGraphF(0.0f, 0.0f, Game::kScreenWidth, Game::kScreenHeight, m_hBackground, true);
	DrawExtendGraphF(0.0f, 700.0f, Game::kScreenWidth, Game::kScreenHeight, m_hBackground2, true);
	// 黒板フレーム描画
	DrawRotaGraphF(kFramePosX, kFramePosY, 1.0, 0.0, m_hKokuban, true);
	int imgX = static_cast<int>(m_chinoImgDrawPos.x), imgY = static_cast<int>(m_chinoImgDrawPos.y);
	int imgW = static_cast<int>(Game::kChipSize), imgH = static_cast<int>(kChinoImgSizeY);
	// 指定されているちの先の画像を描画
	DrawRectRotaGraphF(kChinoPosX, kChinoPosY, imgX, imgY, imgW, imgH,
		kChinosenScale, 0, m_hChinoImg, true);

	imgX = static_cast<int>(m_miniCharaImgPos.x), imgY = static_cast<int>(m_miniCharaImgPos.y);
	imgW = static_cast<int>(kMiniCharaChipSize), imgH = static_cast<int>(kMiniCharaChipSize);
	// ミニキャラ描画
	DrawRectRotaGraphF(m_miniCharaDrawPos.x, m_miniCharaDrawPos.y,
		imgX, imgY, imgW, imgH,
		kChinosenScale, 0, m_hDrawMiniCharaImg, true);
}

void StageDirecting::ChangeAnim(std::string animName)
{
	m_chinoAnimName = animName;
	if (m_chinoAnimName == "normal")
	{
		m_chinoImgDrawPos.y = kChinoImgSizeY * static_cast<int>(ChinoType::normal);
	}
	else if (m_chinoAnimName == "normalFinger")
	{
		m_chinoImgDrawPos.y = kChinoImgSizeY * static_cast<int>(ChinoType::normalFinger);
	}
	else if (m_chinoAnimName == "mouseFinger")
	{
		m_chinoImgDrawPos.y = kChinoImgSizeY * static_cast<int>(ChinoType::mouseFinger);
	}
	else if (m_chinoAnimName == "smile")
	{
		m_chinoImgDrawPos.y = kChinoImgSizeY * static_cast<int>(ChinoType::smile);
	}
	else if (m_chinoAnimName == "sad")
	{
		m_chinoImgDrawPos.y = kChinoImgSizeY * static_cast<int>(ChinoType::sad);
	}
}

void StageDirecting::LoadData()
{
	// 背景画像読み込み
	m_hBackground = LoadGraph("Data/ImageData/Background.png");
	m_hBackground2 = LoadGraph("Data/ImageData/Background2.png");
	m_hKokuban = LoadGraph("Data/ImageData/Kokuban.png");
	// ちの先画像読み込み
	m_hChinoImg = LoadGraph("Data/ImageData/Chinosen.png");
	// ミニキャラ読み込み
	m_hMiniCharaImg.push_back(LoadGraph("Data/ImageData/MiniMyu.png"));
	m_hMiniCharaImg.push_back(LoadGraph("Data/ImageData/MiniNeffy.png"));
	m_hMiniCharaImg.push_back(LoadGraph("Data/ImageData/MiniNina.png"));
	m_hMiniCharaImg.push_back(LoadGraph("Data/ImageData/MiniRara.png"));
	m_hMiniCharaImg.push_back(LoadGraph("Data/ImageData/MiniVitte.png"));
}

void StageDirecting::AnimUpdate()
{
	if (m_countFrame % kChinosenUpdateFrameNum == 0)
	{
		m_chinoImgDrawPos.x += Game::kChipSize;
		if (m_chinoImgDrawPos.x >= Game::kChipSize * 2)
		{
			m_chinoImgDrawPos.x = 0.0f;
		}
	}
}

void StageDirecting::MiniCharaAnimUpdate()
{
	m_miniCharaDrawPos.x -= kMiniCharaMoveSpeed;
	if (m_miniCharaDrawPos.x + kMiniCharaDrawChipSize < 0)
	{
		m_miniCharaDrawPos.x = kMiniCharaDrawPosX;
		SetRandMiniChara();
	}

	if (m_countFrame % kMiniCharaUpdateFrameNum == 0)
	{
		m_miniCharaImgPos.x += kMiniCharaChipSize;
		if (m_miniCharaImgPos.x >= kMiniCharaChipSize * 4)
		{
			m_miniCharaImgPos.x = 0.0f;
		}
	}
}

void StageDirecting::SetRandMiniChara()
{
	int randNum = GetRand(static_cast<int>(m_hMiniCharaImg.size() - 1));

	m_hDrawMiniCharaImg = m_hMiniCharaImg[randNum];
}
