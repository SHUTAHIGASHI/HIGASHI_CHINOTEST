#pragma once

#include <DxLib.h>
#include "InputState.h"
#include "SoundManager.h"
#include "GameDataManager.h"

namespace Game
{
	// システム基本設定 //
#ifdef _DEBUG
	// ウィンドウモード設定
	constexpr bool kWindowMode = true;
#else
	constexpr bool kWindowMode = false;
#endif

	// ウィンドウ名
	const char* const kTitleText = "チノ先生、誕生日おめでとう！！！！！！";
	// ウィンドウサイズ
	constexpr int kScreenWidth = 1920;
	constexpr int kScreenHeight = 1080;
	constexpr int kScreenWidthHalf = kScreenWidth / 2;
	constexpr int kScreenHeightHalf = kScreenHeight / 2;
	constexpr int kScreenWidthTriple = kScreenWidth * 3;
	constexpr int kScreenHeightTriple = kScreenHeight * 3;
	// ゲームで使う色コード
	constexpr int kColorPink = 0xf69896;
	constexpr int kColorCyan = 0x7db3f3;
	constexpr int kColorGray = 0xbbbbbb;
	constexpr int kColorBlack = 0x0a192c;
	constexpr int kColorWhite = 0xffffff;
	// フォントファイル
	const char* const kFontFileName = "Data/fontData/Chalk-S-JP.otf";
	// フォントサイズ
	constexpr int kFontSize = 40;
	// カラーモード
	constexpr int kColorDepth = 32;
	// プレイヤーの基本設定
	constexpr float kChipSize = 640.0f;
	// ゲームのステージサイズ
	constexpr float kGameHeightHalf = Game::kScreenHeightHalf - 100.0f;
}